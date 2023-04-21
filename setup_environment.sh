#!/bin/bash
directory=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
export MF_PROJECTS_DIR="$directory"
export MF_BASICS_DIR="$directory/MFBasics"
export BULLET_PHYSICS_HEADERS="/usr/include/bullet/"
export LIB_NOISE_HEADERS="/usr/include/bullet/"
# export STB_DIR=
# export TINY_OBJECT_LOADER=