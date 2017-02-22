#ifndef COEFFICIENTMATERIALDERIVATIVE_H
#define COEFFICIENTMATERIALDERIVATIVE_H

#include "TimeDerivative.h"

class CoefficientMaterialDerivative;

template<>
InputParameters validParams<CoefficientMaterialDerivative>();

/**
 *
 */
class  CoefficientMaterialDerivative: public TimeDerivative
{
public:
  CoefficientMaterialDerivative(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;


  const unsigned int _mesh_dim;
  std::vector<MooseVariable *> _deformation_velocities;
  const MaterialProperty<Real> & _coefficient;

  RealVectorValue _velocity;

};

#endif // COEFFICIENTMATERIALDERIVATIVE_H
