// MOOSE includes
#include "OpticMaterial.h"

registerADMooseObject("PikaApp", OpticMaterial);

template <>
InputParameters
validParams<OpticMaterial<RESIDUAL>>()
{
  InputParameters params = validParams<Material>();
  return params;
}
template <>
InputParameters
validParams<OpticMaterial<JACOBIAN>>()
{
  return validParams<OpticMaterial<RESIDUAL>>();
}

template <ComputeStage compute_stage>
OpticMaterial<compute_stage>::OpticMaterial(const InputParameters & parameters) :
    ADMaterial<compute_stage>(parameters)
{
}

template <ComputeStage compute_stage>
void
OpticMaterial<compute_stage>::computeQpProperties()
{

}

adBaseClass(OpticMaterial);
