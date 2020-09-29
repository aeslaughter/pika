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

#include "OpticAbsorption.h"

registerMooseObject("PikaApp", OpticAbsorption);

InputParameters
OpticAbsorption::validParams()
{
  InputParameters params = ADKernelValue::validParams();
  params.addParam<MaterialPropertyName>("absorption_coefficient", "optic_absorption_coefficient",
                                        "The absorption coefficient ($\\sigma_a$) name for the radiative transfer equation with a diffusion approximation.");

  return params;
}

OpticAbsorption::OpticAbsorption(const InputParameters & parameters) :
    ADKernelValue(parameters),
    _absorption_coef(getADMaterialProperty<Real>("absorption_coefficient"))
{
}

ADReal
OpticAbsorption::precomputeQpResidual()
{
  return _absorption_coef[_qp]  * _u[_qp];
}
