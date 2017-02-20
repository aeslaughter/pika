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

#ifndef COMPUTEISOTROPICVISCOUSSTRESS_H
#define COMPUTEISOTROPICVISCOUSSTRESS_H

// MOOSE includes
#include "Material.h"

class RankTwoTensor;
class ComputeIsotropicViscousStress;

template<>
InputParameters validParams<ComputeIsotropicViscousStress>();

class ComputeIsotropicViscousStress : public Material
{
public:
  ComputeIsotropicViscousStress(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  const unsigned int _mesh_dim;

  std::vector<MooseVariable *> _deformation_velocities;

  MaterialProperty<RankTwoTensor> & _strain_rate;
  MaterialProperty<RankTwoTensor> & _stress;

  const MaterialProperty<Real> & _poissons_ratio;
  const MaterialProperty<Real> & _viscosity;
  const MaterialProperty<Real> & _lambda;



};

#endif
