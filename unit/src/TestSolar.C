//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "gtest/gtest.h"
#include "solar.h"

TEST(solar, julian_day)
{
  EXPECT_EQ(PikaUtils::julian_day(1980, 6, 24), 2444414.5);

  double jd = PikaUtils::julian_day(1980, 1, 1);
  EXPECT_EQ(jd, 2444239.5);

  double jde = PikaUtils::julian_day_ephemeris(2444239.5, 1980);
  EXPECT_EQ(jde, 2444239.500716666691);

  double jc = PikaUtils::julian_century(jd);
  EXPECT_EQ(jc, -0.20001368925393567255);

  double jce = PikaUtils::julian_century_ephemeris(jde);
  EXPECT_EQ(jce, -0.20001366963267103172);

  double jme = PikaUtils::julian_millennium_ephemeris(jce);
  EXPECT_EQ(jme, -0.020001366963267103172);
}
