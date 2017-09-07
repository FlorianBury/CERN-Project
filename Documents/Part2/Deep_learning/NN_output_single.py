import numpy as np
import h5py
import matplotlib.pyplot as plt
from keras.models import Sequential
from keras.layers import Dense
from keras.callbacks import EarlyStopping, ModelCheckpoint
from keras.models import model_from_json
from sklearn.metrics import roc_curve, auc
import sys
import os
import argparse

# Argument parser #

parser = argparse.ArgumentParser(description='Prints the output of the NN for a given model and a given set of data.\nAlso provides the plots of the differents features for a given cut on the NN output')
parser.add_argument("-m","--model", help="Model of the NN -> COMPULSORY")
parser.add_argument("-i","--input_file", help="Input data file -> COMPULSORY")
parser.add_argument("-l","--label", help="Label of the NN model -> COMPULSORY")
parser.add_argument("-cmin","--minimal_cut", help="Minimal cut of the NN output applied to the plots -> OPTIONAL",default='None')
parser.add_argument("-cmax","--maximal_cut", help="Maximal cut of the NN output applied to the plots -> OPTIONAL",default='None')
parser.add_argument("-b","--background", help="Finds the cut such as ...%% Background rejection -> OPTIONAL",default='None')
parser.add_argument("-c","--convolutional", help="Changes the form of the data to enter the convolutional network -> OPTIONAL : 0 (default) or 1",default='0')

args = parser.parse_args()


print "\nLabel of the model : " + str(args.model)
print "Extraction of the data from : " + str(args.input_file)
print "Label for ouput files : " + str(args.label)
if args.minimal_cut != 'None' and args.maximal_cut != 'None':
	print "Minimal cut = " + str(args.minimal_cut)
	print "Maximal cut  = " + str(args.maximal_cut)
if args.background != 'None':
	print "Background rejection rate = "+str(args.background)+"%"
if int(args.convolutional) == 1:
	print "CNN involved"
if int(args.convolutional) != 0 and int(args.convolutional) != 1:
	print "Error in -c"
print 	


# Input of the data #

input_data = h5py.File('h5_files/'+str(args.input_file),'r')
data = input_data['dataset_1'][:2000000,:]
input_data.close()

if int(args.convolutional) == 1:   #shapes the data for the convolutional network
        data_array_hit = data[:,:30].reshape(data.shape[0],6,5,1)
        data_array_global = data[:,31:].reshape(data.shape[0],1,5,1)
        data_supp = np.zeros(data.shape[0]*7).reshape(data.shape[0],7,1,1) 
        data_supp[:,0,0,0] = data[:,30] #eta
        data = np.concatenate((data_array_hit,data_array_global),axis=1)
        data = np.concatenate((data,data_supp),axis=2)


print("[INFO] Loaded input file")
print("Size of data : {}".format(data.shape[0]))

# Load model #

json_file = open('NN_archi/'+ str(args.model) +'.json', 'r')
loaded_model_json = json_file.read()
json_file.close()
loaded_model = model_from_json(loaded_model_json)

loaded_model.load_weights('NN_archi/'+str(args.model)+'.h5')
print("[INFO] Loaded model from disk")

# Compute the output of the NN #
prediction = loaded_model.predict_proba(data) 
prediction = np.squeeze(prediction)

fig1 = plt.figure(1)
bins = np.linspace(0, 1, 50)
plt.hist(prediction,bins)
plt.title('Output of the NN')
plt.ylabel('Occurrences')
plt.xlabel('Output')
#plt.yscale('log')
fig1.savefig('Plots/NN_single_output/Plots/'+str(args.label)+'_output.png', bbox_inches='tight')

# Writing the NN output #

output = h5py.File('Plots/NN_single_output/data_files/'+str(args.label)+'_output.h5' ,'w')
output.create_dataset('dataset_1', data=prediction)
output.close()

# Check if the cut options are enabled #

if args.minimal_cut != 'None' and args.maximal_cut != 'None':
	# Create directory

	path = "/home/florian/Documents/Part2/Deep_learning/Plots/NN_single_output/Plots/output_of_"+args.label+'_Cut_'+str(args.minimal_cut)+'<out<'+str(args.maximal_cut)
	if not os.path.exists(path):
	    	os.makedirs(path)
	# Concatenating and cutting "

	set_full = np.c_[data, prediction]  # contains input and output
	check_cut_min = set_full[:,-1]>float(args.minimal_cut) 
	check_cut_max = set_full[:,-1]<float(args.maximal_cut)
	check_cut = np.logical_and(check_cut_min,check_cut_max)

	# Extract the input features with the cut #

	charge_norm = set_full[:,0]+set_full[:,5]+set_full[:,10]+set_full[:,15]+set_full[:,20]+set_full[:,25];
	ratio_charge = set_full[:,1]+set_full[:,6]+set_full[:,11]+set_full[:,16]+set_full[:,21]+set_full[:,26];
	nPixel = set_full[:,2]+set_full[:,7]+set_full[:,12]+set_full[:,17]+set_full[:,22]+set_full[:,27];
	sizeX = set_full[:,3]+set_full[:,8]+set_full[:,13]+set_full[:,18]+set_full[:,23]+set_full[:,28];
	sizeY = set_full[:,4]+set_full[:,9]+set_full[:,14]+set_full[:,19]+set_full[:,24]+set_full[:,29];
	
	charge_norm_cut = charge_norm[check_cut]
	ratio_charge_cut = ratio_charge[check_cut]
	nPixel_cut = nPixel[check_cut]
	sizeX_cut = sizeX[check_cut]
	sizeY_cut = sizeY[check_cut]
	
	# Plot the inputs with the cut #
	
	fig2 = plt.figure(2)
	plt.hist(charge_norm, 40, normed=True, range=(0,400000), alpha=0.5, color='g')
	plt.hist(charge_norm_cut, 40, normed=True,  range=(0,400000), alpha=0.5, color='r')
	plt.title('Normalised charge with cut : '+args.minimal_cut+" < Output < "+args.maximal_cut)
	plt.ylabel('Occurrences')
	plt.xlabel('Normalized charge')
	plt.legend(['No cut', 'Cut'], loc='upper right')
	fig2.savefig(path+'/'+str(args.label)+'_charge_norm.png', bbox_inches='tight')
	
	
	fig3 = plt.figure(3)
	plt.hist(ratio_charge, 40, normed=True, range=(0,40), alpha=0.5, color='g')
	plt.hist(ratio_charge_cut, 40, normed=True, range=(0,40), alpha=0.5, color='r')
	plt.title('Ratio of the charge with cut : '+args.minimal_cut+" < Output < "+args.maximal_cut)
	plt.ylabel('Occurrences')
	plt.xlabel('Charge ratio')
	plt.legend(['No cut', 'Cut'], loc='upper right')
	fig3.savefig(path+'/'+str(args.label)+'_ratio_charge.png', bbox_inches='tight')
	
	fig4 = plt.figure(4)
	plt.hist(nPixel,40, range=(0,40),  normed=True, alpha=0.5, color='g')
	plt.hist(nPixel_cut,40, range=(0,40), normed=True, alpha=0.5, color='r')
	plt.title('Number of pixel with cut : '+args.minimal_cut+" < Output < "+args.maximal_cut)
	plt.ylabel('Occurrences')
	plt.xlabel('Number of pixels')
	plt.legend(['No cut', 'Cut'], loc='upper right')
	fig4.savefig(path+'/'+str(args.label)+'_nPixel.png', bbox_inches='tight')

	fig5 = plt.figure(5)
	plt.hist(sizeX,30, normed=True, range=(0,30), alpha=0.5, color='g')
	plt.hist(sizeX_cut,30, normed=True, range=(0,30), alpha=0.5, color='r')
	plt.title('Size in X of the cluster with cut : '+args.minimal_cut+" < Output < "+args.maximal_cut)
	plt.ylabel('Occurrences')
	plt.xlabel('Size X')
	plt.legend(['No cut', 'Cut'], loc='upper right')
	fig5.savefig(path+'/'+str(args.label)+'_sizeX.png', bbox_inches='tight')
	
	fig6 = plt.figure(6)
	plt.hist(sizeY,40, normed=True, range=(0,40), alpha=0.5, color='g')
	plt.hist(sizeY_cut,40, normed=True, range=(0,40), alpha=0.5, color='r')
	plt.title('Size in Y of the cluster with cut : '+args.minimal_cut+" < Output < "+args.maximal_cut)
	plt.ylabel('Occurrences')
	plt.xlabel('Normalized charge')
	plt.legend(['No cut', 'Cut'], loc='upper right')
	fig6.savefig(path+'/'+str(args.label)+'_sizeY.png', bbox_inches='tight')
	
	#plt.show() # show all the plots
	
# Find the cut for 99% Background rejection on MC minbias %
if args.background != 'None':
	pediction_sorted = np.sort(prediction,kind='mergesort')
	cut_index = int(np.floor(float(args.background)*prediction.size/100))
	cut_reject = pediction_sorted[cut_index]
	print "\n\n\t%2.2f%% of background rejection => cut at output = %1.5f" %(float(args.background),cut_reject)
print 
