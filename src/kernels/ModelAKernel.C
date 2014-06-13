/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "ModelAKernel.h"

template<>
InputParameters validParams<ModelAKernel>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<std::string>("m", "Provide a material property to multiply the provided function by");
  return params;
}

ModelAKernel::ModelAKernel(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _m(getMaterialProperty<Real>(getParam<std::string>("m")))
{
}

Real
ModelAKernel::computeQpResidual()
{
  return _test[_qp][_i] * _u[_qp] * (1 - _u[_qp])*_m[_qp];
}
