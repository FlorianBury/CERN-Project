import numpy as np
import h5py
import sys
import argparse
import os

# Argument parser #

parser = argparse.ArgumentParser(description='Process N h5 files and concatenate the data into a single one')
parser.add_argument("-n","--number", help="Index of the last file be processed")
parser.add_argument("-f","--file_name", help="name of the file created")

args = parser.parse_args()

print "Number of the last file to be processed " + str(args.number)
print "The output file is named " + str(args.file_name)
print "Form of the input files : 'out_split_*.h5'"
# Extraction and concatenation of the files #
input_0 =  h5py.File('h5_files/out_split_0.h5', 'r')
dataset = input_0['dataset_1'][:]
input_0.close()
print "Number of entries : %12d -> State : %5.3f%% (file number 0)" % (dataset.shape[0],(100/int(args.number)))

for i in xrange (1,int(args.number)+1):
	input_iter = h5py.File('h5_files/out_split_'+str(args.number)+'.h5','r')
	set_iter = input_iter['dataset_1'][:]
	input_iter.close()
	dataset=np.concatenate((dataset,set_iter),axis=0)
	print "Number of entries : %12d -> State : %5.3f%% (file number %i)"  %(dataset.shape[0],((i+1)*100/(int(args.number)+1)),i)


# Output of the concatenated file #
Out = h5py.File('h5_files/'+str(args.file_name), 'w')
Out.create_dataset('dataset_1', data=dataset)
Out.close()

