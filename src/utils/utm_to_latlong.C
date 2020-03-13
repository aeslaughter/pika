//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "utm_to_latlong.h"

UTMCoordinate::UTMCoordinate(double easting, double northing, unsigned int zone, Hemisphere hemi) :
    easting(easting),
    northing(northing),
    zone(zone),
    hemisphere(hemi)
{
  assert(zone < 61);
}
