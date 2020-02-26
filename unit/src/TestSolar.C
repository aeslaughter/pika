//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include <math.h>
#include "gtest/gtest.h"
#include "solar.h"

TEST(solar, julian_day)
{
  double jd = PikaUtils::julian_day(1980, 6, 24, 4, 24, 2);
  EXPECT_NEAR(jd, 2444414.683359552, 1e-4);

  double jde = PikaUtils::julian_day_ephemeris(jd, 1980);
  EXPECT_NEAR(jde, 2444414.683948889, 2e-4);

  double jc = PikaUtils::julian_century(jd);
  EXPECT_NEAR(jc, -0.19521743026551197, 1e-4);

  double jce = PikaUtils::julian_century_ephemeris(jde);
  EXPECT_NEAR(jce, -0.19521741413035157, 1e-4);

  double jme = PikaUtils::julian_millennium_ephemeris(jce);
  EXPECT_NEAR(jme, -0.019521741413035157, 1e-4);
}

TEST(solar,  earth_heliocentric_longitude)
{
  double L0 = PikaUtils::equation_ten<64>(PikaUtils::Table1::L0, 1);
  EXPECT_DOUBLE_EQ(L0, 174831416.50056037);
  double L1 = PikaUtils::equation_ten<34>(PikaUtils::Table1::L1, 1);
  EXPECT_DOUBLE_EQ(L1, 628331790351.9989);
}
