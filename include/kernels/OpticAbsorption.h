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
#include "ADKernelValue.h"

class OpticAbsorption : public ADKernelValue
{
public:
  static InputParameters validParams();

  OpticAbsorption(const InputParameters & parameters);

protected:
  virtual ADReal precomputeQpResidual() override;

private:

  const ADMaterialProperty<Real> & _absorption_coef;
};
