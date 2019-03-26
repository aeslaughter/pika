#ifndef SNOWOPTICMATERIAL_H
#define SNOWOPTICMATERIAL_H

#include "ADMaterial.h"

// forward declarations
template <ComputeStage>
class SnowOpticMaterial;

declareADValidParams(SnowOpticMaterial);

/**
 * Computes optical properties from Amstrong and Brun, p. 56, Ex. 2.25
 */
template <ComputeStage compute_stage>
class SnowOpticMaterial : public ADMaterial<compute_stage>
{
public:
  SnowOpticMaterial(const InputParameters & parameters);

  virtual void computeQpProperties() override;

protected:

  const MooseEnum & _band;

  const ADVariableValue & _density;

  const ADVariableValue & _optical_diameter;

  const ADVariableValue & _anisotropy_variable;

  ADMaterialProperty(Real) & _diffusion_prop;

  ADMaterialProperty(Real) & _absorption_prop;

  ADMaterialProperty(Real) & _scattering_prop;

  ADMaterialProperty(Real) & _anisotropy_prop;

  usingMaterialMembers;
};

#endif
