#!/bin/bash -e
FILE=$1
filename="$FILE%.*"
NUMPROCESSES=$2

CC -o $filename $FILE
aprun -n $NUMPROCESSES ./$filename

