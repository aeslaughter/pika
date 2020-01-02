// MOOSE includes
#include "SnowOpticMaterial.h"

registerADMooseObject("PikaApp", SnowOpticMaterial);

template <ComputeStage compute_stage>
InputParameters
SnowOpticMaterial<compute_stage>::validParams()
{
    InputParameters params = ADMaterial<compute_stage>::validParams();
    params.addParam<MaterialPropertyName>("effective_attenuation_coefficient", "effective_attenuation_coefficient",
                                          "The effective attenuation coefficient ($\\mu_{eff}$) property name.");
    params.addParam<MaterialPropertyName>("single_scattering_albedo", "single_scattering_albedo",
                                          "The single scattering albedo property name.");
    params.addParam<MaterialPropertyName>("scattering_anisotropy", "scattering_anisotropy",
                                          "The scattering anisotropy property name.");
    return params;
}

template <ComputeStage compute_stage>
SnowOpticMaterial<compute_stage>::SnowOpticMaterial(const InputParameters & parameters) :
    ADMaterial<compute_stage>(parameters),
    _alpha(getADMaterialProperty<Real>("single_scattering_albedo")),
    _kappa(getADMaterialProperty<Real>("effective_attenuation_coefficient")),
    _anisotropy(getADMaterialProperty<Real>("scattering_anisotropy")),
    _diffusion_coefficient(declareADProperty<Real>("optic_diffusion_coefficient")),
    _absorption_coefficient(declareADProperty<Real>("optic_absorption_coefficient"))
{
}

template <ComputeStage compute_stage>
void
SnowOpticMaterial<compute_stage>::computeQpProperties()
{
  ADReal u_a = _kappa[_qp] * std::sqrt(1 / (3 * (1 + _alpha[_qp]/(1 - _alpha[_qp]) - _anisotropy[_qp] * _alpha[_qp] / (1 - _alpha[_qp]))));
  ADReal u_s = _alpha[_qp] * u_a / (1 - _alpha[_qp]);

  _diffusion_coefficient[_qp] = 1 / (3 * (u_a + (1 - _anisotropy[_qp]) * u_s));
  _absorption_coefficient[_qp] = u_a;
}

adBaseClass(SnowOpticMaterial);
