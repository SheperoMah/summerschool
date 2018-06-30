#!/bin/bash -e
#SBATCH -J my_job_name
#SBATCH -N 4
#SBATCH -t 00:05:00
#SBATCH -p test


FILE=$1
filename="${FILE%.*}"
NUMPROCESSES=$2

CC -o $filename $FILE

aprun -n $NUMPROCESSES ./$filename
