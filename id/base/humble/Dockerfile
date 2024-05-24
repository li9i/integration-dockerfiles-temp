FROM osrf/ros:humble-desktop-full-jammy

# Make sure we are using bash and catching errors
SHELL ["/bin/bash", "-o", "pipefail", "-o", "errexit", "-c"]

RUN apt-get -y update                                                       && \
    DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends \
    sudo apt-utils build-essential g++ git libboost-random-dev curl lsb-release \
    python3-rosdep python3-rosinstall python3-rosinstall-generator \
    python3-wstool build-essential ros-humble-rmw-cyclonedds-cpp gosu \
    bash-completion vim nano                                                && \
    rm -rf /var/lib/apt/lists/*
RUN rm /etc/ros/rosdep/sources.list.d/20-default.list                       && \
    rosdep init


################################################################################
# User configuration
################################################################################
# Use bash
RUN rm /bin/sh && ln -s /bin/bash /bin/sh

# ------------------------------------------------------------------------------
# Create new user and home directory
# https://roboticseabass.com/2023/07/09/updated-guide-docker-and-ros2/
ARG USER=robetarme_user
RUN useradd --create-home ${USER}                                           && \
    echo ${USER} ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/${USER}         && \
    chmod 0440 /etc/sudoers.d/${USER}                                       && \
    mkdir -p /home/${USER}
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# copy .bashrc
COPY --chown=${USER}:${USER} bashrc/ /home/${USER}/.bashrc
# ------------------------------------------------------------------------------

################################################################################
# ROS 2 humble configuration
################################################################################

# ------------------------------------------------------------------------------
# Create ROS workspace
RUN rosdep update

# Drop to ${USER} so that `ros2_ws` and everything under it are owned by ${USER}
USER ${USER}

RUN source /opt/ros/humble/setup.bash                                       && \
    mkdir -p /home/${USER}/ros2_ws/src                                      && \
    cd /home/${USER}/ros2_ws                                                && \
    colcon build

# Restore default user
USER root
# ------------------------------------------------------------------------------
