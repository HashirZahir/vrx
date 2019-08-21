/*
 * Copyright (C) 2019 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#pragma once

#include <string>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>
#if GAZEBO_MAJOR_VERSION >= 8
  #include <ignition/msgs.hh>
  #include <ignition/transport.hh>
#endif

namespace gazebo
{
  /// \brief This plugin visualizes forces on each link of an object.
  ///   <scaling />        Scaling for force vectors (optional)
  class ForceVisualPlugin : public ModelPlugin
  {
    /// \brief Constructor
    public: ForceVisualPlugin() = default;

    // Documentation inherited
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);

    /// \brief Update the plugin once every iteration of simulation.
    public: void Update();

    /// \brief Publish force markers for link
    /// @param link link pointer
    /// @return true if marker publishing was successful
    private: bool PublishMarker(const gazebo::physics::LinkPtr& link);

    /// \brief Pointer to the model
    private: physics::ModelPtr model;

    /// \brief Vector of link pointers for the model
    private: physics::Link_V links;

    /// \brief Transport node
    private: ignition::transport::Node node;

    /// \brief Marker service name
    private: std::string markerTopic = "/marker";

    /// \brief Marker namespace
    private: std::string ns;

    /// \brief Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;

    /// \brief Scaling factor for visualized force vectors
    private: double scaling = 1.0;
  };
}