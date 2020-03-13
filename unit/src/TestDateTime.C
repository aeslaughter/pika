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
using namespace PikaUtils::SPA;

TEST(DateTime, add)
{
  DateTime t("2020-02-29T19:42:35");
  EXPECT_EQ(t.year(), 2020);
  EXPECT_EQ(t.month(), 2);
  EXPECT_EQ(t.day(), 29);
  EXPECT_EQ(t.hour(), 19);
  EXPECT_EQ(t.minute(), 42);
  EXPECT_EQ(t.second(), 35);

  t.add(0, 0, 1, 0, 0, 0);
  EXPECT_EQ(t.year(), 2020);
  EXPECT_EQ(t.month(), 3);
  EXPECT_EQ(t.day(), 1);
  EXPECT_EQ(t.hour(), 19);
  EXPECT_EQ(t.minute(), 42);
  EXPECT_EQ(t.second(), 35);

  t.add(0, 0, 0, 0, 0, 172800);
  EXPECT_EQ(t.year(), 2020);
  EXPECT_EQ(t.month(), 3);
  EXPECT_EQ(t.day(), 3);
  EXPECT_EQ(t.hour(), 19);
  EXPECT_EQ(t.minute(), 42);
  EXPECT_EQ(t.second(), 35);

  t.add(0, 0, 0, 0, 0, 60.12);
  EXPECT_EQ(t.year(), 2020);
  EXPECT_EQ(t.month(), 3);
  EXPECT_EQ(t.day(), 3);
  EXPECT_EQ(t.hour(), 19);
  EXPECT_EQ(t.minute(), 43);
  EXPECT_DOUBLE_EQ(t.second(), 35.12);
}

TEST(DateTime, timezone_zero)
{
  DateTime t("2020-02-29T19:42:35+00:00");
  EXPECT_EQ(t.year(), 2020);
  EXPECT_EQ(t.month(), 2);
  EXPECT_EQ(t.day(), 29);
  EXPECT_EQ(t.hour(), 19);
  EXPECT_EQ(t.minute(), 42);
  EXPECT_EQ(t.second(), 35);
}

TEST(DateTime, timezone_positive)
{
  DateTime t("2020-02-29T19:42:35+01:00");
  EXPECT_EQ(t.year(), 2020);
  EXPECT_EQ(t.month(), 2);
  EXPECT_EQ(t.day(), 29);
  EXPECT_EQ(t.hour(), 18);
  EXPECT_EQ(t.minute(), 42);
  EXPECT_EQ(t.second(), 35);
}

TEST(DateTime, timezone_negative)
{
  DateTime t("2020-02-29T19:42:35-00:30");
  EXPECT_EQ(t.year(), 2020);
  EXPECT_EQ(t.month(), 2);
  EXPECT_EQ(t.day(), 29);
  EXPECT_EQ(t.hour(), 20);
  EXPECT_EQ(t.minute(), 12);
  EXPECT_EQ(t.second(), 35);
}

TEST(DateTime, second_fraction)
{
  DateTime t("2020-02-29T19:42:35.032+00:00");
  EXPECT_EQ(t.year(), 2020);
  EXPECT_EQ(t.month(), 2);
  EXPECT_EQ(t.day(), 29);
  EXPECT_EQ(t.hour(), 19);
  EXPECT_EQ(t.minute(), 42);
  EXPECT_EQ(t.second(), 35.032);
}
