#ifndef OPTICMATERIAL_H
#define OPTICMATERIAL_H

#include "ADMaterial.h"

// forward declarations
template <ComputeStage>
class OpticMaterial;

declareADValidParams(OpticMaterial);

/**
 * OpticMaterials compute OpticMaterialProperties.
 */
template <ComputeStage compute_stage>
class OpticMaterial : public ADMaterial<compute_stage>
{
public:
  OpticMaterial(const InputParameters & parameters);

  virtual void computeQpProperties() override;

protected:

  ADMaterialProperty(Real) & _diffusion_coef;

  ADMaterialProperty(Real) & _absorption_coef;

  ADMaterialProperty(Real) & _fresnel_transmittance;

  usingMaterialMembers;
};

#endif
