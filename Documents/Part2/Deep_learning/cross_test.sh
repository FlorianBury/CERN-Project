#!/bin/bash
python test_model.py model-train_10cm out_10.h5 out_minbias.h5 train10_test10 &&
python test_model.py model-train_10cm out_3.h5 out_minbias.h5 train10_test3 &&
python test_model.py model-train_10cm out_30.h5 out_minbias.h5 train10_test30 &&
python test_model.py model-train_3cm out_10.h5 out_minbias.h5 train3_test10 &&
python test_model.py model-train_3cm out_3.h5 out_minbias.h5 train3_test3 &&
python test_model.py model-train_3cm out_30.h5 out_minbias.h5 train3_test30 &&
python test_model.py model-train_30cm out_10.h5 out_minbias.h5 train30_test10 &&
python test_model.py model-train_30cm out_3.h5 out_minbias.h5 train30_test3 &&
python test_model.py model-train_30cm out_30.h5 out_minbias.h5 train30_test30
