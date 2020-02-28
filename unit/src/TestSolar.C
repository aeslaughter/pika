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

// Implements tests presented in https://www.nrel.gov/docs/fy08osti/34302.pd

TEST(solar, julian_day)
{
  //  spa.year          = 2003;
  //  spa.month         = 10;
  //  spa.day           = 17;
  //  spa.hour          = 12;
  //  spa.minute        = 30;
  //  spa.second        = 30;
  //  spa.timezone      = -7.0;
  //  spa.delta_ut1     = 0;
  //  spa.delta_t       = 67;

  double jd = PikaUtils::julian_day(2003, 10, 17, 12, 30, 30, -7, 0);
  EXPECT_DOUBLE_EQ(jd, 2452930.312847222201526165008545);

  double dt = PikaUtils::delta_t(2003);
  EXPECT_DOUBLE_EQ(dt, 87.164800000000014);

  double jde = PikaUtils::julian_day_ephemeris(jd, 67.);
  EXPECT_DOUBLE_EQ(jde, 2452930.313622685149312019348145);

  double jc = PikaUtils::julian_century(jd);
  EXPECT_DOUBLE_EQ(jc, 0.037927798691915169670974);

  double jce = PikaUtils::julian_century_ephemeris(jde);
  EXPECT_DOUBLE_EQ(jce, 0.037927819922933585228275);

  double jme = PikaUtils::julian_millennium_ephemeris(jce);
  EXPECT_DOUBLE_EQ(jme, 0.003792781992293358436091);
}

TEST(solar,  earth_heliocentric_longitude)
{
  double L0 = PikaUtils::equation_ten<64>(PikaUtils::Table1::L0, 1);
  EXPECT_DOUBLE_EQ(L0, 174831416.50056037);
  double L1 = PikaUtils::equation_ten<34>(PikaUtils::Table1::L1, 1);
  EXPECT_DOUBLE_EQ(L1, 628331790351.9989);
  double L2 = PikaUtils::equation_ten<20>(PikaUtils::Table1::L2, 1);
  EXPECT_DOUBLE_EQ(L2, 58127.82598515583);
  double L3 = PikaUtils::equation_ten<7>(PikaUtils::Table1::L3, 1);
  EXPECT_DOUBLE_EQ(L3, 286.84079484062147);
  double L4 = PikaUtils::equation_ten<3>(PikaUtils::Table1::L4, 1);
  EXPECT_DOUBLE_EQ(L4, -119.96607179286497);
  double L5 = PikaUtils::equation_ten<1>(PikaUtils::Table1::L5, 1);
  EXPECT_DOUBLE_EQ(L5, -0.9999987317275395);

  double HL = PikaUtils::earth_heliocentric_longitude(1);
  EXPECT_NEAR(HL, 107.80163343198365, 1e-10);
}

TEST(solar,  earth_heliocentric_latitude)
{
  double B0 = PikaUtils::equation_ten<5>(PikaUtils::Table1::B0, 1);
  EXPECT_DOUBLE_EQ(B0, 83.6936473433185);
  double B1 = PikaUtils::equation_ten<2>(PikaUtils::Table1::B1, 1);
  EXPECT_DOUBLE_EQ(B1, 0.6273493435113817);

  //double HL = PikaUtils::earth_heliocentric_longitude(1);
  //EXPECT_NEAR(HL, 107.80163343198365, 1e-10);
}
