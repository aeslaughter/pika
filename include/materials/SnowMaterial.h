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
#include "ADMaterial.h"

class SnowMaterial : public ADMaterial
{
public:
  static InputParameters validParams();

  SnowMaterial(const InputParameters & parameters);

  virtual void computeQpProperties() override;

protected:

  const ADVariableValue & _temperature;
  const ADMaterialProperty<Real> & _density;
  ADMaterialProperty<Real> & _thermal_conductivity;
  ADMaterialProperty<Real> & _specific_heat;
};
