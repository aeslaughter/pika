//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include <cmath>

#include "Coordinates.h"
#include "Angle.h"

namespace PikaUtils
{
namespace Coordinates
{

const double N0_north = 0.;
const double N0_south = 10000000.; // m
const double k0 = 0.9996;
const double E0 = 500000.; // m
const double a = 6378137.; // m
const double f = 1./298.257223563;
const double n = f / (2 - f);
const double A = a / (1 + n) * (1 + std::pow(n, 2.)/4. + std::pow(n, 4.)/64. + std::pow(n, 6.)/256.);

const std::array<double, 3> beta = {1./2.*n - 2./3.*std::pow(n, 2.) + 37./96.*std::pow(n, 3) - 1./360.*std::pow(n, 4),
                                    1./48.*std::pow(n, 2.) + 1./15.*std::pow(n, 3.) - 437./1440.*std::pow(n, 4.),
                                    17./480.*std::pow(n, 3.) - 37./840.*std::pow(n,4)};
const std::array<double, 3> delta = {2.*n - 2./3.*std::pow(n, 2.) - 2*std::pow(n, 3.),
                                     7./3.*std::pow(n, 2.) - 8./5.*std::pow(n, 3.),
                                     56./15.*std::pow(n, 3.)};

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

WGS84 convert(const UTM & coord)
{
  // TODO: Implement Eq. 13-22 in Karney, 2011, then try section 4
  // The following if from: https://en.wikipedia.org/wiki/Universal_Transverse_Mercator_coordinate_system#Simplified_formulae
  double N0 = (coord.hemisphere == UTM::Hemisphere::NORTH) ? N0_north : N0_south;
  double xi = (coord.northing - N0) / (k0 * A);
  double eta = (coord.easting - E0) / (k0 * A);

  double xi_p = xi;
  double eta_p = eta;
  for (std::size_t j = 1; j < 4; ++j)
  {
    xi_p -= beta[j-1]*sin(2*j*xi) * cosh(2*j*eta);
    eta_p -= beta[j-1]*cos(2*j*xi) * sinh(2*j*eta);
  }
  double chi = asin(sin(xi_p)/cosh(eta_p));
  double phi = Angle::radians_to_degrees(chi + delta[0]*sin(2*chi) + delta[1]*sin(2*2*chi) + delta[2]*sin(2*3*chi));
  double lam_0 = coord.zone * 6. - 183.;
  double lam = Angle::radians_to_degrees(atan(sinh(eta_p)/cos(xi_p)));

  return WGS84(phi, lam + lam_0);
}

UTM convert(const WGS84 & /*coord*/)
{
  // TODO:
  return UTM(0,0,1);
}


}
} // namespace
