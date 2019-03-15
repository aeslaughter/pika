#!/usr/bin/env python
import math
import matplotlib.pyplot as plt
import numpy as np
import mooseutils


vpp = mooseutils.VectorPostprocessorReader('optics_out_line_*.csv')


x = 100 - vpp('radiant_fluence')
y = vpp('y')

depth = 1
kappa = 40
z = np.linspace(0,1,100)
q = 100 * (1 - np.exp(-kappa * (depth-z)))


fig = plt.figure()
ax = fig.add_subplot(1,1,1)

ax.plot(q, z, 'k-')
ax.plot(x,y, 'b-')

plt.show()
