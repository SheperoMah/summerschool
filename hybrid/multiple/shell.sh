#!/bin/bash -e
FILE=$1
filename="${FILE%.*}"
NUMCORES=$2
NUMTHREADS=$3


CC -h omp -o $filename $FILE

aprun -n $NUMCORES -d $NUMTHREADS -e OMP_NUM_THREADS=$NUMTHREADS -e MPICH_MAX_THREAD_SAFTEY=multiple $filename
