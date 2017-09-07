import numpy as np
import h5py
import matplotlib.pyplot as plt
import sys
import os
import argparse

# Argument parser #

parser = argparse.ArgumentParser(description='Compare two outputs of the NN')
parser.add_argument("-o1","--output1", help="First set of output -> COMPULSORY")
parser.add_argument("-o2","--output2", help="Second set of output -> COMPULSORY")

parser.add_argument("-l1","--label1", help="Label first set of output -> COMPULSORY")
parser.add_argument("-l2","--label2", help="Label second set of output -> COMPULSORY")

args = parser.parse_args()


print "\nFirst input from : " + str(args.output1) + " with label : " + str(args.label1)
print "Second input from : " + str(args.output2) + " with label : " + str(args.label2)


# Input of the data #

input_1 = h5py.File('Plots/NN_single_output/data_files/'+str(args.output1),'r')
set1 = input_1['dataset_1'][:]
input_1.close()

input_2 = h5py.File('Plots/NN_single_output/data_files/'+str(args.output2),'r')
set2 = input_2['dataset_1'][:]
input_2.close()

fig1 = plt.figure(1)
bins = np.linspace(0, 1, 50)
plt.hist(set1,bins, alpha=0.5, color='r')
plt.hist(set2,bins, alpha=0.5, color='b')
plt.title('Output of the NN')
plt.ylabel('Occurrences')
plt.xlabel('Output')
plt.legend([str(args.label1), str(args.label2)], loc='upper right')
plt.yscale('log')
#plt.show()
#fig1.savefig('Plots/NN_single_output/'+str(args.label)+'_output.png', bbox_inches='tight')

fig2 = plt.figure(2)
bins = np.linspace(0, 1, 50)
plt.hist(set1,bins, alpha=0.5, color='g', normed=True)
plt.hist(set2,bins, alpha=0.5, color='r', normed=True)
plt.title('Output of the NN')
plt.ylabel('Occurrences')
plt.xlabel('Output')
plt.legend([str(args.label1), str(args.label2)], loc='upper right')
#plt.yscale('log')
plt.show()
fig2.savefig('Plots/Compare_output/'+"out_"+str(args.label1)+'VS'+str(args.label2)+'.png', bbox_inches='tight')

