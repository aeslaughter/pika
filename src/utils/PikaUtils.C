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
#include "PikaUtils.h"
#include "PikaTypes.h"

// libMesh includes
#include "libmesh/libmesh_common.h"

namespace PikaUtils
{

NormalPlane::NormalPlane(const libMesh::Point & p, const libMesh::Point & n) :
    libMesh::Plane(p, n)
{
}

libMesh::Point
NormalPlane::normal() const
{
  return libMesh::Plane::unit_normal(_zero);
}


libMesh::Point
get_intersect(const libMesh::Point & origin, const libMesh::Point & direction, const NormalPlane & plane)
{
  // Denominator 
  libMesh::Real n_dot_d = plane.normal() * direction;
  

  // Case when line and plane are parallel
  if (n_dot_d == 0.)
    return PikaTypes::INVALID_POINT;
  
  // Numerator
  libMesh::Real n_dot_x0_minus_o = plane.normal() * (plane.get_planar_point() - origin);

  // No intersection 
  if (n_dot_x0_minus_o == 0.)
    return PikaTypes::INVALID_POINT;

  // Compute location
  libMesh::Real t = n_dot_x0_minus_o / n_dot_d;

  // Location is in negative dirction of the ray
  if (t < 0)
    return PikaTypes::INVALID_POINT;

  return libMesh::Point(origin + direction * t);
}

} // PikaUtils
