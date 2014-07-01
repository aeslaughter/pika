#! /usr/bin/python


import os, scipy
file = "/home/Users/slauae/Downloads/INL Data/0930_rr_rec_tra_bin_1303.bmp"

image = scipy.misc.imread(file, flatten= 0)

print image
