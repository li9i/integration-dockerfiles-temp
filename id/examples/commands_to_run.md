Open up one terminator, three panes.

Pane #1

```
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge
export ROS_DOMAIN_ID=127
docker compose up -d
docker attach ros1_humble_bridge_deployment_container
```

```
ros2 run ros1_bridge dynamic_bridge
````
---
Pane #2

```
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros-noetic-92
export ROS_DOMAIN_ID=127
mkdir shared-ros-noetic-92
mkdir shared-catkin_ws
docker compose up -d
docker attach ros_noetic_92_deployment_container
```

```
roslaunch ros1_talker ros1_talker.launch
```
---
Pane #3

```
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros2-humble-9f
export ROS_DOMAIN_ID=127
mkdir shared-ros2-humble-9f
mkdir shared-ros2_ws
docker compose up -d
docker attach ros2_humble_9f_deployment_container
```

```
ros2 run cpp_pubsub listener
```

Or `unset ROS_DOMAIN_ID ` altogether: all three nodes need to be on the same `ROS_DOMAIN_ID` (not exactly but this works).

