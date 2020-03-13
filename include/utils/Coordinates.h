//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#pragma once

#include "Angle.h"

namespace PikaUtils
{
namespace Coordinates
{

struct UTM
{
  enum class Hemisphere: int{NORTH=1, SOUTH=-1};

  UTM(double easting, double northing, unsigned int zone, Hemisphere hemi = Hemisphere::NORTH);

  const double easting;
  const double northing;
  const unsigned int zone;
  const Hemisphere hemisphere;
};

struct WGS84
{
  WGS84(double latitude, double longitude);

  const PikaUtils::Angle latitude;
  const PikaUtils::Angle longitude;
};

}
} // namespace
