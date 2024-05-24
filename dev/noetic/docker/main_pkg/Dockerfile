################################################################################
# There are three places where your actions are needed in this Dockerfile.
# These are marked with the label `ACTIONS_NEEDED`.
# After you are done with those:
#
# Pull the robetarme noetic base image with
# `docker login registry.gitlab.com`
# `docker pull registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros-noetic:base`
#
# Then build this Dockerfile with
# `docker compose build`,
#
# and run it with
# `docker compose up -d`.
#
# Then gain access to the container with
# `docker attach ros_noetic_xy_development_container`,
# ** where the string after "attach" is the one specified in the `docker-compose.yml` file under
# services/ros_noetic_xy_development/container_name.
#
# Then simply launch your ROS noetic packages.
################################################################################

FROM registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros-noetic:base
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


# ------------------------------------------------------------------------------
# Place ROS packages into /home/${USER}/ros1_ws workspace and catkin build
# ------------------------------------------------------------------------------
# ACTIONS_NEEDED
# COPY the src/ directory of your host's ROS workspace into the container's
# /home/${USER}/catkin_ws/src/ with `COPY --chown=${USER}:${USER}`. If a package
# uses custom interfaces then THE WORKSPACE MUST INCLUDE THE PACKAGES OF THE
# CUSTOM INTERFACES. The workspace must reside on the host alongside this
# Dockerfile, e.g. if this Dockerfile is at /path/Dockerfile then
# $ ls /path
#   Dockerfile catkin_ws
# The same applies to any other directory you want access to in the container.
# The following line is indicative and should be replaced by you.
# CAUTION: leave trailing slashes as-is
COPY --chown=${USER}:${USER} catkin_ws/src/ /home/${USER}/catkin_ws/src/
# ------------------------------------------------------------------------------

#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
# Do not modify below this line
#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

# ------------------------------------------------------------------------------
# catkin build ROS noetic packages
USER ${USER}
RUN cd /home/${USER}/catkin_ws                                              && \
    source /opt/ros/noetic/setup.bash                                       && \
    catkin build                                                            && \
    source /home/${USER}/catkin_ws/devel/setup.bash
USER root
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Bind mount/shared directory between container and host
# https://docs.docker.com/storage/bind-mounts/
RUN mkdir /home/${USER}/shared
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Entrypoint stuff
# ------------------------------------------------------------------------------
COPY --chown=${USER}:${USER} docker/main_pkg/entrypointd.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
# ------------------------------------------------------------------------------

WORKDIR /home/${USER}
CMD ["/bin/bash"]
