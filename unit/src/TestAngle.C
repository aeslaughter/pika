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

using namespace PikaUtils;

TEST(Angle, radian)
{
  const Angle a(M_PI, Angle::RAD);
  EXPECT_DOUBLE_EQ(a.rad(), M_PI);
  EXPECT_DOUBLE_EQ(a.deg(), 180.);
}

TEST(Angle, radian_over)
{
  const Angle a(3*M_PI, Angle::RAD);
  EXPECT_DOUBLE_EQ(a.rad(), 3*M_PI);
  EXPECT_DOUBLE_EQ(a.deg(), 540.);
}

TEST(Angle, radian_over_limited)
{
  const Angle a(3*M_PI, Angle::RAD, Angle::LIMIT);
  EXPECT_DOUBLE_EQ(a.rad(), M_PI);
  EXPECT_DOUBLE_EQ(a.deg(), 180.);
}

TEST(Angle, degree)
{
  const Angle a(180., Angle::DEG);
  EXPECT_DOUBLE_EQ(a.rad(), M_PI);
  EXPECT_DOUBLE_EQ(a.deg(), 180.);
}

TEST(Angle, degree_over)
{
  const Angle a(720, Angle::DEG);
  EXPECT_DOUBLE_EQ(a.rad(), 4*M_PI);
  EXPECT_DOUBLE_EQ(a.deg(), 720.);
}

TEST(Angle, degree_over_limit)
{
  const Angle a(540., Angle::DEG, Angle::LIMIT);
  EXPECT_DOUBLE_EQ(a.rad(), M_PI);
  EXPECT_DOUBLE_EQ(a.deg(), 180.);
}
