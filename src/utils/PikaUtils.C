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

/**
 * https://en.wikipedia.org/wiki/Snell%27s_law
 */
libMesh::Point
snell(const libMesh::Point & incoming, const libMesh::Point & normal, const libMesh::Real & n_1, const libMesh::Real & n_2)
{
  libMesh::Point l = incoming.unit();
  libMesh::Point n = normal.unit();
  libMesh::Real c = std::abs(-n * l);
  libMesh::Real r = n_1 / n_2;
  return r*l + (r*c - std::sqrt(1 - r*r * (1-c*c)))*n;

  /*
  const libMesh::Point n = normal.unit();
  const libMesh::Point l = incoming.unit();
  libMesh::Real r = n1/n2;
  libMesh::Point c = n * l;
  return libMesh::Point(r*l + (r*c * std::sqrt(1 - r*r*(1 - c*c)))*n);
  */

}

libMesh::Real
clamp(libMesh::Real x, const libMesh::Real & lowerlimit, const libMesh::Real & upperlimit)
{
    if (x < lowerlimit)
      x = lowerlimit;
    if (x > upperlimit)
      x = upperlimit;
    return x;
}

libMesh::Real
smoothstep(const libMesh::Real & in, const libMesh::Real & edge0, const libMesh::Real & edge1)
{
  // Scale, bias and saturate x to 0..1 range
  libMesh::Real x = clamp((in - edge0)/(edge1 - edge0), 0.0, 1.0);
  // Evaluate polynomial
  return x*x*(3 - 2*x);
}


} // PikaUtils
