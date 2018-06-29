#!/bin/bash -e
NUMTHREADS=$1



make clean && make -j4
aprun -e OMP_NUM_THREADS=$NUMTHREADS -n 1 -d $NUMTHREADS ./heat_serial 
