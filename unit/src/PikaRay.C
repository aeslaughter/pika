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

// libMesh includes
#include "libmesh/point.h"
#include "libmesh/plane.h"

// MOOSE includes 
#include "gtest/gtest.h"

namespace Pika
{

class Ray
{
public:
  Ray(const libMesh::Point & origin, const libMesh::Point & direction);

  const libMesh::Point & getOrigin() const { return _origin; }
  const libMesh::Point & getDirection() const { return _direction; }
  
protected:
  const libMesh::Point _origin;
  
  const libMesh::Point _direction;
  
};

Ray::Ray(const libMesh::Point & origin, const libMesh::Point & direction) :
    _origin(origin),
    _direction(direction.unit())
{
}

class Plane: public libMesh::Plane
{
public:
  Plane(const libMesh::Point & p, const libMesh::Point & n);
  libMesh::Point normal() const { return libMesh::Plane::unit_normal(_zero); }

private:
  libMesh::Point _zero;
};

Plane::Plane(const libMesh::Point & p, const libMesh::Point & n) : libMesh::Plane(p, n)
{
}


libMesh::Real min_real = std::numeric_limits<libMesh::Real>::min();
libMesh::Real max_real = std::numeric_limits<libMesh::Real>::max();

libMesh::Point LINE_PARALLEL(min_real, min_real, min_real);
libMesh::Point LINE_NO_INTERSECTION(max_real, max_real, max_real);


/**
 *
 *
 *
 * 
 */
libMesh::Point get_intersect(const Ray & ray, const Plane & plane)
{
  //
  libMesh::Real l_dot_n = ray.getDirection() * plane.normal();

  // Case when line and plane are parallel
  if (l_dot_n == 0.)
    return LINE_PARALLEL;

  libMesh::Real p0_minus_l0_dot_n = (ray.getOrigin() - plane.get_planar_point()) * plane.normal();

  // No intersection 
  if (p0_minus_l0_dot_n == 0.)
    return LINE_NO_INTERSECTION;


  libMesh::Real d = p0_minus_l0_dot_n / l_dot_n;
  return libMesh::Point(d * ray.getDirection() + ray.getOrigin());
  
  
}


  
} // namespace Pika
  
                                       


                                       
TEST(PikaRay, basic)
{
  Pika::Ray ray(libMesh::Point(0,0,0), libMesh::Point(1,1,1));
  EXPECT_EQ(ray.getOrigin(), libMesh::Point(0,0,0));
  EXPECT_EQ(ray.getDirection(), libMesh::Point(1./std::sqrt(3.),
                                               1./std::sqrt(3.),
                                               1./std::sqrt(3.)));

  Pika::Ray ray2(libMesh::Point(1,2,3), libMesh::Point(2,4,0));


  EXPECT_EQ(ray2.getOrigin(), libMesh::Point(1,2,3));
  EXPECT_EQ(ray2.getDirection(), libMesh::Point(2./std::sqrt(20.),
                                                4./std::sqrt(20.),
                                                0.)); 
}

TEST(PikaRay, line_parallel)
{
  Pika::Plane plane(libMesh::Point(0,1,0), libMesh::Point(1,0,0));
  Pika::Ray ray(libMesh::Point(0,0,0), libMesh::Point(0,1,0));
  libMesh::Point c = get_intersect(ray, plane);
  EXPECT_EQ(c, Pika::LINE_PARALLEL);
  

  

}
