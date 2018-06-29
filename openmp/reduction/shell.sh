#!/bin/bash
set -e # exit after errors

FILE=$1
filename="${FILE%.*}"
NUMBERTHREADS=$2


cc -h omp -o $filename $FILE
aprun -e OMP_NUM_THREADS=$NUMBERTHREADS -n 1 -d $NUMBERTHREADS ./$filename 

