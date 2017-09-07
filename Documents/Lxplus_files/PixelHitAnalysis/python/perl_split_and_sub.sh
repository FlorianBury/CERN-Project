##!/bin/bash
N=$(($1))
echo "Start of Split"
#perl cmsSplit.pl pixelHitsAOD_cfg.py --filelist files_MC_1000037_200_10.txt -n $N --label split_pileup_200_10
perl cmsSplit.pl pixelHitsAOD_cfg.py --filelist files_MC_1000037_200_3.txt -n $N --label split_pileup_200_3
#perl cmsSplit.pl pixelHitsAOD_cfg.py --filelist files_MC_1000037_200_30.txt -n $N --label split_pileup_200_30

#perl cmsSplit.pl pixelHitsAOD_cfg.py --filelist files_MC_1000037_300_10.txt -n $N --label split_pileup_300_10
perl cmsSplit.pl pixelHitsAOD_cfg.py --filelist files_MC_1000037_300_3.txt -n $N --label split_pileup_300_3
#perl cmsSplit.pl pixelHitsAOD_cfg.py --filelist files_MC_1000037_300_30.txt -n $N --label split_pileup_300_30

#perl cmsSplit.pl pixelHitsAOD_cfg.py --filelist files_MC_1000037_400_10.txt -n $N --label split_pileup_400_10
perl cmsSplit.pl pixelHitsAOD_cfg.py --filelist files_MC_1000037_400_3.txt -n $N --label split_pileup_400_3
#perl cmsSplit.pl pixelHitsAOD_cfg.py --filelist files_MC_1000037_400_30.txt -n $N --label split_pileup_400_30

#perl cmsSplit.pl pixelHitsAOD_cfg.py --filelist files_MC_1000037_500_10.txt -n $N --label split_pileup_500_10
perl cmsSplit.pl pixelHitsAOD_cfg.py --filelist files_MC_1000037_500_3.txt -n $N --label split_pileup_500_3
#perl cmsSplit.pl pixelHitsAOD_cfg.py --filelist files_MC_1000037_500_30.txt -n $N --label split_pileup_500_30

wait
echo "Start of Submit"
for i in $(seq 1 $N);
do
	echo "Starting sub job $i"
#	bsub -q 1nh -J job_200_10_$i lxplusbatchscript.sh pixelHitsAOD_cfg_split_pileup_200_10_job$i.py 
	bsub -q 1nh -J job_200_3_$i lxplusbatchscript.sh pixelHitsAOD_cfg_split_pileup_200_3_job$i.py 
#	bsub -q 1nh -J job_200_30_$i lxplusbatchscript.sh pixelHitsAOD_cfg_split_pileup_200_30_job$i.py 

#	bsub -q 1nh -J job_300_10_$i lxplusbatchscript.sh pixelHitsAOD_cfg_split_pileup_300_10_job$i.py 
	bsub -q 1nh -J job_300_3_$i lxplusbatchscript.sh pixelHitsAOD_cfg_split_pileup_300_3_job$i.py 
#	bsub -q 1nh -J job_300_30_$i lxplusbatchscript.sh pixelHitsAOD_cfg_split_pileup_300_30_job$i.py 
		
#	bsub -q 1nh -J job_400_10_$i lxplusbatchscript.sh pixelHitsAOD_cfg_split_pileup_400_10_job$i.py 
	bsub -q 1nh -J job_400_3_$i lxplusbatchscript.sh pixelHitsAOD_cfg_split_pileup_400_3_job$i.py 
#	bsub -q 1nh -J job_400_30_$i lxplusbatchscript.sh pixelHitsAOD_cfg_split_pileup_400_30_job$i.py 
	
#	bsub -q 1nh -J job_500_10_$i lxplusbatchscript.sh pixelHitsAOD_cfg_split_pileup_500_10_job$i.py 
	bsub -q 1nh -J job_500_3_$i lxplusbatchscript.sh pixelHitsAOD_cfg_split_pileup_500_3_job$i.py 
#	bsub -q 1nh -J job_500_30_$i lxplusbatchscript.sh pixelHitsAOD_cfg_split_pileup_500_30_job$i.py 
done
