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
                                        "TODO");
  /*
  params.addParam<MaterialPropertyName>("absorption_coefficient", "optic_absoprtion_coefficient",
                                        "TODO");
  params.addParam<MaterialPropertyName>("scattering_coefficient", "optic_scattering_coefficient",
                                        "TODO");
  params.addParam<MaterialPropertyName>("anisotropy", "optic_anisotropy",
                                        "TODO");
  */

  );

template <ComputeStage compute_stage>
OpticDiffusion<compute_stage>::OpticDiffusion(const InputParameters & parameters) :
ADDiffusion<compute_stage>(parameters),
  _diffusion_coef(adGetADMaterialProperty<Real>("diffusion_coefficient"))
//  _absorption_coef(adGetADMaterialProperty<Real>("absorption_coefficient")),
//  _scattering_coef(adGetADMaterialProperty<Real>("scattering_coefficient")),
//  _anisotropy(adGetADMaterialProperty<Real>("anisotropy"))
{
}

template <ComputeStage compute_stage>
ADVectorResidual
OpticDiffusion<compute_stage>::precomputeQpResidual()
{
  //ADReal reduced_scattering = (1.0 - _anisotropy[_qp]) * _scattering_coef[_qp];
  //ADReal diffusion_coef = 1.0 / (3.0*(_absorption_coef[_qp] - reduced_scattering));
  return _diffusion_coef[_qp] * ADDiffusion<compute_stage>::precomputeQpResidual();
}
