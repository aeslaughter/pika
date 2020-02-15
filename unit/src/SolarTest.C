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
  EXPECT_EQ(PikaUtils::julian_day(1980, 1, 1), 2444239.5);
}
