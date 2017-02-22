#include "MooseMesh.h"

#include "MassBalanceDivergence.h"


template<>
InputParameters validParams<MassBalanceDivergence>()
{
  MooseEnum component("x=0 y=1 z=2");

  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("velocities", "The deformation velocity variables.");
  return params;
}

MassBalanceDivergence::MassBalanceDivergence(const InputParameters & parameters) :
    Kernel(parameters),
    _mesh_dim(_mesh.dimension()),
    _deformation_velocities(_mesh_dim)
{
  if (_deformation_velocities.size() != getParam<std::vector<VariableName>>("velocities").size())
    mooseError2("The number of 'velocities' provided must match the problem dimension: ", LIBMESH_DIM);

  for (unsigned int i = 0; i < _mesh_dim; ++i)
    _deformation_velocities[i] = getVar("velocities", i);


}

Real
MassBalanceDivergence::computeQpResidual()
{
  for (unsigned int i = 0; i < _mesh_dim; ++i)
    _velocity(i) = _deformation_velocities[i]->sln()[_qp];

  return -_grad_test[_qp][_i] * _u[_qp] * _velocity;
}

Real
MassBalanceDivergence::computeQpJacobian()
{
  for (unsigned int i = 0; i < _mesh_dim; ++i)
    _velocity(i) = _deformation_velocities[i]->sln()[_qp];
  return -_grad_test[_qp][_i] * _phi[_qp][_j] * _velocity;
}
