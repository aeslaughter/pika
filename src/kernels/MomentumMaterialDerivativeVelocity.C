#include "MooseMesh.h"
#include "MomentumMaterialDerivativeVelocity.h"

template<>
InputParameters validParams<MomentumMaterialDerivativeVelocity>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<MaterialPropertyName>("density", "density", "The material property for the density.");
  params.addRequiredCoupledVar("velocities", "The deformation velocity variables.");
  return params;
}

MomentumMaterialDerivativeVelocity::MomentumMaterialDerivativeVelocity(const InputParameters & parameters) :
    Kernel(parameters),
    _mesh_dim(_mesh.dimension()),
    _deformation_velocities(_mesh_dim),
    _density(getMaterialProperty<Real>("density"))
{
  if (_deformation_velocities.size() != getParam<std::vector<VariableName>>("velocities").size())
    mooseError2("The number of 'velocities' provided must match the problem dimension: ", LIBMESH_DIM);

    for (unsigned int i = 0; i < _mesh_dim; ++i)
      _deformation_velocities[i] = getVar("velocities", i);

}

Real
MomentumMaterialDerivativeVelocity::computeQpResidual()
{
  for (unsigned int i = 0; i < _mesh_dim; ++i)
    _velocity(i) = _deformation_velocities[i]->sln()[_qp];
  return -_density[_qp] * _grad_test[_qp][_i] * _u[_qp] * _velocity;
}

Real
MomentumMaterialDerivativeVelocity::computeQpJacobian()
{
  for (unsigned int i = 0; i < _mesh_dim; ++i)
    _velocity(i) = _deformation_velocities[i]->sln()[_qp];
  return -_density[_qp] * _grad_test[_qp][_i] * _phi[_qp][_j] * _velocity;}
