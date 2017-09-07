import numpy as np
import h5py
import sys

# Import the files to combine #
input_200_3 = h5py.File('h5_files/out_200_3.h5','r')
input_200_10 = h5py.File('h5_files/out_200_10.h5','r')
input_200_30 = h5py.File('h5_files/out_200_30.h5','r')

input_300_3 = h5py.File('h5_files/out_300_3.h5','r')
input_300_10 = h5py.File('h5_files/out_300_10.h5','r')
input_300_30 = h5py.File('h5_files/out_300_30.h5','r')

input_400_3 = h5py.File('h5_files/out_400_3.h5','r')
input_400_10 = h5py.File('h5_files/out_400_10.h5','r')
input_400_30 = h5py.File('h5_files/out_400_30.h5','r')

input_500_3 = h5py.File('h5_files/out_500_3.h5','r')
input_500_10 = h5py.File('h5_files/out_500_10.h5','r')
input_500_30 = h5py.File('h5_files/out_500_30.h5','r')

set_200_3 = input_200_3['dataset_1'][:]
set_200_10 = input_200_10['dataset_1'][:]
set_200_30 = input_200_30['dataset_1'][:]

set_300_3 = input_300_3['dataset_1'][:]
set_300_10 = input_300_10['dataset_1'][:]
set_300_30 = input_300_30['dataset_1'][:]

set_400_3 = input_400_3['dataset_1'][:]
set_400_10 = input_400_10['dataset_1'][:]
set_400_30 = input_400_30['dataset_1'][:]

set_500_3 = input_500_3['dataset_1'][:]
set_500_10 = input_500_10['dataset_1'][:]
set_500_30 = input_500_30['dataset_1'][:]

input_200_3.close() 
input_200_10.close()
input_200_30.close()

input_300_3.close() 
input_300_10.close()
input_300_30.close()

input_400_3.close() 
input_400_10.close()
input_400_30.close()

input_500_3.close() 
input_500_10.close()
input_500_30.close()

features = set_200_3.shape[1]

print "Input files : Done"

# Combining files #

out_200 = np.zeros((0,features))
out_300 = np.zeros((0,features))
out_400 = np.zeros((0,features))
out_500 = np.zeros((0,features))
out_3 = np.zeros((0,features))
out_10 = np.zeros((0,features))
out_30 = np.zeros((0,features))

out_200 = np.r_[out_200,set_200_3]
out_200 = np.r_[out_200,set_200_10]
out_200 = np.r_[out_200,set_200_30]

out_300 = np.r_[out_300,set_300_3]
out_300 = np.r_[out_300,set_300_10]
out_300 = np.r_[out_300,set_300_30]

out_400 = np.r_[out_400,set_400_3]
out_400 = np.r_[out_400,set_400_10]
out_400 = np.r_[out_400,set_400_30]

out_500 = np.r_[out_500,set_500_3]
out_500 = np.r_[out_500,set_500_10]
out_500 = np.r_[out_500,set_500_30]

out_3 = np.r_[out_3,set_200_3]
out_3 = np.r_[out_3,set_300_3]
out_3 = np.r_[out_3,set_400_3]
out_3 = np.r_[out_3,set_500_3]

out_10 = np.r_[out_10,set_200_10]
out_10 = np.r_[out_10,set_300_10]
out_10 = np.r_[out_10,set_400_10]
out_10 = np.r_[out_10,set_500_10]

out_30 = np.r_[out_30,set_200_30]
out_30 = np.r_[out_30,set_300_30]
out_30 = np.r_[out_30,set_400_30]
out_30 = np.r_[out_30,set_500_30]

print "Combining data : Done"
print ("Shape of 200 GeV : {}".format(out_200.shape))
print ("Shape of 300 GeV : {}".format(out_300.shape))
print ("Shape of 400 GeV : {}".format(out_400.shape))
print ("Shape of 500 GeV : {}".format(out_500.shape))
print ("Shape of 3 cm : {}".format(out_3.shape))
print ("Shape of 10 cm : {}".format(out_10.shape))
print ("Shape of 30 cm : {}".format(out_30.shape))


# Output of the combined files #

Output_200 = h5py.File('h5_files/out_200.h5', 'w')
Output_200.create_dataset('dataset_1', data=out_200)
Output_200.close()

Output_300 = h5py.File('h5_files/out_300.h5', 'w')
Output_300.create_dataset('dataset_1', data=out_300)
Output_300.close()

Output_400 = h5py.File('h5_files/out_400.h5', 'w')
Output_400.create_dataset('dataset_1', data=out_400)
Output_400.close()

Output_500 = h5py.File('h5_files/out_500.h5', 'w')
Output_500.create_dataset('dataset_1', data=out_500)
Output_500.close()

Output_3 = h5py.File('h5_files/out_3.h5', 'w')
Output_3.create_dataset('dataset_1', data=out_3)
Output_3.close()

Output_10 = h5py.File('h5_files/out_10.h5', 'w')
Output_10.create_dataset('dataset_1', data=out_10)
Output_10.close()

Output_30 = h5py.File('h5_files/out_30.h5', 'w')
Output_30.create_dataset('dataset_1', data=out_30)
Output_30.close()

print "Output files : done"
