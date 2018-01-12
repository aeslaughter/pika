#* This file is part of the MOOSE framework
#* https://www.mooseframework.org
#*
#* All rights reserved, see COPYRIGHT for full restrictions
#* https://github.com/idaholab/moose/blob/master/COPYRIGHT
#*
#* Licensed under LGPL 2.1, please see LICENSE for details
#* https://www.gnu.org/licenses/lgpl-2.1.html

import csv

##
# Reads CSV into a multidimensional list
# @param filename The filename to read, including the *.csv
# return The header and data lists
#
# Note, this function assumes that the first row is the header, as
# is the case for postprocessor *.csv output
def readCSV(filename):
  with open(filename, 'rb') as f:
    reader = csv.reader(f)
    header = []
    data = []
    for row in reader:
      # Do not include blank rows
      if len(row) == 0:
        continue

      # First row is header
      if reader.line_num == 1:
        header = row
      else:
        data.append(row)

  return header, data
