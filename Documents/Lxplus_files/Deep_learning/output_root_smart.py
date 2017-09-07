import ROOT as rt
rt.gROOT.SetBatch(True)
import numpy as np
import h5py
import sys

# First argument is the name of the code
# Second argument is the input file
# Third argument is the output file

print "Extraction from the file " + str(sys.argv[1])
print "The output file is named " + str(sys.argv[2])
myInput = rt.TFile.Open(str(sys.argv[1]))

tree = myInput.Get("pixelHits/treeAll")

# Input Data
maxent = min(int(sys.argv[3]),tree.GetEntries())
nentries = tree.Draw("1","hit1_layer > 0 && pt >= 2","GOFF",maxent);
dataset = np.empty((nentries,6*6+2))
print "Input data (%d): start" % nentries
entries = 0
plist = []
for i in xrange(maxent):
    tree.GetEntry(i)
    myEvent = [ 
	tree.hit1_layer,tree.hit1_charge_norm,tree.hit1_ratio_charge,tree.hit1_nPixel,tree.hit1_hit_sizeX,tree.hit1_hit_sizeY,
	tree.hit2_layer,tree.hit2_charge_norm,tree.hit2_ratio_charge,tree.hit2_nPixel,tree.hit2_hit_sizeX,tree.hit2_hit_sizeY,
	tree.hit3_layer,tree.hit3_charge_norm,tree.hit3_ratio_charge,tree.hit3_nPixel,tree.hit3_hit_sizeX,tree.hit3_hit_sizeY,
	tree.hit4_layer,tree.hit4_charge_norm,tree.hit4_ratio_charge,tree.hit4_nPixel,tree.hit4_hit_sizeX,tree.hit4_hit_sizeY,
	tree.hit5_layer,tree.hit5_charge_norm,tree.hit5_ratio_charge,tree.hit5_nPixel,tree.hit5_hit_sizeX,tree.hit5_hit_sizeY,
	tree.hit6_layer,tree.hit6_charge_norm,tree.hit6_ratio_charge,tree.hit6_nPixel,tree.hit6_hit_sizeX,tree.hit6_hit_sizeY,	
	tree.pt,tree.eta
	]
    if myEvent[0]==0:  	# if no first hit => dump 
	continue
    if myEvent[36]<2:   # if pt small => dump (probably Background)
	continue
    if entries>=maxent : break;
    for j,v in enumerate(myEvent):
        dataset[entries][j] = v
    #dataset = np.append(dataset,myEvent, axis=0)
    entries += 1 
    if entries %1000==0 : print "%12d  %5.2f%% " % (entries, entries/(0.01*maxent))

print dataset
print "Input data : completed"
print dataset.shape

#Data selection
print "Data selection : start"
data = np.zeros((entries,5))
num = np.array([])

num_bool = dataset[:,[0,6,12,18,24,30]] != 0
num = num_bool.sum(axis=1)
num = np.reshape(num,(entries,1)) # number of hits par tracks
data[:,0] = (dataset[:,1]+dataset[:,7]+dataset[:,13]+dataset[:,19]+dataset[:,25]+dataset[:,31])/num[:,0]
	#data[:,0] contains the sum of the normalized charged 

data[:,1] = dataset[:,2]+dataset[:,8]+dataset[:,14]+dataset[:,20]+dataset[:,26]+dataset[:,32]
	#data[:,1] contains the sum of the ratio of the charge

data[:,2] = dataset[:,3]+dataset[:,9]+dataset[:,15]+dataset[:,21]+dataset[:,27]+dataset[:,33]
        #data[:,2] contains the sum of the number of pixels

data[:,3] = (dataset[:,4]+dataset[:,10]+dataset[:,16]+dataset[:,22]+dataset[:,28]+dataset[:,34])/num[:,0]
        #data[:,3] contains the sum of hit size in X 

data[:,4] = (dataset[:,5]+dataset[:,11]+dataset[:,17]+dataset[:,23]+dataset[:,29]+dataset[:,35])/num[:,0]
        #data[:,4] contains the sum of hit size in Y 
print data.shape
print "Data selection : completed"

print "Output concatenation : start"
output = np.zeros((entries,0))  # See below for scheme

for i in range(0,36):
	if (i%6==0) :  continue
	output = np.c_[output,dataset[:,i]]
output = np.c_[output,dataset[:,37]] #eta

for i in range(0,5):
	output = np.c_[output,data[:,i]]
print output.shape
print "Output concatenation : completed"

print "Output to file : start"

Out = h5py.File(str(sys.argv[2]), 'w')
Out.create_dataset('dataset_1', data=output)
Out.close()

print "Output to file : completed"
print "\n"

# Scheme of the data in the h5 file #

#[0] charge_norm (hit1)	[1] ratio_norm (hit1)	[2] nPixel (hit1)	[3] hit_sizeX (hit1)	[4] hit_sizeY (hit1)
#[5] charge_norm (hit2)	[6] ratio_norm (hit2)	[7] nPixel (hit2)	[8] hit_sizeX (hit2)	[9] hit_sizeY (hit2)
#[10] charge_norm (hit3)[11] ratio_norm (hit3)	[12] nPixel (hit3)	[13] hit_sizeX (hit3)	[14] hit_sizeY (hit3)
#[15] charge_norm (hit4)[16] ratio_norm (hit4)	[17] nPixel (hit4)	[18] hit_sizeX (hit4)	[19] hit_sizeY (hit4)
#[20] charge_norm (hit5)[21] ratio_norm (hit5)	[22] nPixel (hit5)	[23] hit_sizeX (hit5)	[24] hit_sizeY (hit5)
#[25] charge_norm (hit6)[26] ratio_norm (hit6)	[27] nPixel (hit6)	[28] hit_sizeX (hit6)	[29] hit_sizeY (hit6)
#[30] eta
#[31] charge_norm (tot) [32] ratio_charge (tot) [33] nPixel (tot)	[34] hit_sizeX (tot)	[36] hit_sizeY (tot)

