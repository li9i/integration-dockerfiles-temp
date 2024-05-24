# Summary

This repository holds example dockerfiles necessary for the development, integration, and deployment of ROS noetic and ROS 2 humble packages of our project.  The `base` directory holds dockerfiles which produce images on top of which developers of ROS packages write their own `Dockerfile`s. The `deploy/` directory is used by us—the integration and deployment team—in order to run the resulting images, plus images for bridging packages of different ROS versions and different physical machines.

This `README` provides the commands needed to provide an overview of the integration and deployment process. For the full history of commands needed to build all images and run them see `commands_to_build.md` and `commands_to_run.md` under `examples/`.



# Directory structure

<!--
tree.nathanfriend.io/?s=(%27options!(%27fancyA~fullPath!false~trailingSlashA~rootDotA)~F(%27F%27base3noetic38393zenohBdeploy3*E1710IE2720I...3*zenoh-C2-dds-94...0IC1_8_945_tars4*noetic4*84C1G4C2G0examples6build.md6run.md*3*%27)~version!%271%27)*%20%2004dH-compose.yml4DHfileB3B*43I5install63commands_to_74shared-E8humble9bridgeA!trueB%5CnCrosEpkg_Fsource!G_ws4*5HockerI**%01IHGFECBA98765430*
--->


```
$ROBETARME_DOCKER_ID_DIR
├── base/
│   ├── noetic
│   ├── humble
│   ├── bridge
│   └── zenoh
├── deploy/
│   ├── ros2-humble-xy/
│   │   ├── shared-ros2-humble-xy/
│   │   ├── shared-ros2_ws/src
│   │   ├── docker-compose.yml
│   │   └── Dockerfile
│   ├── ros-noetic-mn/
│   │   ├── shared-ros-noetic-mn/
│   │   ├── shared-catkin_ws/src
│   │   ├── docker-compose.yml
│   │   └── Dockerfile
│   ├── ...
│   ├── ros1_humble_bridge/
│   │   ├── install_tars/
│   │   │   ├── noetic
│   │   │   └── humble
│   │   ├── ros1_ws/
│   │   │   └── install
│   │   ├── ros2_ws/
│   │   │   └── install
│   │   ├── docker-compose.yml
│   │   └── Dockerfile
│   └── zenoh-ros2-dds-bridge/
│       ├── ...
│       ├── docker-compose.yml
│       └── Dockerfile
└── examples/
    ├── commands_to_build.md
    └── commands_to_run.md 
```



Table of Contents
=================

* [Entrypoint](#entrypoint)
  * [Assembling everything together](#assembling-everything-together)
    * [Bind mounts](#bind-mounts)
  * [Running everything](#run)
    * [Preparing to run](#preparing-to-run)
    * [Actually running](#actually-running)



# Entrypoint

First we [assemble](#assembling-everything-together), then we [run](#run).

## Assembling everything together

Once all images have been pushed to the [image registry](https://gitlab.com/certh-iti-robotics-lab/robetarme/RoBetArme/container_registry), it is time to pull them to the robot.

![](https://i.imgur.com/VzVj15l.png)

```
...
docker pull registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros-noetic-92:development
docker pull registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros-noetic-92:bridge
docker pull registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros2-humble-9f:development
docker pull registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/ros2-humble-9f:bridge
...
```

If communication occurred without custom interfaces then at this point [we would just run the images, log into the containers, and launch ROS nodes](#run). In our case, though, before these things happen we need to copy from the images and assemble the install directories of all workspaces (which hold packages that communicate through custom interfaces) into one install directory per ROS version, and then copy those two from the host to the bridge's image.

After pulling all images: for each ROS version, for each package, copy a `tar` of each install space onto the host with:

```
# Change into where the tars shall reside
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/install_tars/

# Tar install spaces and copy them to the appropriate directories
./tar.sh
```

Then assemble all of them into one install space per ROS version:

```
# Change into where the tars reside
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/install_tars/

# Untar them into the appropriate directories
./untar.sh
```

The two final install directories

````
$ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/ros1_ws/install
$ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/ros2_ws/install
````

will be `COPY`-ed into the bridge's image—see `$ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/Dockerfile:L35-75`. Do this by building the image with

```
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge/
docker compose build
```

### Bind mounts

By default all images are endowed with __two__ two-way drop boxes for communication between container and host. One shares the ROS workspace of the container to the outside so that source code modifications may occur in runtime without having to build images ex novo, and the second shares anything else (data, etc). At the container's side the former directory resides at `$HOME/catkin_ws` or `$HOME/ros2_ws`. On the host's side they reside at `$ROS_NOETIC_92_PKG_SHARED_DIRECTORY_PARENT/shared-catkin_ws` and `$ROS2_HUMBLE_9F_PKG_SHARED_DIRECTORY_PARENT/shared-ros2_ws`. The second type of bind mount resides at the container's side at `$HOME/shared`. On the host this directory may be placed anywhere but its name should follow the naming convention `shared`-`$(unique_pkg_name)`, e.g. `shared-ros-noetic-92`, `shared-ros2-humble-9f`, etc. 

Each such directory should be `mkdir`-ed beforehand and owned by the current non-root user, e.g:

```
# cd $ROS_NOETIC_92_PKG_SHARED_DIRECTORY_PARENT
mkdir shared-ros-noetic-92
mkdir shared-catkin_ws
```

and

```
# cd $ROS2_HUMBLE_9F_PKG_SHARED_DIRECTORY_PARENT
mkdir shared-ros2-humble-9f
mkdir shared-ros2_ws
```



## Run

### Preparing to run

What will eventually run are as many containers as there are `development` images. In order not to clutter or obfuscate `docker run` commands we do this using `compose`. Further, in order to do this in an orderly fashion, we change into the `deploy` directory and then `mkdir` one directory per image, with the same name, e.g.:
```
cd $ROBETARME_DOCKER_ID_DIR/deploy
mkdir ros2-humble-9f
mkdir ros-noetic-92
...
```

where in each of them we place
- one `Dockerfile`, which is based on the `development` image of each package
- one `docker-compose.yml`, which replaces tag `development` with `deployment` and specifies the bind mount, which has to be the same as that used during development
- the bind mount itself, with the naming convention `shared`-`$(unique_pkg_name)`

Then simply build each `deployment` image:

```
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros-noetic-92
mkdir shared-ros-noetic-92
mkdir shared-catkin_ws
docker compose build

cd $ROBETARME_DOCKER_ID_DIR/deploy/ros2-humble-9f
mkdir shared-ros2-humble-9f
mkdir shared-ros2_ws
docker compose build
...
```


### Actually running

We run as many containers as there are development images, plus one for the bridge (plus one for `zenoh` when needed). In this example we start three containers: one for a ROS noetic package provided by image `ros-noetic-92`, one for a ROS 2 humble package provided by image `ros2-humble-9f`, and one for the bridge.

Open up a terminator and split into three panes; then in each of them do:

Pane #1: start the bridge's container
```
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros1_humble_bridge
docker compose up -d
docker attach ros1_humble_bridge_deployment_container
```
```
ros2 run ros1_bridge dynamic_bridge
```
Pane #2: start a container based on `ros-noetic-92` and then, inside the container, launch the ROS noetic package

```
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros-noetic-92
docker compose up -d
docker attach ros_noetic_92_deployment_container
```
```
roslaunch ros1_talker ros1_talker.launch
```
Pane #3: start a container based on `ros2-humble-9f` and then, inside the container, launch the ROS 2 humble package
```
cd $ROBETARME_DOCKER_ID_DIR/deploy/ros2-humble-9f
docker compose up -d
docker attach ros2_humble_9f_deployment_container
```
```
ros2 run cpp_pubsub listener
```
