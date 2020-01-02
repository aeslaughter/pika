#ifndef SNOWOPTICMATERIAL_H
#define SNOWOPTICMATERIAL_H

#include "ADMaterial.h"

// forward declarations
template <ComputeStage>
class SnowOpticMaterial;

/**
 * Computes optical properties from Amstrong and Brun, p. 56, Ex. 2.25
 */
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
