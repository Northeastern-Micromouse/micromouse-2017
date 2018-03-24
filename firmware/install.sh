#!/bin/bash

# THIS WILL BE RUN ON THE HOST
HOST="debian@192.168.7.2"
BB_HOME_DIR="/home/debian"

BASE_DIR=.
BOARD_FILE="board_setup.sh"

FOLDERS="$BASE_DIR/include $BASE_DIR/src"
FILES="board_setup.sh README"
FOLDER_CMD="scp -r $FOLDERS $HOST:$BB_HOME_DIR"
FILE_CMD="scp $FILES $HOST:$BB_HOME_DIR"

$FOLDER_CMD
$FILE_CMD

echo "Files copied. Executing $BOARD_FILE on beagle"
ssh $HOST $BB_HOME_DIR/$BOARD_FILE
