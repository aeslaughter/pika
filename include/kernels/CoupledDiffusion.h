#ifndef COUPLEDDIFFUSION_H
#define COUPLEDDIFFUSION_H

#include "Diffusion.h"

class CoupledDiffusion;

template<>
InputParameters validParams<CoupledDiffusion>();

/**
 *
 */
class  CoupledDiffusion: public Diffusion
{
public:
  CoupledDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const VariableValue & _velocity;
};

#endif
