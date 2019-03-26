#ifndef OPTICGRIFFITHSBC_H
#define OPTICGRIFFITHSBC_H

// MOOSE includes
#include "ADIntegratedBC.h"

template <ComputeStage compute_stage>
class OpticGriffithsBC;

declareADValidParams(OpticGriffithsBC);

template <ComputeStage compute_stage>
class OpticGriffithsBC : public ADIntegratedBC<compute_stage>
{
public:
  OpticGriffithsBC(const InputParameters & parameters);

protected:
  virtual ADResidual computeQpResidual() override;

private:

  const ADMaterialProperty(Real) & _diffusion_coef;

  usingIntegratedBCMembers;
};

#endif
