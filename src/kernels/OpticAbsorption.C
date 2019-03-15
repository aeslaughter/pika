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
  ADKernelValue,
  params.addParam<MaterialPropertyName>("absorption_coefficient", "optic_absorption_coefficient",
                                        "The absorption coefficient ($\\sigma_a$) name [1/m].");
  );

template <ComputeStage compute_stage>
OpticAbsorption<compute_stage>::OpticAbsorption(const InputParameters & parameters) :
    ADKernelValue<compute_stage>(parameters),
    _absorption_coef(adGetADMaterialProperty<Real>("absorption_coefficient"))
{\
}

template <ComputeStage compute_stage>
ADResidual
OpticAbsorption<compute_stage>::precomputeQpResidual()
{
  return _absorption_coef[_qp]  * _u[_qp];
}
