#!/bin/bash

# Input parameters
FILE_IN="$1"
FILE_OUT="$2"
START="$3"
STOP="$4"

#Set your simulation directory 

cd /afs/cern.ch/user/f/fbury/CMSSW_9_2_3_patch2
eval $(scram runtime -sh)

cd /afs/cern.ch/user/f/fbury/Deep_learning/
#Run your program
python output_root.py -i "$FILE_IN" -o "$FILE_OUT" "$START" "$STOP"
