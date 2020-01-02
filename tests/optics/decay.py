#!/usr/bin/env python
import math
import matplotlib.pyplot as plt
import numpy as np
import mooseutils
import mms

data = mooseutils.PostprocessorReader('decay_out.csv')

fig, ax = plt.subplots(figsize=(10,6), tight_layout=True)
ax.plot(data['h'], data['error'])
fig.savefig('decay.pdf')
