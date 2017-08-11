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

// MOOSE includes
#include "RayProblem.h"
#include "Assembly.h"

template<>
InputParameters
validParams<OpticRayKernel>()
{
  InputParameters params = validParams<RayKernel>();
  params.addCoupledVar("refractive_index", "The field variable containing the refractive index.");
//  params.addCoupledVar("phase", "The field variable containing the phase.");

  return params;
}

OpticRayKernel::OpticRayKernel(const InputParameters & parameters) :
    RayKernel(parameters),
    _refractive_index(coupledValue("refractive_index")),
  //  _phase(coupledValue("phase")),
  //  _grad_phase(coupledGradient("phase")),
    _study(_ray_problem.rayTracingStudy<OpticRayStudy>())
{
}

void
OpticRayKernel::onSegment(const Elem * elem, const Point & start, const Point & end, bool ends_in_elem)
{

  Point mid = start + (end - start);
  _ray_problem.reinitElemPhys(elem, {start, mid, end}, _tid);

  if (_refractive_index[0] != _refractive_index[1])
  {
    Point origin = end - start;
    RealVectorValue normal(-2,0,0);// = _grad_phase[1] / _grad_phase[1].norm();
    Point direction = PikaUtils::snell(origin, normal, _refractive_index[0], _refractive_index[1]);
    Point end = _study.getIntersect(origin, direction);
    _ray->setEnd(end);
//    std::cout << "ID: " << elem->id() << " " << _refractive_index[0] << " " << _refractive_index[1] << _refractive_index[2] << std::endl;
  }

  std::cout << "ID: " << elem->id();
  end.print();
  std::cout << std::endl;

}

/*
void
OpticRayKernel::setRay(const std::shared_ptr<Ray> & ray)
{
  RayKernel::setRay(ray);

  _ray_data = &_ray->data()[0];
}*/
