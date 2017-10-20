
#include "OpticRayProblem.h"
#include "OpticRayStudy.h"

template<>
InputParameters
validParams<OpticRayProblem>()
{
  InputParameters params = validParams<RayProblem>();
  return params;
}

OpticRayProblem::OpticRayProblem(const InputParameters & parameters) : RayProblem(parameters)
{
}

void
OpticRayProblem::solve()
{
  OpticRayStudy & optic_study = rayTracingStudy<OpticRayStudy>();

  // Solve the finite-element problem
  if (_solve_fe)
    FEProblem::solve();

  if (_solve_ray)
    //while (optic_study.hasOpticRay())
      _ray_system->solve();
}
