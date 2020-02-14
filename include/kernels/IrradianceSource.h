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

#ifndef IRRADIANCESOURCE_H
#define IRRADIANCESOURCE_H

// MOOSE includes
#include "ADKernel.h"

template <ComputeStage compute_stage>
class IrradianceSource : public ADKernel<compute_stage>
{
public:
  static InputParameters validParams();

  IrradianceSource(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

private:

  const ADVariableGradient & _grad_irradiance;

  usingKernelMembers;
};

#endif
