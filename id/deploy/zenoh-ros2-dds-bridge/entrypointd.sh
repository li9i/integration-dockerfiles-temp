#!/bin/sh

set -e

# ------------------------------------------------------------------------------
# Drop from root to robetarme_user
#set -- gosu $USER "$@"
# ------------------------------------------------------------------------------

ROS_DOMAIN_ID=26
source /opt/ros/humble/setup.bash
source ~/ros2_ws/install/local_setup.bash

#zenoh_bridge_ros2dds -c ~/ros2_ws/src/zenoh-plugin-ros2dds/robetarme_zenoh_configuration_files/zenoh_config.json5

exec "$@"
