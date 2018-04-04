#include "PhotonBC.h"

#include "PhotonDiffusion.h"

registerMooseObject("PikaApp", PhotonBC);

template<>
InputParameters validParams<PhotonBC>()
{
  InputParameters params = validParams<IntegratedBC>();
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

PhotonBC::PhotonBC(const InputParameters & parameters) :
    IntegratedBC(parameters),
    _speed_of_light(getMaterialProperty<Real>("speed_of_light")),
    _absoprtion_coefficient(getMaterialProperty<Real>("absorption_coefficient")),
    _scattering_coefficient(getMaterialProperty<Real>("scattering_coefficient")),
    _average_of_cosine_phase_function(getMaterialProperty<Real>("average_of_cosine_phase_function"))
{
}

Real
PhotonBC::computeQpResidual()
{
  Real k = PhotonDiffusion::kappa(_speed_of_light[_qp],
                                  _absoprtion_coefficient[_qp],
                                  _scattering_coefficient[_qp],
                                  _average_of_cosine_phase_function[_qp]);


  return _test[_i][_qp] * k * _grad_u[_qp] * _normals[_qp];

}

Real
PhotonBC::computeQpJacobian()
{
  Real k = PhotonDiffusion::kappa(_speed_of_light[_qp],
                                  _absoprtion_coefficient[_qp],
                                  _scattering_coefficient[_qp],
                                  _average_of_cosine_phase_function[_qp]);


  return _test[_i][_qp] * k * _grad_phi[_j][_qp] * _normals[_qp];
}
