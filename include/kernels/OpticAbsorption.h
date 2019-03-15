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

#ifndef OPTICABSORPTION_H
#define OPTICABSORPTION_H

// MOOSE includes
#include "ADKernelValue.h"

template <ComputeStage compute_stage>
class OpticAbsorption;

declareADValidParams(OpticAbsorption);

template <ComputeStage compute_stage>
class OpticAbsorption : public ADKernelValue<compute_stage>
{
public:
  OpticAbsorption(const InputParameters & parameters);

protected:
  virtual ADResidual precomputeQpResidual() override;

private:

  const ADMaterialProperty(Real) & _absorption_coef;

  usingKernelMembers;
};

#endif
