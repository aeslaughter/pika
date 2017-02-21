#include "MomentumMaterialDerivativeTime.h"

template<>
InputParameters validParams<MomentumMaterialDerivativeTime>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addParam<MaterialPropertyName>("density", "density", "The material property for the density.");
  return params;
}

MomentumMaterialDerivativeTime::MomentumMaterialDerivativeTime(const InputParameters & parameters) :
    TimeDerivative(parameters),
    _density(getMaterialProperty<Real>("density"))
{
}

Real
MomentumMaterialDerivativeTime::computeQpResidual()
{
  return _density[_qp] * TimeDerivative::computeQpResidual();
}

Real
MomentumMaterialDerivativeTime::computeQpJacobian()
{
  return _density[_qp] * TimeDerivative::computeQpJacobian();
}
