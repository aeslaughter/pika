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

#include "IrradianceSource.h"
#include "Function.h"

registerADMooseObject("PikaApp", IrradianceSource);

template <ComputeStage compute_stage>
InputParameters
IrradianceSource<compute_stage>::validParams()
{
  InputParameters params = ADKernel<compute_stage>::validParams();
  params.addRequiredCoupledVar("irradiance", "Variable that defines the irradiance ('radiant flux').");
  return params;
}

template <ComputeStage compute_stage>
IrradianceSource<compute_stage>::IrradianceSource(const InputParameters & parameters) :
    ADKernel<compute_stage>(parameters),
    _grad_irradiance(adCoupledGradient("irradiance"))
{
}

template <ComputeStage compute_stage>
ADReal
IrradianceSource<compute_stage>::computeQpResidual()
{
  return _test[_i][_qp] * (_grad_irradiance[_qp](0) + _grad_irradiance[_qp](1) + _grad_irradiance[_qp](2));
}
