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
  params.addCoupledVar("incoming_flux", "The total incoming irradiance ($W/m^2$).");
  params.addParam<MaterialPropertyName>("average_fresnel_transmittance", "fresnel_transmittance",
                                        "The average Fressel transmittance ($F_{dt}$).");
  );

template <ComputeStage compute_stage>
OpticDiffuseSourceBC<compute_stage>::OpticDiffuseSourceBC(const InputParameters & parameters) :
    ADIntegratedBC<compute_stage>(parameters),
    _transmittance(adGetADMaterialProperty<Real>("fresnel_transmittance")),
    _incoming_flux(adCoupledValue("incoming_flux"))
{
}

template <ComputeStage compute_stage>
ADResidual
OpticDiffuseSourceBC<compute_stage>::computeQpResidual()
{
  ADReal gamma_s = _incoming_flux[_qp] * _dt;
  ADReal F_dt = _transmittance[_qp];
  ADReal F_dr = 1.0 - F_dt;
  ADReal A = (1.0 + F_dr) / (1.0 - F_dr);
  return (1.0 / (2.0 * A) * _u[_qp] - 2.0 / (A * F_dt) * gamma_s) * _test[_i][_qp];
}
