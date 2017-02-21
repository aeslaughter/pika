#include "MomentumTimeDerivative.h"

template<>
InputParameters validParams<MomentumTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addParam<MaterialPropertyName>("density", "density", "The material property for the density.");
  return params;
}

MomentumTimeDerivative::MomentumTimeDerivative(const InputParameters & parameters) :
    TimeDerivative(parameters),
    _density(getMaterialProperty<Real>("density"))
{
}

Real
MomentumTimeDerivative::computeQpResidual()
{
  return _density[_qp] * TimeDerivative::computeQpResidual();
}

Real
MomentumTimeDerivative::computeQpJacobian()
{
  return _density[_qp] * TimeDerivative::computeQpJacobian();
}
