#ifndef OPTICRAYPROBLEM_H
#define OPTICRAYPROBLEM_H

#include "RayProblem.h"

class OpticRayProblem;

template<>
InputParameters validParams<OpticRayProblem>();

class OpticRayProblem : public RayProblem
{
public:
  OpticRayProblem(const InputParameters & parameters);
  virtual void solve() override;

};

#endif
