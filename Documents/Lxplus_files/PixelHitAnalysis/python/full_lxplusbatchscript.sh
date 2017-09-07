#!/bin/sh
for i in $(seq 1 $3);
do
  echo "Sending job code $1_$2_job$i.py"
  bsub -q 1nh -J job$i lxplusbatchscript.sh $1_$2_job$i.py
done

wait
echo "All jobs sent"


#First argument = cfg file name
#Second argument = label 
#Third argument = number of jobs
