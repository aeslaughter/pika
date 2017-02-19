#include "CoupledDiffusion.h"

template<>
InputParameters validParams<CoupledDiffusion>()
{
  MooseEnum component("x=0 y=1 z=2");

  InputParameters params = validParams<Diffusion>();
  params.addCoupledVar("velocity", "The velocity variable.");
  return params;
}

CoupledDiffusion::CoupledDiffusion(const InputParameters & parameters) :
    Diffusion(parameters),
    _velocity(coupledValue("velocity"))
{
}

Real
CoupledDiffusion::computeQpResidual()
{
  return _velocity[_qp] * Diffusion::computeQpResidual();
}

Real
CoupledDiffusion::computeQpJacobian()
{
  return _velocity[_qp] * Diffusion::computeQpJacobian();
}
