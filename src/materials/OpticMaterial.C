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
    ADMaterial<compute_stage>(parameters),
    _diffusion_coef(adDeclareADProperty<Real>("optic_diffusion_coefficient")),
    _absorption_coef(adDeclareADProperty<Real>("optic_absorption_coefficient")),
    _fresnel_transmittance(adDeclareADProperty<Real>("fresnel_transmittance"))
{
}

template <ComputeStage compute_stage>
void
OpticMaterial<compute_stage>::computeQpProperties()
{
  Real albedo = 0.94;
  Real density = 200;


  Real mu = 1.0;
  Real r_ice = 1.31;
  Real r_air = 1.003;

  Real x = density/934.0;

  Real r_snow = r_ice * x + r_air * (1-x);

  Real fr = std::pow(r_air - r_snow, 2) / std::pow(r_air + r_snow, 2);

  _absorption_coef[_qp] = 110;
  ADReal scattering_coef = _absorption_coef[_qp] * albedo / (1 - albedo);
  _fresnel_transmittance[_qp] = 1 - fr;

  _diffusion_coef[_qp] = 1.0 / (3 * (1 - mu) * scattering_coef + _absorption_coef[_qp]);


}

adBaseClass(OpticMaterial);
