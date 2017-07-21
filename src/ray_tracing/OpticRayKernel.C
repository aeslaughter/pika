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

// Pika includes
#include "OpticRayKernel.h"

// MOOSE includes
#include "RayProblem.h"
#include "Assembly.h"

template<>
InputParameters
validParams<OpticRayKernel>()
{
  InputParameters params = validParams<RayKernel>();
  params.addCoupledVar("refractive_index", "The field variable containing the refractive index.");
  return params;
}

OpticRayKernel::OpticRayKernel(const InputParameters & parameters) :
    RayKernel(parameters),
    _value(coupledValue("refractive_index"))//,
    // _refractive_var(getCoupledMooseVars()[0])
{
}

void
OpticRayKernel::onSegment(const Elem * elem, const Point & start, const Point & end, bool ends_in_elem)
{
  // std::vector<Point> points = {start, end};
  //_ray_problem.assembly(_tid).reinitAtPhysical(elem, points);

  std::cout << _value.size() << std::endl;
  
}


