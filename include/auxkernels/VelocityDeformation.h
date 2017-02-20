#ifndef VELOCITYDEFORMATION_H
#define VELOCITYDEFORMATION_H

#include "AuxKernel.h"

class VelocityDeformation;

template<>
InputParameters validParams<VelocityDeformation>();

/**
 *
 */
class VelocityDeformation : public AuxKernel
{
public:
  VelocityDeformation(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const VariableValue & _velocity;
};

#endif
