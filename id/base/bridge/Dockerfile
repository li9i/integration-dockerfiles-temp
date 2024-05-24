FROM osrf/ros:humble-desktop-full-jammy

# Make sure we are using bash and catching errors
SHELL ["/bin/bash", "-o", "pipefail", "-o", "errexit", "-c"]

###########################
# 1.) Bring system up to the latest ROS desktop configuration
###########################
RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get -y install ros-humble-desktop

###########################
# 2.) Temporarily remove ROS2 apt repository
###########################
RUN mv /etc/apt/sources.list.d/ros2-latest.list /root/
RUN apt-get update

###########################
# 3.) comment out the catkin conflict
###########################
RUN sed  -i -e 's|^Conflicts: catkin|#Conflicts: catkin|' /var/lib/dpkg/status
RUN apt-get install -f

###########################
# 4.) force install these packages
###########################
RUN apt-get download python3-catkin-pkg
RUN apt-get download python3-rospkg
RUN apt-get download python3-rosdistro
RUN dpkg --force-overwrite -i python3-catkin-pkg*.deb
RUN dpkg --force-overwrite -i python3-rospkg*.deb
RUN dpkg --force-overwrite -i python3-rosdistro*.deb
RUN apt-get install -f

###########################
# 5.) Install the latest ROS1 desktop configuration
# see https://packages.ubuntu.com/jammy/ros-desktop-dev
# note: ros-desktop-dev automatically includes tf tf2
###########################
RUN apt-get -y install ros-desktop-dev

# fix ARM64 pkgconfig path issue -- Fix provided by ambrosekwok
RUN if [[ $(uname -m) = "arm64" || $(uname -m) = "aarch64" ]]; then                    \
    cp /usr/lib/x86_64-linux-gnu/pkgconfig/* /usr/lib/aarch64-linux-gnu/pkgconfig/;    \
    fi

###########################
# 6.) Restore the ROS2 apt repos
###########################
RUN mv /root/ros2-latest.list /etc/apt/sources.list.d/
RUN apt-get -y update


###########################
# 7.) Install tools and rmw
###########################
RUN apt-get -y update                                                       && \
    DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends sudo apt-utils build-essential g++ git libboost-random-dev curl lsb-release python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential ros-humble-rmw-cyclonedds-cpp gosu vim nano && \
    rm -rf /var/lib/apt/lists/*


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
# Create ROS workspace; ROS 2 workspace; the bridge and its workspace
################################################################################

# Drop to ${USER} so that the generated directories are owned by ${USER}
USER ${USER}

# ------------------------------------------------------------------------------
# colcon build ros1_ws
# ------------------------------------------------------------------------------
RUN mkdir -p /home/${USER}/ros1_ws/src
RUN cd /home/${USER}/ros1_ws                                                && \
    unset ROS_DISTRO                                                        && \
    time colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# colcon build ros2_ws
# ------------------------------------------------------------------------------
RUN mkdir -p /home/${USER}/ros2_ws/src
RUN cd /home/${USER}/ros2_ws                                                && \
    source /opt/ros/humble/setup.bash                                       && \
    time colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Source ROS and ROS 2 workspaces before /opt/ros/humble; get the bridge
# ------------------------------------------------------------------------------
RUN source /home/${USER}/ros1_ws/install/setup.bash                         && \
    source /home/${USER}/ros2_ws/install/setup.bash                         && \
    source /opt/ros/humble/setup.bash                                       && \
    mkdir -p /home/${USER}/ros1_humble_bridge_ws/src                        && \
    cd /home/${USER}/ros1_humble_bridge_ws/src                              && \
    git clone https://github.com/ros2/ros1_bridge                           && \
    cd ros1_bridge/                                                         && \
    git checkout b9f1739                                                    #&& \
    #cd ../..                                                                && \
    #MEMG=$(printf "%.0f" $(free -g | awk '/^Mem:/{print $2}'));                \
    #NPROC=$(nproc);  MIN=$((MEMG<NPROC ? MEMG : NPROC));                       \
    #time MAKEFLAGS="-j $MIN" colcon build --event-handlers console_direct+     \
      # -cmake-args -DCMAKE_BUILD_TYPE=Release
# ------------------------------------------------------------------------------

# Restore default user
USER root
