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

#include "OpticGriffithsBC.h"

registerADMooseObject("PikaApp", OpticGriffithsBC);


defineADValidParams(
  OpticGriffithsBC,
  ADIntegratedBC,
  params.addParam<MaterialPropertyName>("diffusion_coefficient", "optic_diffusion_coefficient",
                                        "TODO");
  );

template <ComputeStage compute_stage>
OpticGriffithsBC<compute_stage>::OpticGriffithsBC(const InputParameters & parameters) :
    ADIntegratedBC<compute_stage>(parameters),
    _diffusion_coef(adGetADMaterialProperty<Real>("diffusion_coefficient"))
{
}

template <ComputeStage compute_stage>
ADResidual
OpticGriffithsBC<compute_stage>::computeQpResidual()
{
  return - _test[_i][_qp] * _diffusion_coef[_qp] * _grad_u[_qp] * _normals[_qp];
}
