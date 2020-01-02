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

registerADMooseObject("PikaApp", OpticAbsorption);

defineADLegacyParams(OpticAbsorption);

template <ComputeStage compute_stage>
InputParameters
OpticAbsorption<compute_stage>::validParams()
{
    InputParameters params = ADKernelValue<compute_stage>::validParams();
  params.addParam<MaterialPropertyName>("absorption_coefficient", "optic_absorption_coefficient",
                                        "The absorption coefficient ($\\sigma_a$) name for the radiative transfer equation with a diffusion approximation.");

return params;
}

template <ComputeStage compute_stage>
OpticAbsorption<compute_stage>::OpticAbsorption(const InputParameters & parameters) :
    ADKernelValue<compute_stage>(parameters),
    _absorption_coef(getADMaterialProperty<Real>("absorption_coefficient"))
{\
}

template <ComputeStage compute_stage>
ADReal
OpticAbsorption<compute_stage>::precomputeQpResidual()
{
  return _absorption_coef[_qp]  * _u[_qp];
}
