#!/bin/sh
for i in {1..8}
do
	cmsRun pixelClassifier_cfg_split_job$i.py 2>&1 | tee log$i & 
	echo "Start job $i"
done

wait
echo "cmsRun done"

wait
./pixelClassifier_cfg_split_merge_TFileService.sh
wait
./pixelClassifier_cfg_split_cleanup.sh 

wait 
echo "Merge and cleanup done"
