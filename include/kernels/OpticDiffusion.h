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

#ifndef OPTICDIFFUSION_H
#define OPTICDIFFUSION_H

// MOOSE includes
#include "ADDiffusion.h"

template <ComputeStage compute_stage>
class OpticDiffusion;

declareADValidParams(OpticDiffusion);

template <ComputeStage compute_stage>
class OpticDiffusion : public ADDiffusion<compute_stage>
{
public:
  OpticDiffusion(const InputParameters & parameters);

protected:
  virtual ADResidual computeQpResidual() override;

private:

  const ADMaterialProperty(Real) & _diffusion_coef;

  usingKernelMembers;
};

#endif
