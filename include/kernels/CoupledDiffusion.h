#ifndef COUPLEDDIFFUSION_H
#define COUPLEDDIFFUSION_H

#include "Kernel.h"

class VectorValue;
class CoupledDiffusion;

template<>
InputParameters validParams<CoupledDiffusion>();

/**
 *
 */
class  CoupledDiffusion: public Kernel
{
public:
  CoupledDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  VectorValue<Real> _velocity;

  const unsigned int _mesh_dim;
  std::vector<MooseVariable *> _deformation_velocities;

};

#endif
