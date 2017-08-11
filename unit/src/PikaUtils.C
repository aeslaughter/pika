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

// MOOSE includes
#include "gtest/gtest.h"

// Pika includes
#include "PikaUtils.h"

TEST(PikaUtils, snell)
{
  libMesh::Point in(2,0,2);
  libMesh::Point normal(0,0,-2);
  EXPECT_EQ(libMesh::Point(0.471,0,0.882), PikaUtils::snell(in, normal, 1, 1.5));

}
