#!/usr/bin/python
#* This file is part of the MOOSE framework
#* https://www.mooseframework.org
#*
#* All rights reserved, see COPYRIGHT for full restrictions
#* https://github.com/idaholab/moose/blob/master/COPYRIGHT
#*
#* Licensed under LGPL 2.1, please see LICENSE for details
#* https://www.gnu.org/licenses/lgpl-2.1.html

from sympy import *
from sympy.utilities.codegen import codegen
init_printing()

# This script checks the Jacobian of the phase transition term in Eq. (33)

phi =symbols('phi')

#constants
lam= symbols('lambda')
u = symbols('u')
u_eq = symbols('u_eq')
term3 =-lam*(u-u_eq)*((1-phi**2)**2)

#Print out equation
print 'Residual'
pprint (term3)

print '\n'
print '  jacobian d(Term4)/dphi = \n'
pprint(diff(term3,phi))
print '\n'

print ' offDiagonal  d(Term4)/du = \n'
pprint(diff(term3,u))
print '\n'


'''
#Generate the C/C++ version of the code.
print('Equation 34 Code : \n')
[(c_name, c_code), (h_name, c_header)] = codegen(
         ("f", hx), "C", "test", header=False, empty=False)
print(c_code)
print('\n')


#Generate C/C++ code for term 4
print('-dPhi_dt term Code : \n')
[(c_name, c_code), (h_name, c_header)] = codegen(
         ("f", -term3), "C", "test", header=False, empty=False)
print(c_code)
print('\n')
'''
