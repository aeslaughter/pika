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

using namespace PikaUtils::SPA;

TEST(PikaUtils, Angle)
{
  const Angle a(M_PI, Angle::RAD);
  EXPECT_DOUBLE_EQ(a.rad(), M_PI);
  EXPECT_DOUBLE_EQ(a.deg(), 180.);

  const Angle b(3*M_PI, Angle::RAD);
  EXPECT_DOUBLE_EQ(b.rad(), 3*M_PI);
  EXPECT_DOUBLE_EQ(b.deg(), 540.);

  const Angle c(3*M_PI, Angle::RAD, Angle::LIMIT);
  EXPECT_DOUBLE_EQ(c.rad(), M_PI);
  EXPECT_DOUBLE_EQ(c.deg(), 180.);

  const Angle d(720, Angle::DEG);
  EXPECT_DOUBLE_EQ(d.rad(), 4*M_PI);
  EXPECT_DOUBLE_EQ(d.deg(), 720.);

  const Angle e(540., Angle::DEG, Angle::LIMIT);
  EXPECT_DOUBLE_EQ(e.rad(), M_PI);
  EXPECT_DOUBLE_EQ(e.deg(), 180.);

}



// Implements tests presented in NREL/TP-560-34302
// https://www.nrel.gov/docs/fy08osti/34302.pd
//
// The "gold" values were created using the SPA code from the above report
// https://rredc.nrel.gov/solar/codesandalgorithms/spa/
TEST(PikaUtils, solar)
{
  double year = 2003;
  double month = 10;
  double day = 17;
  double hour = 12;
  double min = 30;
  double sec = 30;
  double tzone = -7;
  double dut1 = 0;
  double deltat = 67.;
  double longitude = -105.1786;
  double latitude = 39.742476;
  double elevation = 1830.14;
  double pressure = 820;
  double temperature = 11;
  double slope = 30;
  double azm_rotation = -10;
  double atm_refract = 0.5667;

  double jd = julian_day(year, month, day, hour, min, sec, tzone, dut1);
  EXPECT_DOUBLE_EQ(jd, 2452930.312847222201526165);

  double dt = delta_t(2003);
  EXPECT_DOUBLE_EQ(dt, 87.164800000000014);

  double jde = julian_day_ephemeris(jd, deltat);
  EXPECT_DOUBLE_EQ(jde, 2452930.313622685149312019);

  double jc = julian_century(jd);
  EXPECT_DOUBLE_EQ(jc, 0.037927798691915169670974);

  double jce = julian_century_ephemeris(jde);
  EXPECT_DOUBLE_EQ(jce, 0.037927819922933585228275);

  double jme = julian_millennium_ephemeris(jce);
  EXPECT_DOUBLE_EQ(jme, 0.003792781992293358436091);

  double L0 = equation_ten<64>(Table1::L0, jme);
  EXPECT_DOUBLE_EQ(L0, 172067561.526585549116134643554688);
  double L1 = equation_ten<34>(Table1::L1, jme);
  EXPECT_DOUBLE_EQ(L1, 628332010650.051147460937500000000000);
  double L2 = equation_ten<20>(Table1::L2, jme);
  EXPECT_DOUBLE_EQ(L2, 61368.682493387161230202764273);
  double L3 = equation_ten<7>(Table1::L3, jme);
  EXPECT_DOUBLE_EQ(L3, -26.902818812449339702652651);
  double L4 = equation_ten<3>(Table1::L4, jme);
  EXPECT_DOUBLE_EQ(L4, -121.279536272762925364077091);
  double L5 = equation_ten<1>(Table1::L5, jme);
  EXPECT_DOUBLE_EQ(L5, -0.999998731727539502678326);

  double L = earth_heliocentric_longitude(jme);
  EXPECT_DOUBLE_EQ(L, 24.0182616916793989503275955);

  double B0 = equation_ten<5>(Table1::B0, jme);
  EXPECT_DOUBLE_EQ(B0, -176.502688041069120573);
  double B1 = equation_ten<2>(Table1::B1, jme);
  EXPECT_DOUBLE_EQ(B1, 3.067581813142713720);

  double B = earth_heliocentric_latitude(jme);
  EXPECT_DOUBLE_EQ(B, -0.00010112192480034234);

  double R0 = equation_ten<40>(Table1::R0, jme);
  EXPECT_DOUBLE_EQ(R0, 99653849.037795737385749817);
  double R1 = equation_ten<10>(Table1::R1, jme);
  EXPECT_DOUBLE_EQ(R1, 100378.567146467292332090);
  double R2 = equation_ten<6>(Table1::R2, jme);
  EXPECT_DOUBLE_EQ(R2, -1140.953507084899229085);
  double R3 = equation_ten<2>(Table1::R3, jme);
  EXPECT_DOUBLE_EQ(R3, -141.115419187090054720);
  double R4 = equation_ten<1>(Table1::R4, jme);
  EXPECT_DOUBLE_EQ(R4, 1.232360591526896032);

  double R = earth_radius_vector(jme);
  EXPECT_DOUBLE_EQ(R, 0.996542297353970818);

  double theta = geocentric_longitude(L);
  EXPECT_DOUBLE_EQ(theta, 204.018261691679413161);

  double beta = geocentric_latitude(B);
  EXPECT_DOUBLE_EQ(beta, 0.00010112192480034234);

  double x0 = mean_elongation_moon(jce);
  EXPECT_DOUBLE_EQ(x0, 17185.861179064908355940);

  double x1 = mean_anomaly_sun(jce);
  EXPECT_DOUBLE_EQ(x1, 1722.893218461364767791);

  double x2 = mean_anomaly_moon(jce);
  EXPECT_DOUBLE_EQ(x2, 18234.075702611266024178);

  double x3 = argument_latitute_moon(jce);
  EXPECT_DOUBLE_EQ(x3, 18420.071012282278388739);

  double x4 = ascending_longitude_moon(jce);
  EXPECT_DOUBLE_EQ(x4, 51.686951165383405282);

  double delta_psi = nutation_longitude(jce);
  EXPECT_DOUBLE_EQ(delta_psi, -0.003998404303332776);

  double delta_eps = nutation_obliquity(jce);
  EXPECT_DOUBLE_EQ(delta_eps, 0.001666568177249686);

  double eps0 = mean_obliquity_ecliptic(jme);
  EXPECT_DOUBLE_EQ(eps0, 84379.672625184990465641);

  double eps = true_obliquity_ecliptic(eps0, delta_eps);
  EXPECT_DOUBLE_EQ(eps, 23.440464519617524530);

  double delta_tau = aberration_correction(R);
  EXPECT_DOUBLE_EQ(delta_tau, -0.005711359293251811);

  double lambda = apparent_sun_longitude(theta, delta_psi, delta_tau);
  EXPECT_DOUBLE_EQ(lambda, 204.008551928082823679);

  double nu0 = mean_sidereal_time_greenwich(jd, jc);
  EXPECT_DOUBLE_EQ(nu0, 318.515578272772472701);

  double nu = apparent_sidereal_time_greenwich(nu0, delta_psi, eps);
  EXPECT_DOUBLE_EQ(nu, 318.511909841120711917);

  double alpha = sun_right_ascension(lambda, eps, beta);
  EXPECT_DOUBLE_EQ(alpha, 202.227407827207258606);

  double delta = geocentric_sun_declination(lambda, eps, beta);
  EXPECT_DOUBLE_EQ(delta, -9.314340090849105636);

  double H = observer_local_hour_angle(longitude, nu, alpha);
  EXPECT_DOUBLE_EQ(H, 11.105902013913436122);

  double xi = equatorial_horizontal_parallax(R);
  EXPECT_DOUBLE_EQ(xi, 0.002451253483433535);

  double delta_alpha = parallax_sun_right_ascension(latitude, elevation, xi, H, delta);
  EXPECT_DOUBLE_EQ(delta_alpha, -0.0003685349841678236312);

  double alpha_prime = topocentric_sun_right_ascension(alpha, delta_alpha);
  EXPECT_DOUBLE_EQ(alpha_prime, 202.227039292223082612);

  double delta_prime = topocentric_sun_declination(latitude, elevation, delta, xi, delta_alpha, H);
  EXPECT_DOUBLE_EQ(delta_prime, -9.3161786997149071964941);

  double H_prime = topocentric_local_hour_angle(H, delta_alpha);
  EXPECT_DOUBLE_EQ(H_prime, 11.106270548897603234);

  double e0 = topocentric_zenith_angle_no_correction(latitude, delta_prime, H_prime);
  EXPECT_DOUBLE_EQ(e0, 39.872045903847180170);

  double delta_e = atomspheric_refraction_correction(pressure, temperature, e0, atm_refract);
  EXPECT_DOUBLE_EQ(delta_e, 0.016332072123099440);

  double e = topocentric_elevation_angle(e0, delta_e);
  EXPECT_DOUBLE_EQ(e, 39.888377975970279010);

  double zenith = topocentric_zenith_angle(e);
  EXPECT_DOUBLE_EQ(zenith, 50.111622024029720990);

  double gamma = topocentric_astronomers_azimuth(latitude, H_prime, delta_prime);
  EXPECT_DOUBLE_EQ(gamma, 14.340240510191623713);

  double phi = topocentric_azimuth_angle(gamma);
  EXPECT_DOUBLE_EQ(phi, 194.340240510191620160);

  double incidence = incidence_angle(zenith, slope, azm_rotation, gamma);
  EXPECT_DOUBLE_EQ(incidence, 25.187000200353150348);
}
