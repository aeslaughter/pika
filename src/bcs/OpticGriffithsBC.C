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

template <ComputeStage compute_stage>
InputParameters
OpticGriffithsBC<compute_stage>::validParams()
{
    InputParameters params = ADIntegratedBC<compute_stage>::validParams();
  params.addParam<MaterialPropertyName>("diffusion_coefficient", "optic_diffusion_coefficient",
                                        "The diffusion coefficient (D) name for the radiative transfer equation with a diffusion approximation.");

return params;
}

template <ComputeStage compute_stage>
OpticGriffithsBC<compute_stage>::OpticGriffithsBC(const InputParameters & parameters) :
    ADIntegratedBC<compute_stage>(parameters),
    _diffusion_coef(getADMaterialProperty<Real>("diffusion_coefficient"))
{
}

template <ComputeStage compute_stage>
ADReal
OpticGriffithsBC<compute_stage>::computeQpResidual()
{
  return - _test[_i][_qp] * _diffusion_coef[_qp] * _grad_u[_qp] * _normals[_qp];
}
