FROM registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros2-humble:base
ARG USER=robetarme_user


# ACTIONS_NEEDED
# ------------------------------------------------------------------------------
# Install your dependencies here
# ------------------------------------------------------------------------------
RUN apt-get -y update                                                       && \
    DEBIAN_FRONTEND=noninteractive                                          && \
    apt install -y --no-install-recommends cargo clang ros-humble-ament-cmake vim && \
    rm -rf /var/lib/apt/lists/*
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# copy .bashrc
COPY --chown=${USER}:${USER} bashrc/ /home/${USER}/.bashrc
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Drop to ${USER} so that zenoh's source and the generated `build,install,log`
# are owned by ${USER}
USER ${USER}

# Clone zenoh-ros2-dds into workspace ...
RUN cd /home/${USER}/ros2_ws/src                                            && \
    git clone https://github.com/eclipse-zenoh/zenoh-plugin-ros2dds.git

# ... and colcon build it
RUN cd /home/${USER}/ros2_ws                                                && \
    source /opt/ros/humble/setup.bash                                       && \
    colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release                    && \
    source /home/${USER}/ros2_ws/install/local_setup.bash
# ------------------------------------------------------------------------------

# Restore default user
USER root
