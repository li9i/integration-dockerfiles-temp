FROM osrf/ros:noetic-desktop-full-focal

# Make sure we are using bash and catching errors
SHELL ["/bin/bash", "-o", "pipefail", "-o", "errexit", "-c"]

RUN apt-get -y update                                                       && \
    DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends \
    sudo apt-utils build-essential g++ git libboost-random-dev curl lsb-release \
    python3-catkin-tools python3-rosdep python3-rosinstall \
    python3-rosinstall-generator python3-wstool build-essential gosu vim nano && \
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
# ROS noetic configuration
################################################################################

# ------------------------------------------------------------------------------
RUN rosdep update

# Drop to ${USER} so that `catkin_ws/` and everything under it are owned by ${USER}
USER ${USER}

# Create ROS workspace
RUN source /opt/ros/noetic/setup.bash                                       && \
    mkdir -p /home/${USER}/catkin_ws/src                                    && \
    cd /home/${USER}/catkin_ws                                              && \
    # https://github.com/catkin/catkin_tools/issues/525#issuecomment-981499680
    catkin config --extend /opt/ros/noetic                                  && \
    catkin build
# ------------------------------------------------------------------------------

# Restore default user
USER root
