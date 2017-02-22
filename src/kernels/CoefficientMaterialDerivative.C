
#include "MooseMesh.h"


#include "CoefficientMaterialDerivative.h"

template<>
InputParameters validParams<CoefficientMaterialDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addRequiredCoupledVar("velocities", "The deformation velocity variables.");
  params.addParam<MaterialPropertyName>("coefficient", 1, "Material property coefficient for the Material Derivative.");
  return params;
}

CoefficientMaterialDerivative::CoefficientMaterialDerivative(const InputParameters & parameters) :
    TimeDerivative(parameters),
    _mesh_dim(_mesh.dimension()),
    _deformation_velocities(_mesh_dim),
    _coefficient(getMaterialProperty<Real>("coefficient"))
{

  if (_deformation_velocities.size() != getParam<std::vector<VariableName>>("velocities").size())
    mooseError2("The number of 'velocities' provided must match the problem dimension: ", LIBMESH_DIM);


  for (unsigned int i = 0; i < _mesh_dim; ++i)
    _deformation_velocities[i] = getVar("velocities", i);
}

Real
CoefficientMaterialDerivative::computeQpResidual()
{

  for (unsigned int i = 0; i < _mesh_dim; ++i)
    _velocity(i) = _deformation_velocities[i]->sln()[_qp];

  return _coefficient[_qp] * (TimeDerivative::computeQpResidual() + _test[_qp][_i] * _grad_u[_qp] * _velocity);


}

Real
CoefficientMaterialDerivative::computeQpJacobian()
{
  for (unsigned int i = 0; i < _mesh_dim; ++i)
    _velocity(i) = _deformation_velocities[i]->sln()[_qp];

  return _coefficient[_qp] * (TimeDerivative::computeQpJacobian() + _test[_qp][_i] * _grad_phi[_qp][_j] * _velocity);
}
