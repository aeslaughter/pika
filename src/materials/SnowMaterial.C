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

#include "SnowMaterial.h"

registerMooseObject("PikaApp", SnowMaterial);

InputParameters
SnowMaterial::validParams()
{
  InputParameters params = ADMaterial::validParams();
  params.addRequiredCoupledVar("temperature", "The snow temperature variable to couple");
  params.addParam<MaterialPropertyName>("density", "density", "Density of snow [kg/m^3]");
  return params;
}

SnowMaterial::SnowMaterial(const InputParameters & parameters) :
    ADMaterial(parameters),
    _temperature(adCoupledValue("temperature")),
    _density(getADMaterialProperty<Real>("density")),
    _thermal_conductivity(declareADProperty<Real>("thermal_conductivity")),
    _specific_heat(declareADProperty<Real>("specific_heat"))
{
}

void
SnowMaterial::computeQpProperties()
{
  _thermal_conductivity[_qp] = 0.021 + 2.5 * std::pow(_density[_qp] / 1000, 2);
  _specific_heat[_qp] = 1000 * (2.115 + 0.00779 * (273.15 - _temperature[_qp]));
}
