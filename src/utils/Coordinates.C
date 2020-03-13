//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Coordinates.h"
#include "Angle.h"

namespace PikaUtils
{
namespace Coordinates
{

UTM::UTM(double easting, double northing, unsigned int zone, UTM::Hemisphere hemi) :
    easting(easting),
    northing(northing),
    zone(zone),
    hemisphere(hemi)
{
  //assert(zone < 61);
}

WGS84::WGS84(double latitude, double longitude) :
    latitude(Angle(latitude, Angle::DEG)),
    longitude(Angle(longitude, Angle::DEG))
{
}

}
} // namespace
