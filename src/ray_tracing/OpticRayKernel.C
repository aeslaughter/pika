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
    const ExecuteMooseObjectWarehouse<UserObject> & objects = _ray_problem.getUserObjects();
    const UserObjectName & name = getParam<UserObjectName>("tracker");
    _tracker = static_cast<OpticRayTracker *>(objects.getActiveObject(name).get());
  }
}

void
OpticRayKernel::onSegment(const Elem * elem, const Point & start, const Point & end, bool ends_in_elem)
{
  std::cout << "OpticRayKernel::onSegment()\n";
  std::cout << "  Elem: " << elem->id();
  std::cout << " Start: "; start.print();
  std::cout << " End: "; end.print();
  std::cout << " ends_in_elem = " << ends_in_elem;
  std::cout << std::endl;
  return;


  Real threshold = 0.5;

  /*
  if (start == _ray->start())
  {
    _tracker->addSegment(start, end, _ray->id());
    return;
  }
  */

  Point mid = start + (end - start)/2.; // TODO: interp on phase
  _ray_problem.reinitElemPhys(elem, {start, mid, end}, _tid);


  if ((_phase[0] < threshold && _phase[2] > threshold) ||
      (_phase[0] > threshold && _phase[2] < threshold))
  {
    Point origin = end - start;
    Point direction = PikaUtils::snell(origin, _grad_phase[1], _refractive_index[1], _refractive_index[0]);


    std::cout << "START: "; start.print(); _ray->start().print(); std::cout << std::endl;
    std::cout << "  MID: "; mid.print(); std::cout << std::endl;
    std::cout << "  END: "; end.print(); std::cout << std::endl;
    std::cout << "  NOR: "; _grad_phase[1].print(); std::cout << std::endl;
    std::cout << "  ORG: "; origin.print(); std::cout << std::endl;
    std::cout << "  DIR: "; direction.print(); std::cout << std::endl;

    _ray->setShouldContinue(false);
    _ray->setEndsWithinMesh();
    _ray->setEnd(mid);

    if (_tracker)
      _tracker->addSegment(start, mid, _ray->id());


    _study.addOpticRay(mid, direction, elem->id(), _ray->id());
  }

  //else if (_tracker)
  //  _tracker->addSegment(start, end, _ray->id());


}

/*
void
OpticRayKernel::setRay(const std::shared_ptr<Ray> & ray)
{
  RayKernel::setRay(ray);

  _ray_data = &_ray->data()[0];
}*/
