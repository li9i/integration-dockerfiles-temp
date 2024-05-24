################################################################################
# There are two places where your actions are needed in this Dockerfile.
# These are marked with the label `ACTIONS_NEEDED`.
# After you are done with those:
#
# Pull the robetarme humble bridge base image with
# `docker login registry.gitlab.com`
# `docker pull registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros1-humble-bridge:base`
#
# Then build with
# `docker compose build`,
#
# and run with
# `docker compose up -d`.
#
# Then gain access to the container with
# `docker attach ros1_humble_bridge_container`,
#
# and finally launch the bridge with
# `ros2 run ros1_bridge dynamic_bridge`.
#
# The last command takes care only of the communication between the ROS noetic
# package and the ROS 2 humble package,
# i.e. you should launch their nodes separately.
################################################################################

FROM registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros1-humble-bridge:base
ARG USER=robetarme_user


################################################################################
# ROS and ROS 2 packages
################################################################################

# ------------------------------------------------------------------------------
# Copy the install space of all ROS packages into /home/${USER}/ros1_ws/install
# ------------------------------------------------------------------------------
# ACTIONS_NEEDED
# Aggregate all install directories from ROS 2 humble packages
# (manually, outside of this Dockerfile) at ros1_ws_install/.
# Then COPY them from the host into the image at /home/${USER}/ros1_ws/install/.
# All origin install directories must reside on the host alongside this
# Dockerfile, e.g. if this Dockerfile is at
# /home/HOST_USER/dockerfiles/Dockerfile
# then
# `ls /home/HOST_USER/dockerfiles/` should output something like
# Dockerfile   ros1_ws/install/   ros2_ws/install/
# CAUTION: leave trailing slashes as-is
# ------------------------------------------------------------------------------
#COPY ros1_ws_install/ /tmp/ros1_ws_install
#RUN find /tmp/ros1_ws_install -mindepth 1 -maxdepth 1 -type d | xargs cp -r -t /home/${USER}/ros1_ws/install # Reference: https://stackoverflow.com/a/149026/5297684
#RUN rm -r /tmp/ros1_ws_install
COPY --chown=${USER}:${USER} ros1_ws/install/ /home/${USER}/ros1_ws/install
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Copy the install space of all ROS 2 packages into /home/${USER}/ros2_ws/install
# ------------------------------------------------------------------------------
# ACTIONS_NEEDED
# Aggregate all install directories from ROS 2 humble packages
# (manually, outside of this Dockerfile) at ros2_ws_install/.
# Then COPY them from the host into the image at /home/${USER}/ros2_ws/install/.
# All origin install directories must reside on the host alongside this
# Dockerfile, e.g. if this Dockerfile is at
# /home/HOST_USER/dockerfiles/Dockerfile
# then
# `ls /home/HOST_USER/dockerfiles/` should output something like
# Dockerfile   ros1_ws/install/   ros2_ws/install/
# CAUTION: leave trailing slashes as-is
# ------------------------------------------------------------------------------
#COPY ros2_ws_install/ /tmp/ros2_ws_install
#RUN find /tmp/ros2_ws_install -mindepth 1 -maxdepth 1 -type d | xargs cp -r -t /home/${USER}/ros2_ws/install # Reference: https://stackoverflow.com/a/149026/5297684
#RUN rm -r /tmp/ros2_ws_install
COPY --chown=${USER}:${USER} ros2_ws/install/ /home/${USER}/ros2_ws/install
# ------------------------------------------------------------------------------

# Change to robetarme_user so that ownership is preserved across all ROS
# workspaces
USER ${USER}

# ------------------------------------------------------------------------------
# Source ROS and ROS 2 workspaces before /opt/ros/humble
# Then compile ros1_bridge. The bridge's git repository has been already cloned
# in the base image.
# ------------------------------------------------------------------------------
RUN source /home/${USER}/ros1_ws/install/setup.bash                         && \
    source /home/${USER}/ros2_ws/install/setup.bash                         && \
    source /opt/ros/humble/setup.bash                                       && \
    cd /home/${USER}/ros1_humble_bridge_ws/                                 && \
    MEMG=$(printf "%.0f" $(free -g | awk '/^Mem:/{print $2}'));                \
    NPROC=$(nproc);  MIN=$((MEMG<NPROC ? MEMG : NPROC));                       \
    chown -R ${USER} .                                                      && \
    time MAKEFLAGS="-j $MIN" colcon build --event-handlers console_direct+     \
    --cmake-args -DCMAKE_BUILD_TYPE=Release
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Pack all ROS 1 dependent libraries
# ------------------------------------------------------------------------------
RUN  ROS1_LIBS="libxmlrpcpp.so";                                               \
     ROS1_LIBS="$ROS1_LIBS librostime.so";                                     \
     ROS1_LIBS="$ROS1_LIBS libroscpp.so";                                      \
     ROS1_LIBS="$ROS1_LIBS libroscpp_serialization.so";                        \
     ROS1_LIBS="$ROS1_LIBS librosconsole.so";                                  \
     ROS1_LIBS="$ROS1_LIBS librosconsole_log4cxx.so";                          \
     ROS1_LIBS="$ROS1_LIBS librosconsole_backend_interface.so";                \
     ROS1_LIBS="$ROS1_LIBS liblog4cxx.so";                                     \
     ROS1_LIBS="$ROS1_LIBS libcpp_common.so";                                  \
     ROS1_LIBS="$ROS1_LIBS libb64.so";                                         \
     ROS1_LIBS="$ROS1_LIBS libaprutil-1.so";                                   \
     ROS1_LIBS="$ROS1_LIBS libapr-1.so";                                       \
     cd /home/${USER}/ros1_humble_bridge_ws/install/ros1_bridge/lib;           \
     for soFile in $ROS1_LIBS; do                                              \
         soFilePath=$(ldd libros1_bridge.so | grep $soFile | awk '{print $3;}');\
         cp $soFilePath ./;                                                    \
     done
# ------------------------------------------------------------------------------

# Restore default user
USER root

WORKDIR /home/${USER}
CMD ["/bin/bash"]
