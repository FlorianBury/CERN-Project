#!/bin/bash
NUMBER=$1 # number of different jobs
LENGTH=$2 # number of events to be extracted

NUMBER=$(($NUMBER-1)) #because starts at 0

# Launch the different jobs #
for (( c=0; c<=$NUMBER; c++ ))
do
	start_num=$(($c*$LENGTH))	
	end_num=$(($start_num+$LENGTH))
	bsub -q 8nh -J job$c lxplusbatch_output_root.sh hits_classifier_data.root out_split_$c.h5 $start_num $end_num 
done


