#!/bin/bash

export DYLD_LIBRARY_PATH=$PWD/allegro/lib
make UBUNTU='"ubuntu"'
# echo $DYLD_LIBRARY_PATH