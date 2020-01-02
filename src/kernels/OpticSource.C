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

#include "OpticSource.h"
#include "Function.h"

registerADMooseObject("PikaApp", OpticSource);

defineADValidParams(
  OpticSource,
  ADKernel,
  params.addParam<FunctionName>("function", "0", "A function that describes the body force");
  );

template <ComputeStage compute_stage>
OpticSource<compute_stage>::OpticSource(const InputParameters & parameters) :
    ADKernel<compute_stage>(parameters),
    _function(getFunction("function"))
{
}

template <ComputeStage compute_stage>
ADReal
OpticSource<compute_stage>::computeQpResidual()
{
  return - _function.value(_t, _q_point[_qp]) * _test[_i][_qp];
}
