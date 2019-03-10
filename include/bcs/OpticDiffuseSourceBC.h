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

#ifndef OPTICDIFFUSESOURCEBC_H
#define OPTICDIFFUSESOURCEBC_H

// MOOSE includes
#include "ADIntegratedBC.h"

template <ComputeStage compute_stage>
class OpticDiffuseSourceBC;

declareADValidParams(OpticDiffuseSourceBC);

template <ComputeStage compute_stage>
class OpticDiffuseSourceBC : public ADIntegratedBC<compute_stage>
{
public:
  OpticDiffuseSourceBC(const InputParameters & parameters);

protected:
  virtual ADResidual computeQpResidual() override;

private:

  const ADMaterialProperty(Real) & _transmittance;

  const ADVariableValue & _incoming_flux;

  usingIntegratedBCMembers;
};

#endif
