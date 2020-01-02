#ifndef OPTICGRIFFITHSBC_H
#define OPTICGRIFFITHSBC_H

// MOOSE includes
#include "ADIntegratedBC.h"

template <ComputeStage compute_stage>
class OpticGriffithsBC : public ADIntegratedBC<compute_stage>
{
public:
  static InputParameters validParams();

  OpticGriffithsBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

private:

  const ADMaterialProperty(Real) & _diffusion_coef;

  usingIntegratedBCMembers;
};

#endif
