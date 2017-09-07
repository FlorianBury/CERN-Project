#!/bin/bash

export ClusterId=$1
export ProcId=$2
shift $#

echo "This is: $ClusterId $ProcId"

#Set your simulation directory 

cd /afs/cern.ch/user/f/fbury/CMSSW_9_2_3_patch2
eval $(scram runtime -sh)

cd /afs/cern.ch/user/f/fbury/Deep_learning/
#Run your program

#cd /afs/cern.ch/user/f/fbury/Deep_learning 
#export PYTHONPATH=/afs/cern.ch/sw/lcg/external/pyanalysis/1.3_python2.7/x86_64-slc6-gcc47-opt/lib/python2.7/site-packages/:$PYTHONPATH 
#echo $_CONDOR_SCRATCH_DIR

printf "Start time: "; /bin/date
printf "Job is running on node: "; /bin/hostname
printf "Job running as user: "; /usr/bin/id
printf "Job is running in directory: "; /bin/pwd

python output_root.py hits_classifier_data.root out_data_test.h5 0 20000
