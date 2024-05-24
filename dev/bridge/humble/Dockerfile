################################################################################
# There are two places where your actions are needed in this Dockerfile.
# These are marked with the label `ACTIONS_NEEDED`.
# After you are done with those:
#
# Pull the robetarme humble bridge base image with
# `docker login registry.gitlab.com`
# `docker pull registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros1-humble-bridge:base`
#
# Then build this Dockefile with
# `docker compose build`,
#
# and run it with
# `docker compose up -d`.
#
# Then copy the `install` directory under /home/${USER}/ros2_ws/ located at the
# container to the host with
# `docker cp ros2_humble_xy_bridge_container:/home/robetarme_user/ros2_ws/install/ ros2_ws_install`
# ** where the string immediately after "docker cp" is the one specified in the `docker-compose.yml` file under
# services/ros1_humble_bridge_ros2_humble_xy/container_name.
# Reference: https://github.com/moby/moby/issues/25245#issuecomment-750336840
################################################################################

FROM registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros1-humble-bridge:base
ARG USER=robetarme_user

#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
# Do not modify above this line
#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

# ACTIONS_NEEDED
# ------------------------------------------------------------------------------
# Install your dependencies here
# ------------------------------------------------------------------------------
#RUN apt-get -y update                                                       && \
    #DEBIAN_FRONTEND=noninteractive                                          && \
    #apt install -y --no-install-recommends PACKAGE_1 PACKAGE_2 ...          && \
    #rm -rf /var/lib/apt/lists/*
# ------------------------------------------------------------------------------

################################################################################
# ROS 2 packages
################################################################################

# ------------------------------------------------------------------------------
# Place ROS 2 packages into /home/${USER}/ros2_ws workspace and colcon build
# ------------------------------------------------------------------------------
# ACTIONS_NEEDED
# COPY the src/ directory of your host's ROS 2 workspace into the container's
# /home/${USER}/ros2_ws/src/ with `COPY --chown=${USER}:${USER}`. If a package
# uses custom interfaces then THE WORKSPACE MUST INCLUDE THE PACKAGES OF THE
# CUSTOM INTERFACES. The workspace must reside on the host alongside this
# Dockerfile, e.g. if this Dockerfile is at /path/Dockerfile then
# $ ls /path
#   Dockerfile ros2_ws
# The same applies to any other directory you want access to in the container.
# The following line is indicative and should be replaced by you.
# CAUTION: leave trailing slashes as-is
COPY --chown=${USER}:${USER} ros2_ws/src/ /home/${USER}/ros2_ws/src/
# ------------------------------------------------------------------------------


#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
# Do not modify below this line
#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

# ------------------------------------------------------------------------------
# colcon build ROS 2 humble packages
USER ${USER}
RUN cd /home/${USER}/ros2_ws                                                && \
    source /opt/ros/humble/setup.bash                                       && \
    time colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
USER root
# ------------------------------------------------------------------------------

WORKDIR /home/${USER}
CMD ["/bin/bash"]
