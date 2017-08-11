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

    RealVectorValue normal(1,0,0);// = _grad_phase[1] / _grad_phase[1].norm();
//    normal.print();
    Point diff = end - start;
    Real theta0 = std::acos(normal*diff / (normal.norm()*diff.norm()));
    std::cout << "THETA0 = " << theta0 << std::endl;


//    Real theta = std::asin(std::sin(std::pi/2.)*_refractive_index[0]/_refractive_index[1]));
//    std::cout << "THETA = " << theta  << std::endl;
//    Point end = _study.getIntersect(mid)

    std::cout << "ID: " << elem->id() << " " << _refractive_index[0] << " " << _refractive_index[1] << _refractive_index[2] << std::endl;
  }

}

/*
void
OpticRayKernel::setRay(const std::shared_ptr<Ray> & ray)
{
  RayKernel::setRay(ray);

  _ray_data = &_ray->data()[0];
}*/
