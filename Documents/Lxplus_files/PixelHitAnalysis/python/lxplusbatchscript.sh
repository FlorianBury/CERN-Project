#!/bin/bash
# Lxplus Batch Job Script
CMSSW_PROJECT_SRC="CMSSW_9_2_3_patch2/src/SusyWithDeDx/PixelHitAnalysis"
CFG_FILE="python"

cd /afs/cern.ch/user/f/fbury/$CMSSW_PROJECT_SRC
eval `scramv1 runtime -sh`
cmsRun /afs/cern.ch/user/f/fbury/$CMSSW_PROJECT_SRC/$CFG_FILE/$1
