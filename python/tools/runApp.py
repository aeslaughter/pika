#* This file is part of the MOOSE framework
#* https://www.mooseframework.org
#*
#* All rights reserved, see COPYRIGHT for full restrictions
#* https://github.com/idaholab/moose/blob/master/COPYRIGHT
#*
#* Licensed under LGPL 2.1, please see LICENSE for details
#* https://www.gnu.org/licenses/lgpl-2.1.html

import os, subprocess

##
# Run an application for purposes of performing convergence study
# @param input_file The input file name
#
# Optional:
#   program=<str> The program to execute (pika-oprof)
#   refinements=<int> The number of successive runs to perform with additional uniform refinement (0)
#   mpi=<int> The number of MPI processes to run (1)
#   output_base=<str> The output file base (<input_file>_out)
def runApp(input_file, **kwargs):

  # Get the default base
  default_base, ext = os.path.splitext(input_file)
  default_base += '_out'

  # Extract the optional agruemnts
  refinements = kwargs.pop('refinements', 0)
  mpi = kwargs.pop('mpi', 1)
  program = kwargs.pop('program', os.path.join(os.getenv('PIKA_DIR'), 'pika-oprof'))
  file_base = kwargs.pop('output_base', default_base )

  for i in range(refinements+1):
    if refinements > 0:
      out_name = file_base + '_' + str(i)
    else:
      out_name = file_base
    cmd = ['mpiexec', '-n', str(mpi), program, '-i', input_file,
           'Mesh/uniform_refine='+str(i), 'Outputs/file_base='+out_name]
    print ' '.join(cmd)
    subprocess.call(cmd)
