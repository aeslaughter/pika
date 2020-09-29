#pragma once

#include "ADMaterial.h"

class SnowOpticMaterial : public ADMaterial
{
public:
  static InputParameters validParams();

  SnowOpticMaterial(const InputParameters & parameters);

  virtual void computeQpProperties() override;

protected:

  const ADMaterialProperty<Real> & _alpha;

  const ADMaterialProperty<Real> & _kappa;

  const ADMaterialProperty<Real> & _anisotropy;

  ADMaterialProperty<Real> & _diffusion_coefficient;

  ADMaterialProperty<Real> & _absorption_coefficient;
};

#endif
