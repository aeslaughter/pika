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
  params.addParam<MaterialPropertyName>("average_frensel_transmittance", "transmittance",
                                        "The average Frensel transmittance ($F_{dt}$).");
  );

template <ComputeStage compute_stage>
OpticDiffuseSourceBC<compute_stage>::OpticDiffuseSourceBC(const InputParameters & parameters) :
    ADIntegratedBC<compute_stage>(parameters),
    _transmittance(adGetADMaterialProperty<Real>("transmittance"))
{
}

template <ComputeStage compute_stage>
ADResidual
OpticDiffuseSourceBC<compute_stage>::computeQpResidual()
{
  ADReal F_dt = _transmittance[_qp];
  ADReal F_dr = 1.0 - F_dt;
  ADReal A = (1.0 + F_dr) / (1.0 - F_dr);
  return (1.0 / (2.0 * A) * _u[_qp] - 2.0 / (A * F_dt) * _incoming_flux[_qp]) * _test[_i][_qp];
}
