#!/bin/bash -e

FILE=$1
filename="$FILE%.*"
NUMTHREADS=$2

cc -h omp -o $filename $FILE
aprun -e OMP_NUM_THREADS=$NUMTHREADS -n 1 -d $NUMTHREADS $filename

