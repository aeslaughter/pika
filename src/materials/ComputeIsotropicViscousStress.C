/**********************************************************************************/
/*                  Pika: Phase field snow micro-structure model                  */
/*                                                                                */
/*                     (C) 2014 Battelle Energy Alliance, LLC                     */
/*                              ALL RIGHTS RESERVED                               */
/*                                                                                */
/*                   Prepared by Battelle Energy Alliance, LLC                    */
/*                      Under Contract No. DE-AC07-05ID14517                      */
/*                      With the U. S. Department of Energy                       */
/**********************************************************************************/

// MOOSE includes
#include "RankTwoTensor.h"
#include "MooseMesh.h"

// Pika includes
#include "ComputeIsotropicViscousStress.h"


template<>
InputParameters validParams<ComputeIsotropicViscousStress>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("velocities", "The deformation velocity variables.");
  params.addParam<std::string>("stress", "stress", "The name of the stress material property being declared by this Material object.");
  params.addParam<MaterialPropertyName>("poissons_ratio", "poissons_ratio", "The name of the material property for Poissons ratio ($\\nu$); a constant or parsed function expression may also be supplied.");
  params.addParam<MaterialPropertyName>("viscosity", "viscosity", "The name of the material property for viscous coefficient ($\\eta$); a constant or parsed function expression may also be supplied.");

  return params;
}

ComputeIsotropicViscousStress::ComputeIsotropicViscousStress(const InputParameters & parameters) :
    Material(parameters),
    _mesh_dim(_mesh.dimension()),
    _deformation_velocities(_mesh_dim),
    _stress(declareProperty<RankTwoTensor>(getParam<std::string>("stress"))),
    _poissons_ratio(getMaterialProperty<Real>("poissons_ratio")),
    _viscosity(getMaterialProperty<Real>("viscosity"))
{
  if (_deformation_velocities.size() != getParam<std::vector<VariableName>>("velocities").size())
    mooseError2("The number of 'velocities' provided must match the problem dimension: ", LIBMESH_DIM);

  for (unsigned int i = 0; i < _mesh_dim; ++i)
    _deformation_velocities[i] = getVar("velocities", i);


}

void
ComputeIsotropicViscousStress::computeQpProperties()
{
  RankTwoTensor strain_rate;
  for (unsigned int i = 0; i < _mesh_dim; ++i)
    for (unsigned int j = 0; j < _mesh_dim; ++j)
      strain_rate(i, j) = 0.5 * (_deformation_velocities[i]->gradSln()[_qp](j) + _deformation_velocities[j]->gradSln()[_qp](i));

  Real lambda = 2 * _poissons_ratio[_qp] * _viscosity[_qp] / (1 - 2 * _poissons_ratio[_qp]);

  _stress[_qp] = 2 * _viscosity[_qp] * strain_rate;
  for (unsigned int i = 0; i < _mesh_dim; ++i)
    _stress[_qp](i,i) = lambda * strain_rate(i,i);

}
