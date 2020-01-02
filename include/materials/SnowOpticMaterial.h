#ifndef SNOWOPTICMATERIAL_H
#define SNOWOPTICMATERIAL_H

#include "ADMaterial.h"

template <ComputeStage compute_stage>
class SnowOpticMaterial : public ADMaterial<compute_stage>
{
public:
  static InputParameters validParams();

  SnowOpticMaterial(const InputParameters & parameters);

  virtual void computeQpProperties() override;

protected:

  const ADMaterialProperty(Real) & _alpha;

  const ADMaterialProperty(Real) & _kappa;

  const ADMaterialProperty(Real) & _anisotropy;

  ADMaterialProperty(Real) & _diffusion_coefficient;

  ADMaterialProperty(Real) & _absorption_coefficient;

  usingMaterialMembers;
};

#endif
