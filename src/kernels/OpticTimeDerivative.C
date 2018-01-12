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

#include "OpticTimeDerivative.h"

registerMooseObject("PikaApp", OpticTimeDerivative);

template<>
InputParameters validParams<OpticTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addParam<MaterialPropertyName>("light_speed", "light_speed", "The speed of light [m/s].");
  return params;
}

OpticTimeDerivative::OpticTimeDerivative(const InputParameters & parameters) :
    TimeDerivative(parameters),
    _light_speed(getMaterialProperty<Real>("light_speed"))
{
}

Real
OpticTimeDerivative::computeQpResidual()
{
  return 1. / _light_speed[_qp] * TimeDerivative::computeQpResidual();
}

Real
OpticTimeDerivative::computeQpJacobian()
{
  return 1. / _light_speed[_qp] * TimeDerivative::computeQpJacobian();
}
