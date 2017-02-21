#ifndef MOMENTUMTIMEDERIVATIVE_H
#define MOMENTUMTIMEDERIVATIVE_H

#include "TimeDerivative.h"

class MomentumTimeDerivative;

template<>
InputParameters validParams<MomentumTimeDerivative>();

/**
 *
 */
class  MomentumTimeDerivative: public TimeDerivative
{
public:
  MomentumTimeDerivative(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _density;
};

#endif // MOMENTUMTIMEDERIVATIVE_H
