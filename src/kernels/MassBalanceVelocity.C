#include "MassBalanceVelocity.h"

template<>
InputParameters validParams<MassBalanceVelocity>()
{
  MooseEnum component("x=0 y=1 z=2");

  InputParameters params = validParams<Kernel>();
  params.addParam<MooseEnum>("component", component, "The compoment to operate against.");
  params.addCoupledVar("velocity", "The velocity variable.");
  return params;
}

MassBalanceVelocity::MassBalanceVelocity(const InputParameters & parameters) :
    Kernel(parameters),
    _grad_velocity(coupledGradient("velocity")),
    _component(getParam<MooseEnum>("component"))
{
}

Real
MassBalanceVelocity::computeQpResidual()
{
  return _test[_i][_qp] * _u[_qp] * _grad_velocity[_qp](_component);
}

Real
MassBalanceVelocity::computeQpJacobian()
{
  return 0;
}
