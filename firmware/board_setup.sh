#! /bin/bash

# THIS FILE WILL BE RUN ON THE BEAGLE
HOME_DIR=/home/debian

# COMPILE I2C
pushd $HOME_DIR/src
make clean && make
popd
