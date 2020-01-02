#!/usr/bin/env python
import math
import matplotlib.pyplot as plt
import numpy as np
import mooseutils
import mms

def u_a(u_eff, alpha, g):
    return u_eff * math.sqrt(1/(3*(1 + alpha/(1-alpha) - g * alpha/(1-alpha))))

def u_s(u_eff, alpha, g):
    return alpha*u_a(u_eff, alpha, g)/(1-alpha)

def D(u_eff, alpha, g):
    return 1/(3*(u_a(u_eff, alpha, g) + (1-g)*u_s(u_eff, alpha, g)))


N = 20
depth = 0.25
u_eff = 40
alpha = 0.94
q_in = 100
g = 0



print("u_a = ", u_a(u_eff, alpha, g))
print("u_s = ", u_s(u_eff, alpha, g))
print("D = ", D(u_eff, alpha, g))


vpp = mooseutils.VectorPostprocessorReader('decay_out_line_*.csv')


x = vpp['u']
y = vpp['x']


z = np.linspace(0,depth,N)
q = q_in*np.exp(-u_eff*z)


fig = plt.figure()
ax = fig.add_subplot(1,1,1)

ax.plot(q, z, 'k-', marker='o')
ax.plot(x, y, 'b-')

plt.savefig('decay.pdf')
#plt.show()
