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
    _start_points(getParam<std::vector<Point>>("start_points")),
    _start_directions(getParam<std::vector<Point>>("start_directions")),
    _bounding_box(_ray_problem.boundingBox())
{
  if (_start_points.size() != _start_directions.size())
    mooseError("start_points length must match start_directions length!");
}

void
OpticRayStudy::addOpticRay(const Point & origin, const Point & direction)
{
  _start_points.push_back(origin);
  _start_directions.push_back(direction);
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
}

void
OpticRayStudy::generateRays()
{
  std::vector<std::shared_ptr<Ray>> rays;

  for (std::size_t i = 0; i < _start_points.size(); ++i)
  {
    libMesh::Point end = getIntersect(_start_points[i], _start_directions[i]);
    if (end != PikaTypes::INVALID_POINT)
    {
      auto ray = std::make_shared<Ray>(_start_points[i], end, _num_groups);
      ray->setID(_id);
    //  ray->setEndsWithinMesh(); // this may not be true for unstructured
      ray->setStartingElem(_fe_problem.mesh().elemPtr(0)); // TODO: loop over elements on boundary

      //ray->start().print();
      //ray->end().print();

      rays.emplace_back(ray);
      _id++;
    }
  }

  chunkyTraceAndBuffer(rays);

  _start_points.clear();
  _start_directions.clear();
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
