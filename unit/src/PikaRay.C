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

/*
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
*/
