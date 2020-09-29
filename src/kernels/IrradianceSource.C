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

#include "IrradianceSource.h"
#include "Function.h"

registerMooseObject("PikaApp", IrradianceSource);

InputParameters
IrradianceSource::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("irradiance", "Variable that defines the irradiance ('radiant flux').");
  return params;
}

IrradianceSource::IrradianceSource(const InputParameters & parameters) :
    ADKernel(parameters),
    _grad_irradiance(adCoupledGradient("irradiance"))
{
}

ADReal
IrradianceSource::computeQpResidual()
{
  return _test[_i][_qp] * (_grad_irradiance[_qp](0) + _grad_irradiance[_qp](1) + _grad_irradiance[_qp](2));
}
