#include "libmesh/libmesh_common.h"

#include "MooseMesh.h"

#include "CoupledDiffusion.h"

template<>
InputParameters validParams<CoupledDiffusion>()
{
  MooseEnum component("x=0 y=1 z=2");

  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("velocities", "The velocity variables.");
  return params;
}

CoupledDiffusion::CoupledDiffusion(const InputParameters & parameters) :
    Kernel(parameters),
    _mesh_dim(_mesh.dimension()),
    _deformation_velocities(_mesh_dim)
{
  if (_deformation_velocities.size() != getParam<std::vector<VariableName>>("velocities").size())
    mooseError2("The number of 'velocities' provided must match the problem dimension: ", _mesh_dim);

  for (unsigned int i = 0; i < _mesh_dim; ++i)
    _deformation_velocities[i] = getVar("velocities", i);
}

Real
CoupledDiffusion::computeQpResidual()
{
  for (unsigned int i = 0; i < _mesh_dim; ++i)
    _velocity(i) = _deformation_velocities[i]->sln()[_qp];

  return _grad_test[_qp][_i] * _velocity * _u[_qp];
}

Real
CoupledDiffusion::computeQpJacobian()
{
  for (unsigned int i = 0; i < _mesh_dim; ++i)
    _velocity(i) = _deformation_velocities[i]->sln()[_qp];

  return _grad_test[_qp][_i] * _velocity * _phi[_qp][_j];
}
