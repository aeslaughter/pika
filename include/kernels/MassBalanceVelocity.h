#ifndef MASSBALANCEVELOCITY_H
#define MASSBALANCEVELOCITY_H

#include "Kernel.h"

class MassBalanceVelocity;

template<>
InputParameters validParams<MassBalanceVelocity>();

/**
 *
 */
class  MassBalanceVelocity: public Kernel
{
public:
  MassBalanceVelocity(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const VariableGradient & _grad_velocity;
  const MooseEnum & _component;
};

#endif // MASSBALANCEVELOCITY_H
