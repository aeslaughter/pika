/**********************************************************************************/
/*                  Pika: Phase field snow micro-structure model                  */
/*                                                                                */
/*                     (C) 2014 Battelle Energy Alliance, LLC                     */
/*                              ALL RIGHTS RESERVED                               */
/*                                                                                */
/*                   Prepared by Battelle Energy Alliance, LLC                    */
/*                      Under Contract No. DE-AC07-05ID14517                      */
/*                      With the U. S. Department of Energy                       */
/**********************************************************************************/

#pragma once

// MOOSE includes
#include "TimeDerivative.h"

// Forward declerations
class OpticTimeDerivative;

template<>
InputParameters validParams<OpticTimeDerivative>();

class OpticTimeDerivative :
  public TimeDerivative
{
public:
  OpticTimeDerivative(const InputParameters & parameters);

protected:
  Real computeQpResidual();
  Real computeQpJacobian();

private:

  const MaterialProperty<Real> & _light_speed;
};
