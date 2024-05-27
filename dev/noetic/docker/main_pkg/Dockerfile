################################################################################
# There are places where your actions are needed in this Dockerfile.
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

# ACTIONS_NEEDED
# ------------------------------------------------------------------------------
# Place your ROS packages into the host's catkin_ws/src directory
# i.e. $PWD/../../catkin_ws/src. This directory will be copied verbatim into
# the image.
#
# CAUTION! Anything else you `COPY` must be specified with
# `COPY --chown=${USER}:${USER} source destination`
# ------------------------------------------------------------------------------

#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
# Do not modify below this line
#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

# ------------------------------------------------------------------------------
# COPY the src/ directory of your host's ROS workspace into the container's
# ------------------------------------------------------------------------------
COPY --chown=${USER}:${USER} catkin_ws/src/ /home/${USER}/catkin_ws/src/
# ------------------------------------------------------------------------------

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
# Bind mount/shared directory between container and host;
# robetarme_user is owner
# https://docs.docker.com/storage/bind-mounts/
USER ${USER}
RUN mkdir /home/${USER}/shared
USER root
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
