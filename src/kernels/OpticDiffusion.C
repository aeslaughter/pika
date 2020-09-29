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

#include "OpticDiffusion.h"

registerMooseObject("PikaApp", OpticDiffusion);

InputParameters
OpticDiffusion::validParams()
{
    InputParameters params = ADDiffusion::validParams();
  params.addParam<MaterialPropertyName>("diffusion_coefficient", "optic_diffusion_coefficient",
                                        "The diffusion coefficient (D) name for the radiative transfer equation with a diffusion approximation.");

return params;
}

OpticDiffusion::OpticDiffusion(const InputParameters & parameters) :
ADDiffusion(parameters),
  _diffusion_coef(getADMaterialProperty<Real>("diffusion_coefficient"))
{
}

ADRealVectorValue
OpticDiffusion::precomputeQpResidual()
{
  return _diffusion_coef[_qp] * ADDiffusion::precomputeQpResidual();
}
