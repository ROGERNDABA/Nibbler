#!/bin/bash

export DYLD_LIBRARY_PATH=$PWD/allegro/lib
make
echo $DYLD_LIBRARY_PATH