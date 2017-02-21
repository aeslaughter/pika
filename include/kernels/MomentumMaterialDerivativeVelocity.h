#ifndef MOMENTUMMATERIALDERIVATIVEVELOCITY_H
#define MOMENTUMMATERIALDERIVATIVEVELOCITY_H

#include "Kernel.h"

class MomentumMaterialDerivativeVelocity;

template<>
InputParameters validParams<MomentumMaterialDerivativeVelocity>();

/**
 *
 */
class  MomentumMaterialDerivativeVelocity: public Kernel
{
public:
  MomentumMaterialDerivativeVelocity(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const unsigned int _mesh_dim;

  std::vector<MooseVariable *> _deformation_velocities;

  const MaterialProperty<Real> & _density;

  RealVectorValue _velocity;
};

#endif
