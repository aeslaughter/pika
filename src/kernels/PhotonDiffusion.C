#include "PhotonDiffusion.h"

registerMooseObject("PikaApp", PhotonDiffusion);

template<>
InputParameters validParams<PhotonDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addParam<MaterialPropertyName>("speed_of_light",
                                        "speed_of_light",
                                        "The speed of light through the medium ($$c$$; m/s).");

  params.addParam<MaterialPropertyName>("absorption_coefficient",
                                        "absorption_coefficient",
                                        "Absorption coefficient of medium ($\\mu_a$$; 1/m)");

  params.addParam<MaterialPropertyName>("scattering_coefficient",
                                        "scattering_coefficient",
                                        "Scattering coefficient of medium ($\\mu_s$$; 1/m)");

  params.addParam<MaterialPropertyName>("average_of_cosine_phase_function",
                                        "average_of_cosine_phase_function",
                                        "The average cosine of (direction independent) phase "
                                        "function ($\\overline{f}$).");
  return params;
}

PhotonDiffusion::PhotonDiffusion(const InputParameters & parameters) :
    Diffusion(parameters),
    _speed_of_light(getMaterialProperty<Real>("speed_of_light")),
    _absoprtion_coefficient(getMaterialProperty<Real>("absorption_coefficient")),
    _scattering_coefficient(getMaterialProperty<Real>("scattering_coefficient")),
    _average_of_cosine_phase_function(getMaterialProperty<Real>("average_of_cosine_phase_function"))
{
}

Real
PhotonDiffusion::computeQpResidual()
{
  Real k = kappa(_speed_of_light[_qp],
                 _absoprtion_coefficient[_qp],
                 _scattering_coefficient[_qp],
                 _average_of_cosine_phase_function[_qp]);

  return k * Diffusion::computeQpResidual();
}

Real
PhotonDiffusion::computeQpJacobian()
{
  Real k = kappa(_speed_of_light[_qp],
                 _absoprtion_coefficient[_qp],
                 _scattering_coefficient[_qp],
                 _average_of_cosine_phase_function[_qp]);

  return k * Diffusion::computeQpJacobian();
}

Real
PhotonDiffusion::kappa(const Real & c, const Real & mu_a, const Real & mu_s, const Real & f)
{
  return c / (3 * (mu_a + (1 - f) * mu_s));
}
