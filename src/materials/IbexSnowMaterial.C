/**********************************************************************************/
/*                  Pika: Phase field snow micro-structure model                  */
/*                                                                                */
/*                     (C) 2014 Battelle Energy Alliance, LLC                     */
/*                              ALL RIGHTS RESERVED                               */
/*                                                                                */
/*                   Prepared by Battelle Energy Alliance, LLC                    */
/*                      Under Contract No. DE-AC07-05ID14517                      */
/*                      With the U. S. Department of Energy                       */
/**********************************************************************************/

#include "IbexSnowMaterial.h"

template<>
InputParameters validParams<IbexSnowMaterial>()
{
  MooseEnum model("Teufelsbasur2011=0 Kojima1974=1", "Teufelsbasur2011");


  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("temperature", "The snow temperature variable to couple");
  params.addCoupledVar("density", 200, "Density of snow.");
  params.addParam<Real>("thermal_conductivity", "Thermal conductivity of snow; if omitted it is estimated based on density");
  params.addParam<Real>("specific_heat", "Specific heat of snow; if omitted it is estimated based on temperature");

  params.addCoupledVar("thermal_conductivity_name", "Name of a variable to utilize for thermal conductivity; this superceeds all other values");

  params.addParam<MooseEnum>("viscosity_model", model, "The viscosity model to utilze.");

  params.addRangeCheckedParam<Real>("poissons_ratio_max", 0.49, "poissons_ratio_max<0.5 & poissons_ratio_max>-1", "The maximum allowable poissons ratio to compute.");
  params.addRangeCheckedParam<Real>("density_reference", 300, "density_reference>0 & density_reference<900", "The reference density for computing poissons ratio.");
  params.addParam<Real>("temperature_reference_coefficient", 15., "The linear temperature coefficient ($r_{T}$) for computing poissons ratio.");
  params.addParam<Real>("density_reference_coefficient", 15., "The linear density coefficient ($r_{\\rho}$) for computing poissons ratio.");

  return params;
}

IbexSnowMaterial::IbexSnowMaterial(const InputParameters & parameters) :
    Material(parameters),
    _temperature(coupledValue("temperature")),
    _input_density(coupledValue("density")),
    _compute_conductivity(!isParamValid("thermal_conductivity")),
    _input_conductivity(_compute_conductivity ? 0 : getParam<Real>("thermal_conductivity")),
    _compute_specific_heat(!isParamValid("specific_heat")),
    _input_specific_heat(_compute_specific_heat ? 0 : getParam<Real>("specific_heat")),
    _density(declareProperty<Real>("density")),
    _conductivity(declareProperty<Real>("thermal_conductivity")),
    _specific_heat(declareProperty<Real>("specific_heat")),
    _use_conductivity_variable(isParamValid("thermal_conductivity_name")),
    _conductivity_variable(_use_conductivity_variable ? coupledValue("thermal_conductivity_name") : _zero),
    _viscosity_model(getParam<MooseEnum>("viscosity_model")),
    _viscosity(declareProperty<Real>("viscosity")),
    _poissons_ratio(declareProperty<Real>("poissons_ratio")),
    _lambda(declareProperty<Real>("lambda")),
    _density_reference(getParam<Real>("density_reference")),
    _poissons_ratio_max(getParam<Real>("poissons_ratio_max")),
    _density_reference_coefficient(getParam<Real>("density_reference_coefficient")),
    _temperature_reference_coefficient(getParam<Real>("temperature_reference_coefficient"))
{
}

void
IbexSnowMaterial::computeQpProperties()
{
  _density[_qp] = _input_density[_qp];

  if (_use_conductivity_variable)
    _conductivity[_qp] = _conductivity_variable[_qp];
  else if (_compute_conductivity)
    _conductivity[_qp] = 0.021 + 2.5 * std::pow(_density[_qp] / 1000, 2);
  else
    _conductivity[_qp] = _input_conductivity;

  if (_compute_specific_heat)
    _specific_heat[_qp] = 1000 * (2.115 + 0.00779 * (_temperature[_qp] - 273.15));
  else
    _specific_heat[_qp] = _input_specific_heat;


  switch (_viscosity_model)
  {
  case 0: // Teufelsbasur2011
    _eta_s = 0.05 * std::pow(_density[_qp], -0.0371 * (_temperature[_qp] - 273.15) + 4.4) * (10E-4 * exp(0.018 * _density[_qp]) + 1);
    break;
  case 1: // Kojima1974
    _eta_s = 8.64 * 10E6 * exp(0.021 * _density[_qp]);
    break;
  }

  Real v_p_T = poissonsRatioBar(_density[_qp], _temperature[_qp]);
  Real v_0_T = poissonsRatioBar(0.0, _temperature[_qp]);
  Real v_1000_T = poissonsRatioBar(1000., _temperature[_qp]);

  _poissons_ratio[_qp] = _poissons_ratio_max * (v_p_T - v_0_T) / (v_1000_T - v_0_T);

  std::cout << "mu = " << _poissons_ratio[_qp] << std::endl;
  std::cout << "_eta_s = " << _eta_s << std::endl;
  _viscosity[_qp] = _eta_s * (2 * _poissons_ratio[_qp] - 1) / (2 * (_poissons_ratio[_qp] - 2));
  std::cout << "eta = " << _viscosity[_qp] << std::endl;
  _lambda[_qp] = -(2 * _viscosity[_qp] * _poissons_ratio[_qp]) / (2 * _poissons_ratio[_qp] - 1 );
  std::cout << "lambda = " << _lambda[_qp] << std::endl;
}

Real
IbexSnowMaterial::poissonsRatioBar(const Real & density, const Real & temperature)
{
  Real rho_p = _density_reference - _temperature_reference_coefficient * (temperature - 273.15);
  std::cout << "rho_p = " << rho_p << std::endl;
  return std::atan((density - rho_p) / _density_reference_coefficient);
}
