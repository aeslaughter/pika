// MOOSE includes
#include "SnowOpticMaterial.h"

registerADMooseObject("PikaApp", SnowOpticMaterial);

template <ComputeStage compute_stage>
InputParameters
SnowOpticMaterial<compute_stage>::validParams()
{
    InputParameters params = ADMaterial<compute_stage>::validParams();
  params.addCoupledVar("density", "The density of the snow ($kg/m^3$).");
  params.addCoupledVar("optical_diameter", "The optical grain size ($m$).");
  params.addCoupledVar("optic_anisotropy", 1, "Optical anisotropy coefficient."
return params;
}

  MooseEnum bands("VIS NIR SWIR");
  params.addParam<MooseEnum>("band", bands, "The wavelength band to consider as defined by Armstrong and Brun (2008): VIS (0.3--0.8 $\\textrm{\\mu m}$), NIR (0.8--1.5 $\\textrm{\\mu m}$), or SWIR (1.5--2.8 $\\textrm{\\mu m}$).");

//  params.addParam<MaterialPropertyName>("optic_diffusion_coefficient_name", "optic_diffusion_coefficient", "The name of the diffusion coefficient for the optical diffusion equation ($D$) in $m$.");
//  params.addParam<MaterialPropertyName>("optic_absorption_coefficient_name");
//  params.addParam<MaterialPropertyName>("optic_scattering_coefficient_name");
//  params.addParam<MaterialPropertyName>("optic_anisotropy_name");



  );

template <ComputeStage compute_stage>
SnowOpticMaterial<compute_stage>::SnowOpticMaterial(const InputParameters & parameters) :
    ADMaterial<compute_stage>(parameters),
      _band(adGetParam<MooseEnum>("band")),
    _density(adCoupledValue("density")),
    _optical_diameter(adCoupledValue("optical_diameter")),
      _anisotropy_variable(adCoupledValue("optic_anisotropy")),
      _diffusion_prop(adDeclareADProperty<Real>("optic_diffusion_coefficient_" + std::string(_band))),
      _absorption_prop(adDeclareADProperty<Real>("optic_absorption_coefficient_" + std::string(_band))),
      _scattering_prop(adDeclareADProperty<Real>("optic_scattering_coefficient_" + std::string(_band))),
      _anisotropy_prop(adDeclareADProperty<Real>("optic_anisotropy_" + std::string(_band)))
{
}

template <ComputeStage compute_stage>
void
SnowOpticMaterial<compute_stage>::computeQpProperties()
{
  // Compute the albedo and coefficient of absoprtion according to Eq. 2.25, note that beta
  // is compute in 1/cm.

  ADReal alpha = 0.0;
  ADReal beta = 0.0;
  const ADReal & d_opt = _optical_diameter[_qp];
  const ADReal sqrt_d_opt = std::sqrt(d_opt);
  if (_band == "VIS")
  {
    alpha = std::min(0.94, 0.96 - 1.58 * sqrt_d_opt);
    beta = std::max(0.04, 0.0192 * _density[_qp] / sqrt_d_opt);
  }
  else if (_band == "NIR")
  {
    alpha = 0.95 - 15.4 * sqrt_d_opt;
    beta = std::max(1.0, 0.1098 * _density[_qp] / sqrt_d_opt);
  }
  else if (_band == "SWIR")
  {
    alpha =  0.95 - 15.4 * sqrt_d_opt;
    beta = std::numeric_limits<ADReal>::infinity();
  }

  _absorption_prop[_qp] = beta * 100.;
  _scattering_prop[_qp] = alpha * beta / (1 - alpha);
  _anisotropy_prop[_qp] = _anisotropy_variable[_qp];

  ADReal reduced_scattering = (1.0 - _anisotropy_prop[_qp]) * _scattering_prop[_qp];
  _diffusion_prop[_qp] = 1.0 / (3.0*(_absorption_prop[_qp] - reduced_scattering));
}

adBaseClass(SnowOpticMaterial);
