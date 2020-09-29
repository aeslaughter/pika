#pragma once

// MOOSE includes
#include "ADIntegratedBC.h"

class OpticGriffithsBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  OpticGriffithsBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

private:

  const ADMaterialProperty<Real> & _diffusion_coef;
};
