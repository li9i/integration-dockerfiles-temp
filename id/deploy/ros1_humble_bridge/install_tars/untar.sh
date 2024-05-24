#!/bin/bash

# untar `.tar`s under noetic/ into ../ros1_ws/install
for i in noetic/*; do
  tar -xvf "$i" -C ../ros1_ws/install
done

# untar `.tar`s under humble/ into ../ros2_ws/install
for i in humble/*; do
  tar -xvf "$i" -C ../ros2_ws/install
done
