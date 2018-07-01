#!/bin/bash -e
FILE=$1
filename="${FILE%.*}"
numProcesses=$2

cc -o $filename $FILE

aprun -n $numProcesses ./$filename 
