#include "VelocityDeformation.h"

template<>
InputParameters validParams<VelocityDeformation>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("velocity", "The velocity variable utilized to compute the deformation.");
  return params;
}

VelocityDeformation::VelocityDeformation(const InputParameters & parameters) :
    AuxKernel(parameters),
    _velocity(coupledValue("velocity"))
{
}

Real
VelocityDeformation::computeValue()
{
  return _u_old[_qp] + _velocity[_qp] * _dt;
}
