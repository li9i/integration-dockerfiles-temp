# Summary

This repository holds dockerfiles necessary for the development of ROS noetic and ROS 2 humble packages of our project.  The `noetic` and `humble` directories hold example `Dockerfile`s; in each of these two there are instructions on how to modify them in order for your packages to be placed into a Docker image, depending on your package's ROS version. If you don't have Docker installed you should start from the [Installing Docker](#installing-docker) section. Afterwards go to the [Identifying your case](#identifying-your-case) section. At the end visit the [After you are finished]((#after-you-are-finished)) section.



# Directory structure

```
$ROBETARME_DOCKER_DEV_DIR/
├── noetic/
│   ├── catkin_ws/src
│   ├── docker/
│   │   ├── main_pkg/
│   │   │   ├── docker-compose.yml
│   │   │   ├── Dockerfile
│   │   │   └── entrypointd.sh  
│   │   └── bridge/
│   │       ├── docker-compose.yml
│   │       └── Dockerfile  
│   └── shared-ros-noetic-xy
└── humble/
    ├── ros2_ws/src
    ├── docker/
    │   ├── main_pkg/
    │   │   ├── docker-compose.yml
    │   │   ├── Dockerfile
    │   │   └── entrypointd.sh  
    │   └── bridge/
    │       ├── docker-compose.yml
    │       └── Dockerfile   
    └── shared-ros2-humble-mn
```



Table of Contents
=================

* [Installing Docker](#installing-docker)
* [Identifying your case](#identifying-your-case)
  * [You are developing a ROS noetic package](#you-are-developing-a-ROS-noetic-package)
  * [You are developing a ROS 2 humble package](#you-are-developing-a-ROS-2-humble-package)
* [After you are finished](#after-you-are-finished)



# Installing Docker

We find [this section](https://docs.docker.com/engine/install/ubuntu/#install-using-the-convenience-script) of the official Docker installation instructions coupled with [this guide](https://www.youtube.com/watch?v=SAMPOK_lazw&t=67s) very easy to follow.


# Identifying your case



## You are developing ROS noetic packages

- Place your packages under `$ROBETARME_DOCKER_DEV_DIR/noetic/catkin_ws/src` (see [Directory structure](#directory-structure))
- Follow the instructions in the `Dockerfile` and `docker-compose.yml` files under `ROBETARME_DOCKER_DEV_DIR/noetic/docker/main_pkg`

**Should your package communicate with a ROS 2 humble package via custom interfaces** follow the instructions in the `Dockerfile` and `docker-compose.yml` files under `$ROBETARME_DOCKER_DEV_DIR/noetic/docker/bridge`.

## You are developing ROS 2 humble packages

- Place your packages under `$ROBETARME_DOCKER_DEV_DIR/humble/ros2_ws/src` (see [Directory structure](#directory-structure)) 
- Follow the instructions in the `Dockerfile` and `docker-compose.yml` files under `$ROBETARME_DOCKER_DEV_DIR/humble/docker/main_pkg`

**Should your package communicate with a ROS 2 humble package via custom interfaces** follow the instructions in the `Dockerfile` and `docker-compose.yml` files under `$ROBETARME_DOCKER_DEV_DIR/humble/docker/bridge`.

## You are developing something else
You shouldn't be developing something else! This incident will be reported.



# After you are finished

At this point the output of `$ docker images` should include the docker image that holds the functionality of your package:

```
$ docker images
REPOSITORY                          TAG           IMAGE ID       CREATED       SIZE
  ...
registry.gitlab.com/.../my-pkg-3f   development   3d7a8d9be17a   4 hours ago   4.59GB
  ...
```

If your package communicates with a package of another version of ROS via custom interfaces then, in addition, you should be seeing an extra entry in the above list, which is the image that holds the ROS 2 humble `install` directory of your package (regardless of your package's ROS version) :

```
$ docker images
REPOSITORY                          TAG           IMAGE ID       CREATED       SIZE
  ...
registry.gitlab.com/.../my-pkg-3f   development   3d7a8d9be17a   4 hours ago   4.59GB
registry.gitlab.com/.../my-pkg-3f   bridge        9be17a3d7a8d   4 hours ago   3.16GB
  ...
```

The next step is to push your image(s) to [RobetArme's Gitlab image registry](https://gitlab.com/certh-iti-robotics-lab/robetarme/RoBetArme/container_registry) with

```
docker login registry.gitlab.com
docker push registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/my-pkg-3f:development
docker push registry.gitlab.com/certh-iti-robotics-lab/robetarme/robetarme/my-pkg-3f:bridge
```
