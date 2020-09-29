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
#include "ADDiffusion.h"

class OpticDiffusion : public ADDiffusion
{
public:
  static InputParameters validParams();

  OpticDiffusion(const InputParameters & parameters);

protected:
  virtual ADRealVectorValue precomputeQpResidual() override;

private:

  const ADMaterialProperty<Real> & _diffusion_coef;
  //const ADMaterialProperty(Real) & _absorption_coef;
  //const ADMaterialProperty(Real) & _scattering_coef;
  //const ADMaterialProperty(Real) & _anisotropy;
};
