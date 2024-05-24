Clone repository
```
mkdir -p ~/dockerfiles/roberarme
cd ~/dockerfiles/roberarme
git clone git@gitlab.com:certh-iti-robotics-lab/robetarme/RoBetArme.git
cd RoBetArme
export ROBETARME_DOCKER_ID_DIR=$PWD
```

---
Step 1: description: Build base images

One terminator; four panes:

```
cd $ROBETARME_DOCKER_ID_DIR/base/bridge
```
```
cd $ROBETARME_DOCKER_ID_DIR/base/noetic
```
```
cd $ROBETARME_DOCKER_ID_DIR/base/humble
```

`Alt-a`, then

```
docker compose build --no-cache
```

then `Alt-o`.

This should have built the following images

```
$ docker images
REPOSITORY                                                                        TAG  IMAGE ID     CREATED    SIZE
registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros1-humble-bridge base b53ebcce0762 7 days ago 4.21GB
registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros-noetic         base 7d1c16369f04 7 days ago 3.52GB
registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros2-humble        base c52e66bbf07d 7 days ago 3.9GB
```

---
Step 2: description: Build `development` images

One terminal:

```
mkdir -p ~/dockerfiles/roberarme
cd ~/dockerfiles/roberarme
git clone git@gitlab.com:certh-iti-robotics-lab/robetarme/RoBetArme.git
cd RoBetArme
export ROBETARME_DOCKER_DEV_DIR=$PWD
```

Then one terminator; four panes:

```
cd $ROBETARME_DOCKER_DEV_DIR/noetic
```
```
cd $ROBETARME_DOCKER_DEV_DIR/bridge/noetic
```
```
cd $ROBETARME_DOCKER_DEV_DIR/humble
```
```
cd $ROBETARME_DOCKER_DEV_DIR/bridge/humble
```

Follow instructions in their respective Dockerfiles. Then `Alt-a` and

```
docker compose build --no-cache
```

then `Alt-o`.  This should have built the following images

```
$ docker images
REPOSITORY                                                                    TAG         IMAGE ID     CREATED        SIZE
registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros-noetic-92  development 1f622f417b8c 28 minutes ago 3.53GB
registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros2-humble-9f development 61be8a004f9d 28 minutes ago 3.92GB
registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros-noetic-92  bridge      06a86c8fe22d 27 minutes ago 4.21GB
registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros2-humble-9f bridge      ea96e3c08b43 27 minutes ago 4.22GB
```

---
Step 3: description: Run `bridge/noetic` and `bridge/humble` containers in order to copy the install directories of their ros and ros2 workspaces to the host.

One terminal.

```
mkdir -p $ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/ros1_ws/install
mkdir -p $ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/install_tars/noetic
mkdir -p $ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/ros2_ws/install
mkdir -p $ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/install_tars/humble

# Change into where the tars shall reside
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/install_tars

# Tar install spaces and copy them to the appropriate directories
./tar.sh
```

---
Step 4: description: Then copy them from the host to bridge/bridge. After all ros noetic and ros2 humble install spaces have been copied into `$ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/install_tars` we need to assemble them into one install space (one per ROS version).

One terminal.

```
# Change into where the tars reside
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/install_tars/

# Untar them into the appropriate directories
./untar.sh
```

---
Step 5: description: You may now build the bridge

One terminal

```
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/
docker compose build
```

---
Step 6: description: Build deployment images. Deployment images are the same as development images but specify "new" bind mounts. We do this by wrapping development images into one `Dockerfile` and one `docker-compose.yml` file, so that the `docker run` command does not become near-illegible.

One terminator, two panes:

```
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros-noetic-92
docker compose build
```

```
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros2-humble-9f
docker compose build
```

---
