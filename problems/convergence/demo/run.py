#* This file is part of the MOOSE framework
#* https://www.mooseframework.org
#*
#* All rights reserved, see COPYRIGHT for full restrictions
#* https://github.com/idaholab/moose/blob/master/COPYRIGHT
#*
#* Licensed under LGPL 2.1, please see LICENSE for details
#* https://www.gnu.org/licenses/lgpl-2.1.html

#! /usr/bin/python
# A simple demonstration of the convergence tools in Pika, the
# executable is slightly modified version of Example 14 of Moose.

# Import necessary packages
import sys, os
import matplotlib.pyplot, numpy
from pylab import *


# Load Pika Python tools
sys.path.append(os.path.join(os.getenv('PIKA_DIR'), 'python'))
from tools import *

# Run the problem; this problem is a Steady calculations so adaptivity
# is used in a single run to perform the analysis
#runApp('demo.i', mpi=4)

# Extract the data from the Postprocessor CSV output (out.csv)
#x, y = extractPostprocessorData('out')
#plt = ConvergencePlot(sqrt(x),y, xlabel='sqrt(ndofs)', ylabel='L2_error')
#plt.fit()

x, y = extractPostprocessorData('out', x = 'h_max', xlabel='Element Size', ylabel='L2_error')
plt2 = ConvergencePlot(x,y)
plt2.fit()

show()
