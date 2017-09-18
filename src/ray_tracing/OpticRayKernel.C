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
#include "OpticRayStudy.h"
#include "OpticRayTracker.h"

// MOOSE includes
#include "RayProblem.h"
#include "Assembly.h"

template<>
InputParameters
validParams<OpticRayKernel>()
{
  InputParameters params = validParams<RayKernel>();
  params.addCoupledVar("refractive_index", "The field variable containing the refractive index.");
  params.addCoupledVar("phase", "The field variable containing the phase.");
  params.addParam<UserObjectName>("tracker", "OpticRayTracker object for output (optional).");
  return params;
}

OpticRayKernel::OpticRayKernel(const InputParameters & parameters) :
    RayKernel(parameters),
    _refractive_index(coupledValue("refractive_index")),
    _phase(coupledValue("phase")),
    _grad_phase(coupledGradient("phase")),
    _study(_ray_problem.rayTracingStudy<OpticRayStudy>()),
    _tracker(nullptr)
{
  if (isParamValid("tracker"))
  {
    std::cout << "TRACKER!!!!!!!!!!!!!" << std::endl;
    const ExecuteMooseObjectWarehouse<UserObject> & objects = _ray_problem.getUserObjects();
    const UserObjectName & name = getParam<UserObjectName>("tracker");
    _tracker = static_cast<OpticRayTracker *>(objects.getActiveObject(name).get());
  }
}

void
OpticRayKernel::onSegment(const Elem * elem, const Point & start, const Point & end, bool ends_in_elem)
{
  //_ray_problem.setActiveElementalMooseVariables({getVar("refractive_index", 0)}, _tid);
  Point mid = start + (end - start);
  _ray_problem.reinitElemPhys(elem, {start, mid, end}, _tid);

  if (_phase[0] != _phase[2])
  {
    Point origin = end - start;
    Point direction = PikaUtils::snell(origin, _grad_phase[1], _refractive_index[0], _refractive_index[2]);
    Point new_end = _study.getIntersect(origin, direction);
    _ray->setEnd(new_end);

    if (_tracker)
      _tracker->addSegment(start, mid, _ray->id());
  }

  if (_tracker)
    _tracker->addSegment(start, end, _ray->id());


  //std::cout << "ID: " << elem->id();
  //end.print();
  //std::cout << std::endl;

}

/*
void
OpticRayKernel::setRay(const std::shared_ptr<Ray> & ray)
{
  RayKernel::setRay(ray);

  _ray_data = &_ray->data()[0];
}*/
