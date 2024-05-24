#!/bin/bash

# ==============================================================================
# ROS noetic part
# ==============================================================================
# Get the REPOSITORY part of docker images of noetic packages (bridge tag)
cmd="docker images registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros-noetic*:bridge --format="{{.Repository}}""
imgs=$($cmd)

# $ echo $imgs
# registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros-noetic-92:bridge

imgs+=":bridge"

# Get the package's name (everything after last slash)
imgs_names=$($cmd | sed 's:.*/::')
# $ echo $imgs_names
# ros-noetic-92


for i in "${!imgs[@]}"; do

  # Create the container
  id=$(docker create "${imgs[i]}")

  # Copy the ros1_ws/install directory from the container to the host machine
  docker cp $id:/home/robetarme_user/ros1_ws/install/. - > ./noetic/"${imgs_names[i]}".tar

  # Remove the container (silently)
  docker rm -v $id > /dev/null

done
# ==============================================================================

# ------------------------------------------------------------------------------

# ==============================================================================
# ROS 2 humble part
# ==============================================================================
# Get the REPOSITORY part of docker images of humble packages (bridge tag)
cmd="docker images registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros2-humble*:bridge --format="{{.Repository}}""
imgs=$($cmd)

# $ echo $imgs
# registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros2-humble-9f:bridge

imgs+=":bridge"

# Get the package's name (everything after last slash)
imgs_names=$($cmd | sed 's:.*/::')
# $ echo $imgs_names
# ros2-humble-9f


for i in "${!imgs[@]}"; do

  # Create the container
  id=$(docker create "${imgs[i]}")

  # Copy the ros1_ws/install directory from the container to the host machine
  docker cp $id:/home/robetarme_user/ros2_ws/install/. - > ./humble/"${imgs_names[i]}".tar

  # Remove the container (silently)
  docker rm -v $id > /dev/null

done
# ==============================================================================
