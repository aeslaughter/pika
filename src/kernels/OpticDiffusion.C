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


defineADValidParams(
  OpticDiffusion,
  ADDiffusion,
  params.addParam<MaterialPropertyName>("diffusion_coefficient", "optic_diffusion_coefficient",
                                        "The diffusion coefficient for optical diffusion.");
  );

template <ComputeStage compute_stage>
OpticDiffusion<compute_stage>::OpticDiffusion(const InputParameters & parameters) :
    ADDiffusion<compute_stage>(parameters),
    _diffusion_coef(adGetADMaterialProperty<Real>("diffusion_coefficient"))
{
}

template <ComputeStage compute_stage>
ADResidual
OpticDiffusion<compute_stage>::computeQpResidual()
{
  return _diffusion_coef[_qp] * ADDiffusion<compute_stage>::computeQpResidual();
}
