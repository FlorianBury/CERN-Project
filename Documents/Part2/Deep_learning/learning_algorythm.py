import numpy as np
import h5py
import matplotlib.pyplot as plt
from keras.models import Sequential
from keras.layers import Dense, Flatten
from keras.layers import Conv2D, MaxPooling2D, AveragePooling2D
from keras.callbacks import EarlyStopping, ModelCheckpoint
from keras.models import model_from_json
from sklearn.metrics import roc_curve, auc
import sys
import os
import argparse

# Argument parser #

parser = argparse.ArgumentParser(description='Learning algorithm that uses a mixed set of Signal (MC) and background (MC) to train and test')
parser.add_argument("-s","--signal", help="Signal data file -> COMPULSORY")
parser.add_argument("-b","--background", help="Background data file -> COMPULSORY")
parser.add_argument("-l","--label", help="Label of the NN model to be saved -> COMPULSORY")
parser.add_argument("-c","--convolutional", help="Add a convolutional layer as input of the regular NN : '0' or '1' (default '0')", default='0')

args = parser.parse_args()

print "Extraction first set from the file " + str(args.signal)
print "Extraction second set from the file " + str(args.background)
print "Label for ouput files " + str(args.label)
if int(args.convolutional)==0:
	print "No CNN involved"
elif int(args.convolutional)==1:
	print "CNN involved"
else:
	sys.exit("Error in the -c argument")
print "\n\n"

def find_closest(A, target):
    #A must be sorted
    idx = A.searchsorted(target)
    idx = np.clip(idx, 1, len(A)-1)
    left = A[idx-1]
    right = A[idx]
    idx -= target - left < right - target
    return idx

input_MC = h5py.File('h5_files/'+str(args.signal),'r')
set_MC = input_MC['dataset_1'][:]
input_MC.close()

input_data = h5py.File('h5_files/'+str(args.background),'r')
set_data = input_data['dataset_1'][:]
input_data.close()

entries_MC = set_MC.shape[0]
features = set_MC.shape[1] 

#set_data = set_data[:(entries_MC*2),:]

entries_data = set_data.shape[0]

# Create the target vectors and concatenate the complete set #

target_MC = np.ones((entries_MC,1))
target_data = np.zeros((entries_data,1))

set_MC = np.c_[set_MC,target_MC]
set_data = np.c_[set_data,target_data]

set_tot = np.r_[set_MC,set_data]
entries = set_tot.shape[0]

# Shuffle and split the train and test data #
np.random.shuffle(set_tot)
split = np.floor(0.7*entries)
split = split.astype(int)

set_train = set_tot[0:split,0:-1] 	#select 70% as training set
target_train = set_tot[0:split,-1]	#select correspondng target vector 
set_test = set_tot[split:,0:-1] 	#select remaining 30% as test set
target_test = set_tot[split:,-1]	#select correspondng target vector 
print "[INFO] Data ready to enter the neural network"
print set_tot.shape
print ("MC entries : {0}\tMinbias entries : {1}".format(entries_MC,entries_data))
# Architecture of the Neural Network #
print set_train.shape

model = Sequential()
if int(args.convolutional)==1:
	# Reshape #
	set_train_array_hit = set_train[:,:30].reshape(set_train.shape[0],6,5,1)
	set_train_array_global = set_train[:,31:].reshape(set_train.shape[0],1,5,1)
	set_train_supp = np.zeros(set_train.shape[0]*7).reshape(set_train.shape[0],7,1,1) 
	set_train_supp[:,0,0,0] = set_train[:,30] #eta
	set_train = np.concatenate((set_train_array_hit,set_train_array_global),axis=1)
	set_train = np.concatenate((set_train,set_train_supp),axis=2)

	set_test_array_hit = set_test[:,:30].reshape(set_test.shape[0],6,5,1)
	set_test_array_global = set_test[:,31:].reshape(set_test.shape[0],1,5,1)
	set_test_supp = np.zeros(set_test.shape[0]*7).reshape(set_test.shape[0],7,1,1) 
	set_test_supp[:,0,0,0] = set_test[:,30] #eta
	set_test = np.concatenate((set_test_array_hit,set_test_array_global),axis=1)
	set_test = np.concatenate((set_test,set_test_supp),axis=2)
	# CNN #
	model.add(Conv2D(12,kernel_size=(2,5),strides=(1, 1),activation='relu',input_shape=(7,6,1),padding='same', data_format="channels_last"))
	model.add(Conv2D(24, (2,1), activation='relu',padding='same'))
	model.add(Flatten())

	# DNN #
	#model.add(Dense(1000, kernel_initializer="uniform", activation="relu"))	
	#model.add(Dense(700, kernel_initializer="uniform", activation="relu"))	
	model.add(Dense(500, kernel_initializer="uniform", activation="relu"))	
	model.add(Dense(200, kernel_initializer="uniform", activation="relu"))	
	model.add(Dense(100, kernel_initializer="uniform", activation="relu"))	

elif int(args.convolutional)==0:  # just DNN
	model.add(Dense(60, input_dim=features, kernel_initializer="uniform", activation="relu"))

model.add(Dense(50, kernel_initializer="uniform", activation="relu"))
model.add(Dense(40, kernel_initializer="uniform", activation="relu"))
model.add(Dense(30, kernel_initializer="uniform", activation="relu"))
model.add(Dense(20, kernel_initializer="uniform", activation="relu"))
model.add(Dense(1, kernel_initializer="uniform", activation="sigmoid"))

# Callbacks #

early_stopping = EarlyStopping(monitor='val_loss', min_delta=0.001, patience=5, verbose=1, mode='min')
#filepath = 'NN_archi/'+str(args.label)+'.hdf5'  # for different files : -{epoch:02d}_{val_loss:.2f}
#checkpoint = ModelCheckpoint(filepath, monitor='val_loss', verbose=1, save_best_only=True, mode='min', period=1)

Callback_list = [early_stopping]

# Training of the NN #

print "[INFO] Compiling model"
model.compile(loss="binary_crossentropy", optimizer="adam",metrics=["accuracy"])
history = model.fit(set_train, target_train, epochs=100, batch_size=128, verbose=2, validation_data=(set_test,target_test), callbacks=Callback_list)

# Save the model #

model_json = model.to_json()
with open('NN_archi/model-'+str(args.label)+'.json', "w") as json_file:
    json_file.write(model_json)

model.save_weights('NN_archi/model-'+str(args.label)+'.h5')

print("[INFO] Saved model to disk")

# Set up directory for the plots #
path = "/home/florian/Documents/Part2/Deep_learning/Plots/NN_tests/"+args.label
if not os.path.exists(path):
    os.makedirs(path)

# Plot loss and accuracy #

print "[INFO] Starting the plot section"
print(history.history.keys())

# summarize history for accuracy 
fig1, (ax1, ax2) = plt.subplots(2, sharex=False, sharey=True)

ax1.plot(history.history['acc'])
ax1.plot(history.history['val_acc'])
ax1.set_title('Model accuracy')
ax1.set_ylabel('Accuracy')
ax1.legend(['train', 'test'], loc='lower right')

# summarize history for loss #
ax2.plot(history.history['loss'])
ax2.plot(history.history['val_loss'])
ax2.set_title('Model loss')
ax2.set_ylabel('Loss')
ax2.set_xlabel('Epoch')
ax2.legend(['train', 'test'], loc='upper right')
plt.show()
fig1.savefig('Plots/NN_tests/'+str(args.label)+'/'+str(args.label)+'_acc_err.png', bbox_inches='tight')

# ROC curve #

set_pred = model.predict_proba(set_test)  # predicted value of the model => target_test is true value
set_pred = np.squeeze(set_pred)

false_positive_rate, true_positive_rate, thresholds = roc_curve(target_test, set_pred)
roc_auc = auc(false_positive_rate, true_positive_rate)

print ("\nAUC score = {}".format(roc_auc))

fig2 = plt.figure(2)
bins = np.linspace(0, 1, 30)
plt.hist([target_test,set_pred],bins)
plt.title('True and predicted outputs')
plt.ylabel('Occurrences')
plt.xlabel('Output')
plt.legend(['True value','Prediction of the NN'],loc='upper right')
plt.show()
fig2.savefig('Plots/NN_tests/'+str(args.label)+'/'+str(args.label)+'_true_vs_pred.png', bbox_inches='tight')


bkgd_rej = 1-false_positive_rate
sig_eff = true_positive_rate
br_1 = bkgd_rej[find_closest(sig_eff,0.01)]
br_10 = bkgd_rej[find_closest(sig_eff,0.1)]
br_30 = bkgd_rej[find_closest(sig_eff,0.3)]
se_1 = sig_eff[find_closest(false_positive_rate,0.01)]
se_10 = sig_eff[find_closest(false_positive_rate,0.1)]
se_30 = sig_eff[find_closest(false_positive_rate,0.3)]



fig3 = plt.figure(3)
plt.title('Receiver Operating Characteristic')
line, =plt.plot(sig_eff, bkgd_rej, 'b', label='AUC = %0.3f \nSignal efficiency (@B = 0.01) = %0.2f\nSignal efficiency (@B = 0.1) = %0.2f\nSignal efficiency (@B = 0.3) = %0.2f'% (roc_auc,se_1,se_10,se_30))
#plt.plot([0, 1], [1, 0], color='navy', linestyle='--')
plt.legend(handles=[line],loc='lower left')
plt.xlim([0,1])
plt.ylim([0,1])
plt.grid(True)
plt.xlabel('Signal Efficiency')
plt.ylabel('Background Rejection')
plt.show()
fig3.savefig('Plots/NN_tests/'+str(args.label)+'/'+str(args.label)+'_ROC_curve', bbox_inches='tight')

fig4 = plt.figure(4)
plt.title('Receiver Operating Characteristic [logarithmic scale]')
plt.semilogx(sig_eff, bkgd_rej, 'b', label='AUC = %0.15f \nSignal efficiency (background rej = 0.01) = %0.15f\nSignal efficiency (@B = 0.1) = %0.15f\nSignal efficiency (@B = 0.3) = %0.15f\nBackground rejection (signal eff = 0.01) = %0.15f\nBackground rejection (signal eff = 0.1) = %0.15f\nBackground rejection (signal eff = 0.3) = %0.15f\n'% (roc_auc,se_1,se_10,se_30,br_1,br_10,br_30))
#plt.semilogx([0, 1], [0, 1], color='navy', linestyle='--')
plt.legend(loc='lower right')
plt.xlim([-0.1,1.2])
plt.ylim([-0.1,1.2])
plt.xlabel('Signal Efficiency')
plt.ylabel('Background Rejection')
plt.xscale('log')
plt.grid(True)
#plt.show()
#fig4.savefig('Plots/NN_tests/'+str(args.label)+'/'+str(args.label)+'_ROC_curve(log)', bbox_inches='tight')


