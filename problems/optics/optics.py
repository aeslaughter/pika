#!/usr/bin/env python
import math
import matplotlib.pyplot as plt
import numpy as np
import mooseutils
import mms

vpp = mooseutils.VectorPostprocessorReader('optics_out_center_*.csv')


x = vpp['T'] - 273.15
y = vpp['y']


fig = plt.figure()
ax = fig.add_subplot(1,1,1)

ax.plot(x, y, 'b-')

plt.savefig('optics.pdf')
#plt.show()
