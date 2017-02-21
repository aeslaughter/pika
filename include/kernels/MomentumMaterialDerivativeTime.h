#ifndef MOMENTUMMATERIALDERIVATIVETIME_H
#define MOMENTUMMATERIALDERIVATIVETIME_H

#include "TimeDerivative.h"

class MomentumMaterialDerivativeTime;

template<>
InputParameters validParams<MomentumMaterialDerivativeTime>();

/**
 *
 */
class  MomentumMaterialDerivativeTime: public TimeDerivative
{
public:
  MomentumMaterialDerivativeTime(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _density;
};

#endif // MomentumMaterialDerivativeTime_H
