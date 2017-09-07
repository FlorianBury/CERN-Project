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

print "Label of the model " + str(sys.argv[1])
print "Extraction of the signal from " + str(sys.argv[2])
print "Extraction of the background from " + str(sys.argv[3])
print "Label for ouput files " + str(sys.argv[4])

# Input of the data #

input_sig = h5py.File('h5_files/'+str(sys.argv[2]),'r')
signal = input_sig['dataset_1'][:]
input_sig.close()

input_back = h5py.File('h5_files/'+str(sys.argv[3]),'r')
back = input_back['dataset_1'][:]
input_back.close()
back = back[:signal.shape[0],:]

target_sig = np.ones((signal.shape[0],1)) 
target_back = np.zeros((back.shape[0],1)) 

set_sig = np.c_[signal, target_sig] 
set_back = np.c_[back, target_back]

set_tot = np.r_[set_sig,set_back]
np.random.shuffle(set_tot)
data = set_tot[:,:-1]
target = set_tot[:,-1]

print("[INFO] Loaded input file")
print("Size of Signal : {}\tSize of Minbias :{}".format(signal.shape[0],back.shape[0]))


# Load model #

json_file = open('NN_archi/'+ str(sys.argv[1]) +'.json', 'r')
loaded_model_json = json_file.read()
json_file.close()
loaded_model = model_from_json(loaded_model_json)

loaded_model.load_weights('NN_archi/'+str(sys.argv[1])+'.h5')
print("[INFO] Loaded model from disk")
 
# Evaluate loaded model on test data #

loaded_model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])
score = loaded_model.evaluate(data, target, verbose=0)
print("%s: %.2f%%" % (loaded_model.metrics_names[1], score[1]*100))

# Roc curve #

prediction = loaded_model.predict_proba(data) 
prediction = np.squeeze(prediction)

false_positive_rate, true_positive_rate, thresholds = roc_curve(target, prediction)
roc_auc = auc(false_positive_rate, true_positive_rate)

print ("AUC score : {}".format(roc_auc))

# Plot #

fig1 = plt.figure(1)
plt.title('Receiver Operating Characteristic')
plt.plot(false_positive_rate, true_positive_rate, 'b', label='AUC = %0.15f'% roc_auc)
plt.plot([0, 1], [0, 1], color='navy', linestyle='--')
plt.legend(loc='lower right')
plt.xlim([-0.1,1.2])
plt.ylim([-0.1,1.2])
plt.ylabel('True Positive Rate')
plt.xlabel('False Positive Rate')
#plt.show()
fig1.savefig('Plots/NN_cross/'+str(sys.argv[4])+'_ROC_curve.png', bbox_inches='tight')

fig2 = plt.figure(2)
plt.title('Receiver Operating Characteristic [logarithmic scale]')
plt.semilogx(false_positive_rate, true_positive_rate, 'b', label='AUC = %0.15f1'% roc_auc)
plt.legend(loc='lower right')
plt.xlim([-0.1,1.2])
plt.ylim([-0.1,1.2])
plt.ylabel('True Positive Rate')
plt.xlabel('False Positive Rate')
plt.xscale('log')
plt.grid(True)
#plt.show()
fig2.savefig('Plots/NN_cross/'+str(sys.argv[4])+'_ROC_curve(log).png', bbox_inches='tight')

fig3 = plt.figure(3)
bins = np.linspace(0, 1, 30)
plt.hist([target,prediction],bins)
plt.title('True and predicted outputs')
plt.ylabel('Occurrences')
plt.xlabel('Output')
plt.legend(['True value','Prediction of the NN'],loc='upper right')
#plt.show()
fig3.savefig('Plots/NN_cross/'+str(sys.argv[4])+'_true_vs_pred.png', bbox_inches='tight')

print "\n"
