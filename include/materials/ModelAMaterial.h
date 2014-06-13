/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef MODELAMATERIAL_H
#define MODELAMATERIAL_H

// MOOSE includes
#include "Material.h"

// Forward declerations
class ModelAMaterial;

template<>
InputParameters validParams<ModelAMaterial>();

/**
 *
 */
class ModelAMaterial : public Material
{
public:

  /**
   * Class constructor
   * @param prop_name
   */
  ModelAMaterial(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~ModelAMaterial();

protected:
  virtual void computeQpProperties();

private:

  VariableValue & _phase;
  VariableGradient & _grad_phase;
  VariableValue & _dT;

  Real _kappa_1;
  Real _kappa_2;
  Real _tau_param;
  Real _c;
  Real _alpha;
  Real _N;
  Real _theta;
  Real _D_T_param;

  MaterialProperty<RealTensorValue> & _D;
  MaterialProperty<Real> & _tau;
  MaterialProperty<Real> & _D_T;
  MaterialProperty<Real> & _m;

};

#endif //MODELAMATERIAL_H
