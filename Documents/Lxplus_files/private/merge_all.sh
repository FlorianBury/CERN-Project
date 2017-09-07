#!/bin/bash
#Merge without pileup
hadd -f hits_AOD_MC_1000037_pileup.root hits_AOD_200_10_pileup.root hits_AOD_200_30_pileup.root hits_AOD_200_3_pileup.root hits_AOD_300_10_pileup.root hits_AOD_300_10_pileup.root hits_AOD_300_30_pileup.root hits_AOD_300_3_pileup.root hits_AOD_400_10_pileup.root hits_AOD_400_30_pileup.root hits_AOD_400_3_pileup.root hits_AOD_500_10_pileup.root hits_AOD_500_30_pileup.root hits_AOD_500_3_pileup.root 

#Merge with pileup
hadd -f hits_AOD_MC_1000037.root hits_AOD_200_10.root hits_AOD_200_30.root hits_AOD_200_3.root hits_AOD_300_10.root hits_AOD_300_10.root hits_AOD_300_30.root hits_AOD_300_3.root hits_AOD_400_10.root hits_AOD_400_30.root hits_AOD_400_3.root hits_AOD_500_10.root hits_AOD_500_30.root hits_AOD_500_3.root 
