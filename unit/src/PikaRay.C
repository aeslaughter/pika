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
libMesh::Point INVALID_POINT(min_real, min_real, min_real);


/**
 * o = Ray origin
 * d = Ray direction 
 * x0 = Point on plane
 * n = Plane normal 
 *
 * v_i = o_i + d_i*t 
 * 
 */
libMesh::Point get_intersect(const Ray & ray, const Plane & plane)
{
  // Denominator 
  libMesh::Real n_dot_d = plane.normal() * ray.getDirection();
  

  // Case when line and plane are parallel
  if (n_dot_d == 0.)
    return INVALID_POINT;
  
  // Numerator
  libMesh::Real n_dot_x0_minus_o = plane.normal() * (plane.get_planar_point() - ray.getOrigin());

  // No intersection 
  if (n_dot_x0_minus_o == 0.)
    return INVALID_POINT;

  // Compute location
  libMesh::Real t = n_dot_x0_minus_o / n_dot_d;

  // Location is in negative dirction of the ray
  if (t < 0)
    return INVALID_POINT;

  return libMesh::Point(ray.getOrigin() + ray.getDirection() * t);
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
  EXPECT_EQ(c, Pika::INVALID_POINT); 
}

TEST(PikaRay, no_plane)
{
  Pika::Plane plane(libMesh::Point(1,0.5,0.5), libMesh::Point(1,0,0));
  Pika::Ray ray(libMesh::Point(1,0.25,0.25), libMesh::Point(0,1,0));
  libMesh::Point c = get_intersect(ray, plane);
  EXPECT_EQ(c, Pika::INVALID_POINT);
}

TEST(PikaRay, wrong_direction)
{
  Pika::Plane plane(libMesh::Point(1,0.5,0.5), libMesh::Point(1,0,0));
  Pika::Ray ray(libMesh::Point(0,0.5,0.5), libMesh::Point(-1,0,0));
  libMesh::Point c = get_intersect(ray, plane);
  EXPECT_EQ(c, Pika::INVALID_POINT);
}

TEST(PikaRay, find_point)
{
  Pika::Plane plane(libMesh::Point(1,0.5,0.5), libMesh::Point(1,0,0));
  Pika::Ray ray(libMesh::Point(0,0.5,0.), libMesh::Point(1,0,0.5));
  libMesh::Point c = get_intersect(ray, plane);
  EXPECT_EQ(c, libMesh::Point(1, 0.5, 0.5));

}
