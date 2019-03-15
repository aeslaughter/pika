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

  const ADVariableValue & _absorption_variable;
  const ADVariableValue & _scattering_variable;
  const ADVariableValue & _anisotropy_variable;

  ADMaterialProperty(Real) & _diffusion_prop;

  ADMaterialProperty(Real) & _absorption_prop;

  ADMaterialProperty(Real) & _scattering_prop;

  ADMaterialProperty(Real) & _anisotropy_prop;

  ADMaterialProperty(Real) & _fresnel_transmittance;

  usingMaterialMembers;
};

#endif
