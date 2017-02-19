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

#ifndef IBEXSNOWMATERIAL_H
#define IBEXSNOWMATERIAL_H

// MOOSE includes
#include "Material.h"

// Forward declerations
class IbexSnowMaterial;

template<>
InputParameters validParams<IbexSnowMaterial>();

/**
 *
 */
class IbexSnowMaterial : public Material
{
public:

  /**
   * Class constructor
   * @param prop_name
   */
  IbexSnowMaterial(const InputParameters & parameters);

protected:
  void computeQpProperties();

  Real poissonsRatioBar(const Real & density, const Real & temperature);

  const VariableValue & _temperature;



  const VariableValue & _input_density;

  bool _compute_conductivity;

  const Real _input_conductivity;
  bool _compute_specific_heat;
  const Real _input_specific_heat;
  MaterialProperty<Real> & _density;
  MaterialProperty<Real> & _conductivity;
  MaterialProperty<Real> & _specific_heat;

  bool _use_conductivity_variable;
  const VariableValue & _conductivity_variable;

  const MooseEnum & _viscosity_model;
  Real _eta_s;

  MaterialProperty<Real> & _viscosity;
  MaterialProperty<Real> & _poissons_ratio;
  MaterialProperty<Real> & _lambda;

  const Real & _density_reference;
  const Real & _poissons_ratio_max;
  const Real & _density_reference_coefficient;
  const Real & _temperature_reference_coefficient;


};

#endif //IBEXSNOWMATERIAL_H
