# If you havent' done so already, pull the robetarme zenoh bridge base image with
# `docker login registry.gitlab.com`
# `docker pull registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/zenoh-ros2-dds-bridge:base`

FROM registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/zenoh-ros2-dds-bridge:base
ARG USER=robetarme_user

# ------------------------------------------------------------------------------
# Copy zenoh configuration file for this machine over to the image
# ------------------------------------------------------------------------------
USER ${USER}
RUN mkdir /home/${USER}/ros2_ws/src/zenoh-plugin-ros2dds/robetarme_zenoh_configuration_files
USER root
COPY --chown=${USER}:${USER} zenoh_config.json5 /home/${USER}/ros2_ws/src/zenoh-plugin-ros2dds/robetarme_zenoh_configuration_files/zenoh_config.json5
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Copy cyclonedds configuration and use it
COPY --chown=${USER}:${USER} cyclonedds.conf.xml /home/${USER}/cyclonedds.conf.xml
RUN echo "export CYCLONEDDS_URI=file:///home/${USER}/cyclonedds.conf.xml" >> /home/${USER}/.bashrc
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Specify ROS_DOMAIN_ID
# ------------------------------------------------------------------------------
RUN echo "export ROS_DOMAIN_ID=26" >> /home/${USER}/.bashrc
# ------------------------------------------------------------------------------
# DEPRECATED
# Make ${USER} own the source space of the ROS 2 workspace
# (owning all of the workspace results in a huge image)
#RUN chown -R ${USER} /home/${USER}/ros2_ws/src/
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
COPY --chown=${USER}:${USER} entrypointd.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
# ------------------------------------------------------------------------------

WORKDIR /home/${USER}
CMD ["/bin/bash"]
