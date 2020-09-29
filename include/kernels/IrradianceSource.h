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
#pragma once

// MOOSE includes
#include "ADKernel.h"

class IrradianceSource : public ADKernel
{
public:
  static InputParameters validParams();

  IrradianceSource(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

private:

  const ADVariableGradient & _grad_irradiance;
};
