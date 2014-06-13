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

#include "ModelAMaterial.h"

template<>
InputParameters validParams<ModelAMaterial>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("phase_field_variable", "The phase-field variable to couple");
  params.addRequiredCoupledVar("dimensionless_undercooling_variable", "The dimensionless undercooling variable to couple");
  params.addParam<Real>("kappa_1", 0.9, "...(kappa_1)");
  params.addParam<Real>("kappa_2", 30, "...(kappa_2)");
  params.addParam<Real>("tau", 3e-4, "...(tau)");
  params.addParam<Real>("c", 0.02, "...(c)");
  params.addParam<Real>("alpha", 0.015, "...(alpha)");
  params.addParam<Real>("N", 6, "Symmetry (N)");
  params.addParam<Real>("theta", 0.39269908169, "...Pi/8 (theta)");
  params.addParam<Real>("D_T", 2.25, "...(D_{T})");
  return params;
}

ModelAMaterial::ModelAMaterial(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    _phase(coupledValue("phase_field_variable")),
    _grad_phase(coupledGradient("phase_field_variable")),
    _dT(coupledValue("dimensionless_undercooling_variable")),
    _kappa_1(getParam<Real>("kappa_1")),
    _kappa_2(getParam<Real>("kappa_2")),
    _tau_param(getParam<Real>("tau")),
    _c(getParam<Real>("c")),
    _alpha(getParam<Real>("alpha")),
    _N(getParam<Real>("N")),
    _theta(getParam<Real>("theta")),
    _D_T_param(getParam<Real>("D_T")),
    _D(declareProperty<RealTensorValue>("D")),
    _tau(declareProperty<Real>("tau")),
    _D_T(declareProperty<Real>("D_T")),
    _m(declareProperty<Real>("m"))
{
}

ModelAMaterial::~ModelAMaterial()
{
  _tau[_qp] = _tau_param;

  _D_T[_qp] = _D_T_param;

  _m[_qp] = _phase[_qp] - 0.5 - _kappa_1/libMesh::pi * std::atan(_kappa_2*_dT[_qp]);


  Real psi = _theta + std::atan(_grad_phase[_qp](1) / _grad_phase[_qp](2));
  Real Phi = std::tan(0.5*_N*psi);
  Real beta = (1 - Phi*Phi) / (1 + Phi*Phi);
  Real dbeta_dpsi = -_N * 2. * Phi / (1. + Phi*Phi);

  _D[_qp](0,0) = 1 + _c*beta;
  _D[_qp](0,1) = -_c*dbeta_dpsi;
  _D[_qp](1,0) = _c*dbeta_dpsi;
  _D[_qp](1,1) = 1 + _c*beta;
  _D[_qp] *= _alpha*_alpha*(1 + _c*beta);
}

void
ModelAMaterial::computeQpProperties()
{
}
