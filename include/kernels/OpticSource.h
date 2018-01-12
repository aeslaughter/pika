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

#ifndef OPTICSOURCE_H
#define OPTICSOURCE_H

// MOOSE includes
#include "ADKernel.h"

template <ComputeStage compute_stage>
class OpticSource;

declareADValidParams(OpticSource);

template <ComputeStage compute_stage>
class OpticSource : public ADKernel<compute_stage>
{
public:
  OpticSource(const InputParameters & parameters);

protected:
  virtual ADResidual computeQpResidual() override;

private:

  Function & _function;

  using ADKernel<compute_stage>::getFunction;//(const std::string &);
  using ADKernel<compute_stage>::_qp;
  using ADKernel<compute_stage>::_i;
  using ADKernel<compute_stage>::_q_point;
  using ADKernel<compute_stage>::_t;
  using ADKernel<compute_stage>::_test;

};

#endif
