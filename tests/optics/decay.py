#!/usr/bin/env python
import math
import matplotlib.pyplot as plt
import numpy as np
import mooseutils

data = mooseutils.PostprocessorReader('decay_out.csv')
#fig = mooseutils.ConvergencePlot(np.sqrt(data['dofs']), data['error'], xlabel='sqrt(ndofs)', ylabel='L2 Error')
fig = mooseutils.ConvergencePlot(data['h'], data['error'], xlabel='Element Length', ylabel='L2 Error')
#fig.save('convergence.png')
fig.show()
