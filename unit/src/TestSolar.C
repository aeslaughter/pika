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

// Implements tests presented in NREL/TP-560-34302
// https://www.nrel.gov/docs/fy08osti/34302.pd
//
// The "gold" values were created using the SPA code from the above report
// https://rredc.nrel.gov/solar/codesandalgorithms/spa/
TEST(PikaUtils, solar)
{
  double jd = PikaUtils::julian_day(2003, 10, 17, 12, 30, 30, -7, 0);
  EXPECT_DOUBLE_EQ(jd, 2452930.312847222201526);

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

  double L0 = PikaUtils::equation_ten<64>(PikaUtils::Table1::L0, jme);
  EXPECT_DOUBLE_EQ(L0, 172067561.526585549116134643554688);
  double L1 = PikaUtils::equation_ten<34>(PikaUtils::Table1::L1, jme);
  EXPECT_DOUBLE_EQ(L1, 628332010650.051147460937500000000000);
  double L2 = PikaUtils::equation_ten<20>(PikaUtils::Table1::L2, jme);
  EXPECT_DOUBLE_EQ(L2, 61368.682493387161230202764273);
  double L3 = PikaUtils::equation_ten<7>(PikaUtils::Table1::L3, jme);
  EXPECT_DOUBLE_EQ(L3, -26.902818812449339702652651);
  double L4 = PikaUtils::equation_ten<3>(PikaUtils::Table1::L4, jme);
  EXPECT_DOUBLE_EQ(L4, -121.279536272762925364077091);
  double L5 = PikaUtils::equation_ten<1>(PikaUtils::Table1::L5, jme);
  EXPECT_DOUBLE_EQ(L5, -0.999998731727539502678326);

  double L = PikaUtils::earth_heliocentric_longitude(jme);
  EXPECT_DOUBLE_EQ(L, 24.0182616916793989503275955);
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
