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
    libMesh::Point in(std::sqrt(2.)/2., std::sqrt(2.)/2.,2);
    libMesh::Point normal(0,1,0);
    libMesh::Point s2 = PikaUtils::snell(in, normal, 1, 0.9);
    EXPECT_TRUE(s2.relative_fuzzy_equals(libMesh::Point(0.6363696, -0.771632, 0.)));
  }
}
