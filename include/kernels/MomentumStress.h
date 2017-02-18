#ifndef MOMENTUMSTRESS_H
#define MOMENTUMSTRESS_H

#include "Kernel.h"

class RankTwoTensor;
class MomentumStress;

template<>
InputParameters validParams<MomentumStress>();

/**
 *
 */
class MomentumStress : public Kernel
{
public:
  MomentumStress(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MaterialProperty<RankTwoTensor> & _stress;
  const MooseEnum & _component;
};

#endif // MOMENTUMSTRESS_H
