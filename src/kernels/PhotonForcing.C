#include "PhotonForcing.h"

registerMooseObject("PikaApp", PhotonForcing);

template<>
InputParameters validParams<PhotonForcing>()
{
  InputParameters params = validParams<Diffusion>();
  params.addParam<MaterialPropertyName>("speed_of_light",
                                        "speed_of_light",
                                        "The speed of light through the medium ($$c$$; m/s).");

  params.addParam<MaterialPropertyName>("absorption_coefficient",
                                        "absorption_coefficient",
                                        "Absorption coefficient of medium ($\\mu_a$$; 1/m)");

  return params;
}

PhotonForcing::PhotonForcing(const InputParameters & parameters) :
    Kernel(parameters),
    _speed_of_light(getMaterialProperty<Real>("speed_of_light")),
    _absoprtion_coefficient(getMaterialProperty<Real>("absorption_coefficient"))
{
}

Real
PhotonForcing::computeQpResidual()
{
  return _speed_of_light[_qp] * _absoprtion_coefficient[_qp] * _u[_qp] * _test[_i][_qp];
}

Real
PhotonForcing::computeQpJacobian()
{
  return _speed_of_light[_qp] * _absoprtion_coefficient[_qp] * _test[_i][_qp];
}
