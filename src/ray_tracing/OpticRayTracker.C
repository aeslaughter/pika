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
#include "OpticRayTracker.h"

// libMesh includes
#include "libmesh/mesh_tools.h"

// MOOSE Includes
#include "MooseMesh.h"
#include "RayProblem.h"

template <>
InputParameters
validParams<OpticRayTracker>()
{
  InputParameters params = validParams<GeneralUserObject>();
  return params;
}

OpticRayTracker::OpticRayTracker(const InputParameters & parameters)
  : GeneralUserObject(parameters)
{
}


void
OpticRayTracker::initialSetup()
{
}

void
OpticRayTracker::timestepSetup()
{
}


void
OpticRayTracker::addSegment(const Point & start, const Point & end, unsigned int id)
{
  //Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);

  std::cout << "OpticRayStudy::addSegment - "; start.print();
  std::cout << std::endl;

  _segments[id].emplace_back(std::make_pair(start, end));
}


const std::map<unsigned int, std::vector<std::pair<Point, Point>>> &
OpticRayTracker::getSegments() const
{
  return _segments;
}
