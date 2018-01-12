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

defineADValidParams(
  OpticAbsorption,
  ADKernel,
  params.addParam<MaterialPropertyName>("absorption_coefficient", "absorption_coefficient",
                                        "The absorption coefficient ($\\mu_a$) name [1/m].");
  );

template <ComputeStage compute_stage>
OpticAbsorption<compute_stage>::OpticAbsorption(const InputParameters & parameters) :
    ADKernel<compute_stage>(parameters),
    _absorption_coef(adGetADMaterialProperty<Real>("absorption_coefficient"))
{
}

template <ComputeStage compute_stage>
ADResidual
OpticAbsorption<compute_stage>::computeQpResidual()
{
  return _absorption_coef[_qp] * _test[_i][_qp] * _u[_qp];
}
