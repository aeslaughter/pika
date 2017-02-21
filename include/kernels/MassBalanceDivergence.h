#ifndef MASSBALANCEDIVERGENCE_H
#define MASSBALANCEDIVERGENCE_H

#include "Kernel.h"

class MassBalanceDivergence;

template<>
InputParameters validParams<MassBalanceDivergence>();

/**
 *
 */
class  MassBalanceDivergence: public Kernel
{
public:
  MassBalanceDivergence(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const unsigned int _mesh_dim;

  std::vector<MooseVariable *> _deformation_velocities;

  RealVectorValue _velocity;
};

#endif
