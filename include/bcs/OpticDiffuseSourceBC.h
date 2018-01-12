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

#include "OpticDiffuseSourceBC.h"

registerADMooseObject("PikaApp", OpticDiffuseSourceBC);


defineADValidParams(
  OpticDiffuseSourceBC,
  ADIntegratedBC,
  //params.addParam<MaterialPropertyName>("diffusion_coefficient", "optic_diffusion_coefficient",
  //                                      "The diffusion coefficient for optical diffusion.");
  );

template <ComputeStage compute_stage>
OpticDiffuseSourceBC<compute_stage>::OpticDiffuseSourceBC(const InputParameters & parameters) :
    ADIntegratedBC<compute_stage>(parameters)//,
//    _diffusion_coef(adGetADMaterialProperty<Real>("diffusion_coefficient"))
{
}

template <ComputeStage compute_stage>
ADResidual
OpticDiffuseSourceBC<compute_stage>::computeQpResidual()
{
  return 0.0;// _diffusion_coef[_qp] * ADDiffuseSourceBC<compute_stage>::computeQpResidual();
}
