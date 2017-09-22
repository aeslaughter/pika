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

// Pika types
#include "PikaTypes.h"
#include "PikaUtils.h"
#include "OpticRayStudy.h"

// libMesh includes
#include "libmesh/mesh_tools.h"

// MOOSE Includes
#include "MooseMesh.h"
#include "RayProblem.h"

template <>
InputParameters
validParams<OpticRayStudy>()
{
  InputParameters params = validParams<RayTracingStudy>();
  params.addParam<std::vector<Point>>("start_points", "The points to initiate rays.");
  params.addParam<std::vector<Point>>("start_directions", "The direction the rays shall emit.");
  return params;
}

OpticRayStudy::OpticRayStudy(const InputParameters & parameters)
  : RayTracingStudy(parameters),
    _bounding_box(_ray_problem.boundingBox())
{
  //if (_start_points.size() != _start_directions.size())
  //  mooseError("start_points length must match start_directions length!");

}

void
OpticRayStudy::addOpticRay(const Point & origin, const Point & direction,
                           const dof_id_type elem_id, const unsigned int ray_id)
{

  std::cout << "BEFORE: OpticRayStudy::addOpticRay " << hasOpticRay() << std::endl;

  libMesh::Point end = getIntersect(origin, direction);
  if (end != PikaTypes::INVALID_POINT)
  {
    std::shared_ptr<Ray> ray = std::make_shared<Ray>(origin, end, _num_groups);
    ray->setID(ray_id);
    ray->setStartingElem(_fe_problem.mesh().elemPtr(elem_id));
    _optic_rays.push_back(ray);
    std::cout << "IN HERE" << std::endl;
  }
  std::cout << "AFTER: OpticRayStudy::addOpticRay " << hasOpticRay() << std::endl;

  // TODO: error here for invalid end point

  /*
  std::cout << "OpticRayStudy::addOpticRay " << hasOpticRay() << std::endl;
  _start_points.push_back(origin);
  _start_directions.push_back(direction);
  std::cout << "OpticRayStudy::addOpticRay " << hasOpticRay() << std::endl;
  */
}


void
OpticRayStudy::initialSetup()
{
  // Define planes (left, front, bottom, right, back, top)
  std::vector<PikaUtils::NormalPlane> planes;
  _planes.emplace_back(_bounding_box.min(), Point(1,0,0));
  _planes.emplace_back(_bounding_box.min(), Point(0,1,0));
  _planes.emplace_back(_bounding_box.min(), Point(0,0,1));
  _planes.emplace_back(_bounding_box.max(), Point(-1,0,0));
  _planes.emplace_back(_bounding_box.max(), Point(0,-1,0));
  _planes.emplace_back(_bounding_box.max(), Point(0,0,-1));
  _id = 0;

  // TODO: Loop over boundary are create rays that emit from centroid of elements
  const Point & origin = getParam<std::vector<Point>>("start_points")[0];
  const Point & direction = getParam<std::vector<Point>>("start_directions")[0];
  addOpticRay(origin, direction, 0, 0);

}


void
OpticRayStudy::generateRays()
{
  std::cout << "OpticRayStudy::generateRays() " << _optic_rays.size() << std::endl;

  std::vector<std::shared_ptr<Ray>> rays = _optic_rays;
  _optic_rays.clear();
  chunkyTraceAndBuffer(rays);

}

Point
OpticRayStudy::getIntersect(const Point & origin, const Point & direction) const
{
  for (const auto & plane : _planes)
  {
    libMesh::Point end = PikaUtils::get_intersect(origin, direction, plane);
    if (end != PikaTypes::INVALID_POINT && _bounding_box.contains_point(end))
      return end;
  }
  return PikaTypes::INVALID_POINT;
}

bool
OpticRayStudy::hasOpticRay()
{
  return !_optic_rays.empty();
}
