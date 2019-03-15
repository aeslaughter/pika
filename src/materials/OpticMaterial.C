// MOOSE includes
#include "OpticMaterial.h"

registerADMooseObject("PikaApp", OpticMaterial);


defineADValidParams(
  OpticMaterial,
  ADMaterial,
  params.addCoupledVar("optic_absorption", "Optical absoprtion coefficient.");
  params.addCoupledVar("optic_scattering", "Optical scattering coefficient.");
  params.addCoupledVar("optic_anisotropy", "Optical anisotropy coefficient.");
  );

template <ComputeStage compute_stage>
OpticMaterial<compute_stage>::OpticMaterial(const InputParameters & parameters) :
    ADMaterial<compute_stage>(parameters),
    _absorption_variable(adCoupledValue("optic_absorption")),
    _scattering_variable(adCoupledValue("optic_scattering")),
    _anisotropy_variable(adCoupledValue("optic_anisotropy")),
    _diffusion_prop(adDeclareADProperty<Real>("optic_diffusion_coefficient")),
    _absorption_prop(adDeclareADProperty<Real>("optic_absorption_coefficient")),
    _scattering_prop(adDeclareADProperty<Real>("optic_scattering_coefficient")),
    _anisotropy_prop(adDeclareADProperty<Real>("optic_anisotropy")),
    _fresnel_transmittance(adDeclareADProperty<Real>("optic_fresnel_transmittance"))
{
}

template <ComputeStage compute_stage>
void
OpticMaterial<compute_stage>::computeQpProperties()
{
  _absorption_prop[_qp] = _absorption_variable[_qp];
  _scattering_prop[_qp] = _scattering_variable[_qp];
  _anisotropy_prop[_qp] = _anisotropy_variable[_qp];

  ADReal reduced_scattering = (1.0 - _anisotropy_prop[_qp]) * _scattering_prop[_qp];
  _diffusion_prop[_qp] = 1.0 / (3.0*(_absorption_prop[_qp] - reduced_scattering));

  //Real albedo = 0.94;
  //Real density = 300;

  //Real mu = 1.0;
  Real r_ice = 1.31;
  Real r_air = 1.003;

  //Real x = density/934.0;

  //Real r_snow = r_ice * x + r_air * (1-x);
  Real eta = r_ice / r_air;

  //Real fr = std::pow(r_air - r_ice, 2) / std::pow(r_air + r_ice, 2);
  Real f_dr = -1.440 / (eta * eta) + 0.710/eta + 0.668 + 0.0636*eta;

  //std::cout << "fr = " << fr << "; f_dr = " << f_dr << std::endl;

  _fresnel_transmittance[_qp] = 1 - f_dr;

}

adBaseClass(OpticMaterial);
