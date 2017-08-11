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
  {
    libMesh::Point in(2,0,2);
    libMesh::Point normal(0,0,-2);
    libMesh::Point s2 = PikaUtils::snell(in, normal, 1, 1.5);
    EXPECT_TRUE(s2.relative_fuzzy_equals(libMesh::Point(0.471404520791,0,0.881917103688)));
  }

  {
    libMesh::Point in(4,1,1);
    libMesh::Point normal(0,-2,-1);
    libMesh::Point s2 = PikaUtils::snell(in, normal, 1, 1.5);
    EXPECT_TRUE(s2.relative_fuzzy_equals(libMesh::Point(0.628539361055,0.661393354975,0.409264097619)));
  }
}
