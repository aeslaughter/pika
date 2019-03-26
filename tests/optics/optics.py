#!/usr/bin/env python
import math
import matplotlib.pyplot as plt
import numpy as np
import mooseutils


vpp = mooseutils.VectorPostprocessorReader('decay_out_line_*.csv')


x = vpp('u')
y = vpp('x')

print y

depth = 1
kappa = 1
z = np.linspace(0,2,100)
q = np.exp(-z)


fig = plt.figure()
ax = fig.add_subplot(1,1,1)

ax.plot(q, z, 'k-')
ax.plot(x,y, 'b-')

plt.show()
