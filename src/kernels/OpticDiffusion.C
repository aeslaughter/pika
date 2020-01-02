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

registerADMooseObject("PikaApp", OpticDiffusion);

template <ComputeStage compute_stage>
InputParameters
OpticDiffusion<compute_stage>::validParams()
{
    InputParameters params = ADDiffusion<compute_stage>::validParams();
  params.addParam<MaterialPropertyName>("diffusion_coefficient", "optic_diffusion_coefficient",
                                        "The diffusion coefficient (D) name for the radiative transfer equation with a diffusion approximation.");

return params;
}

template <ComputeStage compute_stage>
OpticDiffusion<compute_stage>::OpticDiffusion(const InputParameters & parameters) :
ADDiffusion<compute_stage>(parameters),
  _diffusion_coef(getADMaterialProperty<Real>("diffusion_coefficient"))
{
}

template <ComputeStage compute_stage>
ADRealVectorValue
OpticDiffusion<compute_stage>::precomputeQpResidual()
{
  return _diffusion_coef[_qp] * ADDiffusion<compute_stage>::precomputeQpResidual();
}
