import numpy as np
import h5py
import sys
import argparse
import os

# Argument parser #

parser = argparse.ArgumentParser(description='Process N h5 files and concatenate the data into a single one')
parser.add_argument("-i","--input", help="Names of the files to be concatenated", nargs='+')
parser.add_argument("-o","--output", help="Name of output file")

args = parser.parse_args()
path = '/home/florian/Documents/Part2/Deep_learning/h5_files/'

# Extraction and concatenation of the files #
firstfile = h5py.File(path+args.input[0], 'r')
dataset = firstfile['dataset_1'][:]
firstfile.close()
print ("File 1 concatenated : {}".format(args.input[0]))

entry = 0
for i in range(len(args.input)):
	if i==0: continue
	afile = h5py.File(path+args.input[i], 'r')
	aset = afile['dataset_1'][:]
	afile.close()
	dataset=np.concatenate((dataset,aset),axis=0)
	print ("File {} concatenated : {}".format(i+1,args.input[i]))


# Output of the concatenated file #
Out = h5py.File(path+str(args.output), 'w')
Out.create_dataset('dataset_1', data=dataset)
Out.close()
print "Output of the file"
