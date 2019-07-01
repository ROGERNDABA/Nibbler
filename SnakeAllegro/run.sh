#!/bin/bash

export LD_LIBRARY_PATH=$PWD/allegro/lib
make
unset LD_LIBRARY_PATH