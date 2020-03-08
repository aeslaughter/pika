#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <regex>
#include <sstream>
#include "solar.h"

namespace PikaUtils
{
namespace SPA
{

Angle::Angle(double value, Type type, Limit limit)
{
  bool limited = limit == Angle::Limit::LIMIT;
  if (type == Angle::Type::RAD)
  {
    _degrees = limited ? limit_degrees(radians_to_degrees(value)) : radians_to_degrees(value);
    _radians = limited ? degrees_to_radians(_degrees) : value;
  }
  else if (type == Angle::Type::DEG)
  {
    _degrees = limited ? limit_degrees(value) : value;
    _radians = degrees_to_radians(_degrees);
  }
}

double
Angle::deg() const
{
  return _degrees;
}

double
Angle::rad() const
{
  return _radians;
}

double
Angle::radians_to_degrees(double rad)
{
  return (rad * 180.)/M_PI;
}

double
Angle::degrees_to_radians(double deg)
{
  return (M_PI / 180.0) * deg;
}

double
Angle::limit_degrees(double deg)
{
  deg /= 360.0;
  double limited = 360.0*(deg - std::floor(deg));
  if (limited < 0)
    limited += 360.0;
  return limited;
}

DateTime::DateTime(const std::string & date, Format format)
{
  std::regex re;
  switch (format)
  {
  case Format::ISO8601:
    re ="([0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2})(?:\\.([0-9]+))?(?:([+-])([0-2][0-9]):([0-6][0-9]))?";
  }
  std::smatch match;
  std::regex_match(date, match, re);

  _tinfo.tm_year = std::stoi(match[1]) - 1900;
  _tinfo.tm_mon = std::stoi(match[2]) - 1;
  _tinfo.tm_mday = std::stoi(match[3]);
  _tinfo.tm_hour = std::stoi(match[4]);
  _tinfo.tm_min = std::stoi(match[5]);
  _tinfo.tm_sec = std::stoi(match[6]);
  _tinfo.tm_isdst = 0;

  if (match[7].matched)
  {
    std::ostringstream oss;
    oss << "0." << match[7];
    _fraction_sec = std::stod(oss.str());
  }

  int sign = match[8] == "-" ? -1 : 1;
  int tz_hour = match[9].matched ? sign * std::stoi(match[9]) : 0;
  int tz_min = match[10].matched ? sign * std::stoi(match[10]) : 0;
  _tinfo.tm_hour -= tz_hour;
  _tinfo.tm_min -= tz_min;

  mktime(&_tinfo);
}

void
DateTime::add(int years, int months, int days, int hours, int minutes, double seconds)
{
  _tinfo.tm_year += years;
  _tinfo.tm_mon += months;
  _tinfo.tm_mday += days;
  _tinfo.tm_hour += hours;
  _tinfo.tm_min += minutes;

  seconds += _tinfo.tm_sec;
  _fraction_sec = modf(seconds , &seconds);
  _tinfo.tm_sec = static_cast<int>(seconds);
  mktime(&_tinfo);
}

double julian_day(unsigned int year, unsigned int month, unsigned int day, unsigned int hour,
                  unsigned int min, double sec, double timezone, double dut1)
{
  // Apply DUT1, which is the difference between Coordinated Universal Time (UTC) and
  // Principal Universal Time (UT1)
  sec += dut1;

  // Remove the timezone, which is given by the hours from UTC
  hour -= timezone;

  // Compute decimal day
  double dec_day = day + hour/24. + min/1440. + sec/86400.;

  // Adjust year and month (see Eq. 4)
  if (month < 3)
  {
    year -= 1;
    month += 12;
  }

  // Compute the Julian Day using Eq. 4
  double jd = std::floor(365.25*(year + 4716.)) + std::floor(30.6001*(month+1)) + dec_day - 1524.5;

  // Adjust for the 1582 Gregorian calender change
  if (jd > 2299160.)
  {
    double A = std::floor(year/100.);
    jd += (2 - A + std::floor(A/4.));
  }
  return jd;
}

double delta_t(unsigned int year)
{
  // https://eclipse.gsfc.nasa.gov/SEcat5/deltat.html
  // ΔT = -20 + 32 * t^2 seconds
  // where:	t = (year-1820)/100
  return 32. * std::pow((year - 1820.)/100., 2.) - 20.;
}

double julian_day_ephemeris(double jd, double dt)
{
  return jd + dt / 86400.;
}

double julian_century(double jd)
{
  return (jd - 2451545.) / 36525.;
}

double julian_century_ephemeris(double jde)
{
  return (jde - 2451545.) / 36525.;
}

double julian_millennium_ephemeris(double jce)
{
  return jce / 10.;
}

double rad_to_degrees(double rad)
{
  return (rad * 180.)/M_PI;
}

double degrees_to_rad(double deg)
{
  return (M_PI / 180.0) * deg;
}

double limit_degrees(double deg)
{
  deg /= 360.0;
  double limited = 360.0*(deg - std::floor(deg));
  if (limited < 0)
    limited += 360.0;
  return limited;
}

double earth_heliocentric_longitude(double jme)
{
  double L0 = equation_ten<64>(Table1::L0, jme);
  double L1 = equation_ten<34>(Table1::L1, jme);
  double L2 = equation_ten<20>(Table1::L2, jme);
  double L3 = equation_ten<7>(Table1::L3, jme);
  double L4 = equation_ten<3>(Table1::L4, jme);
  double L5 = equation_ten<1>(Table1::L5, jme);
  double L_rad = (L0 + L1 * jme + L2 * std::pow(jme, 2) + L3 * std::pow(jme, 3) + L4 * std::pow(jme, 4) + L5 * std::pow(jme, 5)) / 1e8;
  return limit_degrees(rad_to_degrees(L_rad));
}

double earth_heliocentric_latitude(double jme)
{
  double B0 = equation_ten<5>(Table1::B0, jme);
  double B1 = equation_ten<2>(Table1::B1, jme);
  double B_rad = (B0 + B1 * jme) / 1e8;
  return rad_to_degrees(B_rad);
}

double earth_radius_vector(double jme)
{
  double R0 = equation_ten<40>(Table1::R0, jme);
  double R1 = equation_ten<10>(Table1::R1, jme);
  double R2 = equation_ten<6>(Table1::R2, jme);
  double R3 = equation_ten<2>(Table1::R3, jme);
  double R4 = equation_ten<1>(Table1::R4, jme);
  double R = (R0 + R1 * jme + R2 * std::pow(jme, 2) + R3 * std::pow(jme, 3) + R4 * std::pow(jme, 4)) / 1e8;
  return R;
}

double geocentric_longitude(double L)
{
  double theta = L + 180.;
  if (theta > 360.)
    theta -= 360.;
  return theta;
}

double geocentric_latitude(double B)
{
  return -B;
}

double mean_elongation_moon(double jce)
{
  return 297.85036 + 445267.11148 * jce - 0.0019142 * std::pow(jce, 2) + std::pow(jce, 3)/189474.;
}

double mean_anomaly_sun(double jce)
{
  return 357.52772 + 35999.050340 * jce - 0.0001603 * std::pow(jce, 2) - std::pow(jce, 3)/300000.;
}

double mean_anomaly_moon(double jce)
{
  return 134.96298 + 477198.867398 * jce + 0.0086972 * std::pow(jce, 2) + std::pow(jce, 3)/56250.;
}

double argument_latitute_moon(double jce)
{
  return 93.27191 + 483202.017538 * jce - 0.0036825 * std::pow(jce, 2) + std::pow(jce, 3)/327270.;
}

double ascending_longitude_moon(double jce)
{
  return 125.04452 - 1934.136261 * jce + 0.0020708 * std::pow(jce, 2) + std::pow(jce, 3)/450000.;
}

double nutation_longitude(double jce)
{
  using namespace Table2;
  double delta_psi = 0;
  const double X0 = mean_elongation_moon(jce);
  const double X1 = mean_anomaly_sun(jce);
  const double X2 = mean_anomaly_moon(jce);
  const double X3 = argument_latitute_moon(jce);
  const double X4 = ascending_longitude_moon(jce);
  for (std::size_t i = 0; i < 63; ++i)
  {
    double inner = degrees_to_rad(X0*Y[i][0] + X1*Y[i][1] + X2*Y[i][2] + X3*Y[i][3] + X4*Y[i][4]);
    delta_psi += (PE[i][0] + PE[i][1] * jce) * std::sin(inner);
  }

  return delta_psi / 36000000.;
}

double nutation_obliquity(double jce)
{
  using namespace Table2;
  double delta_eps = 0;
  const double X0 = mean_elongation_moon(jce);
  const double X1 = mean_anomaly_sun(jce);
  const double X2 = mean_anomaly_moon(jce);
  const double X3 = argument_latitute_moon(jce);
  const double X4 = ascending_longitude_moon(jce);
  for (std::size_t i = 0; i < 63; ++i)
  {
    double inner = degrees_to_rad(X0*Y[i][0] + X1*Y[i][1] + X2*Y[i][2] + X3*Y[i][3] + X4*Y[i][4]);
    delta_eps += (PE[i][2] + PE[i][3] * jce) * std::cos(inner);
  }
  return delta_eps / 36000000.;
}

double mean_obliquity_ecliptic(double jme)
{
  double U = jme / 10.;
  return 84381.448 - 4680.93*U - 1.55 * std::pow(U, 2) + 1999.25 * std::pow(U, 3) -
    51.38 * std::pow(U, 4) - 249.67 * std::pow(U, 5) - 39.05 * std::pow(U, 6) +
    7.12 * std::pow(U, 7) + 27.87 * std::pow(U, 8) + 5.79 * std::pow(U, 9) +
    2.45 * std::pow(U, 10);
}

double true_obliquity_ecliptic(double eps0, double delta_eps)
{
  return eps0 / 3600. + delta_eps;
}

double aberration_correction(double R)
{
  return -20.4898 / (3600. * R);
}

double apparent_sun_longitude(double theta, double delta_psi, double delta_tau)
{
  return theta + delta_psi + delta_tau;
}

double mean_sidereal_time_greenwich(double jd, double jc)
{
  double nu0 = 280.46061837 + 360.98564736629 * (jd - 2451545) + 0.000387933 * std::pow(jc, 2) -
    std::pow(jc, 3) / 38710000.;
  return limit_degrees(nu0);
}

double apparent_sidereal_time_greenwich(double nu0, double delta_psi, double eps)
{
  return nu0 + delta_psi * std::cos(degrees_to_rad(eps));
}

double sun_right_ascension(double lambda, double eps, double beta)
{
  lambda = degrees_to_rad(lambda);
  eps = degrees_to_rad(eps);
  beta = degrees_to_rad(beta);
  double alpha = std::atan2(std::sin(lambda) * std::cos(eps) - std::tan(beta) * std::sin(eps), std::cos(lambda));
  return limit_degrees(rad_to_degrees(alpha));
}

double geocentric_sun_declination(double lambda, double eps, double beta)
{
  lambda = degrees_to_rad(lambda);
  eps = degrees_to_rad(eps);
  beta = degrees_to_rad(beta);
  double delta = std::asin(std::sin(beta) * std::cos(eps) + std::cos(beta) * std::sin(eps) * std::sin(lambda));
  return rad_to_degrees(delta);
}

double observer_local_hour_angle(double longitude, double nu, double alpha)
{
  return limit_degrees(nu + longitude - alpha);
}

double equatorial_horizontal_parallax(double R)
{
  return 8.794 / (3600. * R);
}

double parallax_sun_right_ascension(double latitude, double elevation, double xi, double H, double delta)
{
  latitude = degrees_to_rad(latitude);
  H = degrees_to_rad(H);
  delta = degrees_to_rad(delta);
  xi = degrees_to_rad(xi);

  double u = std::atan(0.99664719 * std::tan(latitude));
  double x = std::cos(u) + elevation / 6378140. * std::cos(latitude);
  double delta_alpha = std::atan2(-x * std::sin(xi) * std::sin(H),
                                  std::cos(delta) - x * sin(xi) * cos(H));
  return rad_to_degrees(delta_alpha);
}

double topocentric_sun_right_ascension(double alpha, double delta_alpha)
{
  return alpha + delta_alpha;
}

double topocentric_sun_declination(double latitude, double elevation, double delta, double xi, double delta_alpha, double H)
{
  latitude = degrees_to_rad(latitude);
  xi = degrees_to_rad(xi);
  H = degrees_to_rad(H);
  delta = degrees_to_rad(delta);
  delta_alpha = degrees_to_rad(delta_alpha);
  double u = std::atan(0.99664719 * std::tan(latitude));
  double x = std::cos(u) + elevation / 6378140. * std::cos(latitude);
  double y = 0.99664719 * std::sin(u) + elevation / 6378140 * std::sin(latitude);
  double delta_prime = std::atan2((std::sin(delta) - y * std::sin(xi)) * std::cos(delta_alpha),
                                  std::cos(delta) - x * std::sin(xi) * std::cos(H));
  return rad_to_degrees(delta_prime);
}

double topocentric_local_hour_angle(double H, double delta_alpha)
{
  return H - delta_alpha;
}

double topocentric_zenith_angle_no_correction(double latitude, double delta_prime, double H_prime)
{
  latitude = degrees_to_rad(latitude);
  delta_prime = degrees_to_rad(delta_prime);
  H_prime = degrees_to_rad(H_prime);
  double e0 = std::asin(std::sin(latitude) * std::sin(delta_prime) +
                        std::cos(latitude) * std::cos(delta_prime) * std::cos(H_prime));
  return rad_to_degrees(e0);
}

double atomspheric_refraction_correction(double P, double T, double e0, double atm_refraction)
{
  double del_e = 0.;
  const double sun_radius = 0.26667;
  if (e0 >= -sun_radius + atm_refraction)
  {
    double arg = degrees_to_rad(e0 + 10.3 / (e0 + 5.11));
    del_e = P / 1010. * 283. / (273. + T) * 1.02 / (60 * std::tan(arg));
  }
  return del_e;
}

double topocentric_elevation_angle(double e0, double delta_e)
{
  return e0 + delta_e;
}

double topocentric_zenith_angle(double e)
{
  return 90. - e;
}

double topocentric_astronomers_azimuth(double latitude, double H_prime, double delta_prime)
{
  latitude = degrees_to_rad(latitude);
  delta_prime = degrees_to_rad(delta_prime);
  H_prime = degrees_to_rad(H_prime);
  double gamma = std::atan2(std::sin(H_prime), std::cos(H_prime) * std::sin(latitude) - std::tan(delta_prime) * std::cos(latitude));
  return rad_to_degrees(gamma);
}

double topocentric_azimuth_angle(double gamma)
{
  return limit_degrees(gamma + 180.);
}

double incidence_angle(double zenith, double slope, double rotation, double gamma)
{
  zenith = degrees_to_rad(zenith);
  slope = degrees_to_rad(slope);
  rotation = degrees_to_rad(rotation);
  gamma = degrees_to_rad(gamma);
  double incidence = std::acos(std::cos(zenith) * std::cos(slope) + std::sin(slope) * std::sin(zenith) * std::cos(gamma - rotation));
  return rad_to_degrees(incidence);
}

// clang-format off
const std::array<std::array<double, 3>, 64> Table1::L0 =
{
  std::array<double, 3>({175347046, 0,            0}),        // 0
  std::array<double, 3>({  3341656, 4.6692568, 6283.07585}),  // 1
  std::array<double, 3>({    34894, 4.6261,    12566.1517}),  // 2
  std::array<double, 3>({     3497, 2.7441,    5753.3849}),   // 3
  std::array<double, 3>({     3418, 2.8289,       3.5231}),   // 4
  std::array<double, 3>({     3136, 3.6277,   77713.7715}),   // 5
  std::array<double, 3>({     2676, 4.4181,    7860.4194}),   // 6
  std::array<double, 3>({     2343, 6.1352,    3930.2097}),   // 7
  std::array<double, 3>({     1324, 0.7425,   11506.7698}),   // 8
  std::array<double, 3>({     1273, 2.0371,     529.691}),    // 9
  std::array<double, 3>({     1199, 1.1096,    1577.3435}),   // 10
  std::array<double, 3>({      990, 5.233,     5884.927}),    // 11
  std::array<double, 3>({      902, 2.045,       26.298}),    // 12
  std::array<double, 3>({      857, 3.508,      398.149}),    // 13
  std::array<double, 3>({      780, 1.179,     5223.694}),    // 14
  std::array<double, 3>({      753, 2.533,     5507.553}),    // 15
  std::array<double, 3>({      505, 4.583,    18849.228}),    // 16
  std::array<double, 3>({      492, 4.205,      775.523}),    // 17
  std::array<double, 3>({      357, 2.92,         0.067}),    // 18
  std::array<double, 3>({      317, 5.849,    11790.629}),    // 19
  std::array<double, 3>({      284, 1.899,      796.298}),    // 20
  std::array<double, 3>({      271, 0.315,    10977.079}),    // 21
  std::array<double, 3>({      243, 0.345,     5486.778}),    // 22
  std::array<double, 3>({      206, 4.806,     2544.314}),    // 23
  std::array<double, 3>({      205, 1.869,     5573.143}),    // 24
  std::array<double, 3>({      202, 2.458,    6069.777}),     // 25
  std::array<double, 3>({      156, 0.833,      213.299}),    // 26
  std::array<double, 3>({      132, 3.411,     2942.463}),    // 27
  std::array<double, 3>({      126, 1.083,       20.775}),    // 28
  std::array<double, 3>({      115, 0.645,        0.98}),     // 29
  std::array<double, 3>({      103, 0.636,     4694.003}),    // 30
  std::array<double, 3>({      102, 0.976,    15720.839}),    // 31
  std::array<double, 3>({      102, 4.267,        7.114}),    // 32
  std::array<double, 3>({       99, 6.21,       2146.17}),    // 33
  std::array<double, 3>({       98, 0.68,        155.42}),    // 34
  std::array<double, 3>({       86, 5.98,     161000.69}),    // 35
  std::array<double, 3>({       85, 1.3,        6275.96}),    // 36
  std::array<double, 3>({       85, 3.67,      71430.7}),     // 37
  std::array<double, 3>({       80, 1.81,      17260.15}),    // 38
  std::array<double, 3>({       79, 3.04,      12036.46}),    // 39
  std::array<double, 3>({       75, 1.76,       5088.63}),    // 40
  std::array<double, 3>({       74, 3.5,        3154.69}),    // 41
  std::array<double, 3>({       74, 4.68,        801.82}),    // 42
  std::array<double, 3>({       70, 0.83,       9437.76}),    // 43
  std::array<double, 3>({       62, 3.98,       8827.39}),    // 44
  std::array<double, 3>({       61, 1.82,       7084.9}),     // 45
  std::array<double, 3>({       57, 2.78,       6286.6}),     // 46
  std::array<double, 3>({       56, 4.39,      14143.5}),     // 47
  std::array<double, 3>({       56, 3.47,       6279.55}),    // 48
  std::array<double, 3>({       52, 0.19,      12139.55}),    // 49
  std::array<double, 3>({       52, 1.33,       1748.02}),    // 50
  std::array<double, 3>({       51, 0.28,       5856.48}),    // 51
  std::array<double, 3>({       49, 0.49,       1194.45}),    // 52
  std::array<double, 3>({       41, 5.37,       8429.24}),    // 53
  std::array<double, 3>({       41, 2.4,       19651.05}),    // 54
  std::array<double, 3>({       39, 6.17,      10447.39}),    // 55
  std::array<double, 3>({       37, 6.04,      10213.29}),    // 56
  std::array<double, 3>({       37, 2.57,       1059.38}),    // 57
  std::array<double, 3>({       36, 1.71,       2352.87}),    // 58
  std::array<double, 3>({       36, 1.78,       6812.77}),    // 59
  std::array<double, 3>({       33, 0.59,      17789.85}),    // 60
  std::array<double, 3>({       30, 0.44,      83996.85}),    // 61
  std::array<double, 3>({       30, 2.74,       1349.87}),    // 62
  std::array<double, 3>({       25, 3.16,       4690.48})     // 63
};

const std::array<std::array<double, 3>, 34> Table1::L1 =
{
  std::array<double, 3>({628331966747, 0,           0}),       // 0
  std::array<double, 3>({      206059, 2.678235, 6283.07585}), // 1
  std::array<double, 3>({        4303, 2.6351,  12566.1517}),  // 2
  std::array<double, 3>({         425, 1.59,        3.523}),   // 3
  std::array<double, 3>({         119, 5.796,      26.298}),   // 4
  std::array<double, 3>({         109, 2.966,    1577.344}),   // 5
  std::array<double, 3>({          93, 2.59,    18849.23}),    // 6
  std::array<double, 3>({          72, 1.14,      529.69}),    // 7
  std::array<double, 3>({          68, 1.87,      398.15}),    // 8
  std::array<double, 3>({          67, 4.41,     5507.55}),    // 9
  std::array<double, 3>({          59, 2.89,     5223.69}),    // 10
  std::array<double, 3>({          56, 2.17,      155.42}),    // 11
  std::array<double, 3>({          45, 0.4,       796.3}),     // 12
  std::array<double, 3>({          36, 0.47,      775.52}),    // 13
  std::array<double, 3>({          29, 2.65,        7.11}),    // 14
  std::array<double, 3>({          21, 5.34,        0.98}),    // 15
  std::array<double, 3>({          19, 1.85,     5486.78}),    // 16
  std::array<double, 3>({          19, 4.97,      213.3}),     // 17
  std::array<double, 3>({          17, 2.99,     6275.96}),    // 18
  std::array<double, 3>({          16, 0.03,     2544.31}),    // 19
  std::array<double, 3>({          16, 1.43,     2146.17}),    // 20
  std::array<double, 3>({          15, 1.21,    10977.08}),    // 21
  std::array<double, 3>({          12, 2.83,     1748.02}),    // 22
  std::array<double, 3>({          12, 3.26,     5088.63}),    // 23
  std::array<double, 3>({          12, 5.27,     1194.45}),    // 24
  std::array<double, 3>({          12, 2.08,     4694}),       // 25
  std::array<double, 3>({          11, 0.77,      553.57}),    // 26
  std::array<double, 3>({          10, 1.3,      6286.6}),     // 27
  std::array<double, 3>({          10, 4.24,     1349.87}),    // 28
  std::array<double, 3>({           9, 2.7,       242.73}),    // 29
  std::array<double, 3>({           9, 5.64,      951.72}),    // 30
  std::array<double, 3>({           8, 5.3,      2352.87}),    // 31
  std::array<double, 3>({           6, 2.65,     9437.76}),    // 32
  std::array<double, 3>({           6, 4.67,     4690.48})     // 33
};

const std::array<std::array<double, 3>, 20> Table1::L2 =
{
  std::array<double, 3>({52919, 0,          0}),      // 0
  std::array<double, 3>({ 8720, 1.0721,  6283.0758}), // 1
  std::array<double, 3>({  309, 0.867,  12566.152}),  // 2
  std::array<double, 3>({   27,  0.05,      3.52}),   // 3
  std::array<double, 3>({   16,  5.19,     26.3}),    // 4
  std::array<double, 3>({   16,  3.68,    155.42}),   // 5
  std::array<double, 3>({   10,  0.76,  18849.23}),   // 6
  std::array<double, 3>({    9,  2.06,   77713.77}),  // 7
  std::array<double, 3>({    7,  0.83,     775.52}),  // 8
  std::array<double, 3>({    5,  4.66,    1577.34}),  // 9
  std::array<double, 3>({    4,  1.03,       7.11}),  // 10
  std::array<double, 3>({    4,  3.44,    5573.14}),  // 11
  std::array<double, 3>({    3,  5.14,     796.3}),   // 12
  std::array<double, 3>({    3,  6.05,    5507.55}),  // 13
  std::array<double, 3>({    3,  1.19,     242.73}),  // 14
  std::array<double, 3>({    3,  6.12,     529.69}),  // 15
  std::array<double, 3>({    3,  0.31,     398.15}),  // 16
  std::array<double, 3>({    3,  2.28,     553.57}),  // 17
  std::array<double, 3>({    2,  4.38,    5223.69}),  // 18
  std::array<double, 3>({    2,  3.75,       0.98})   // 19
};

const std::array<std::array<double, 3>, 7> Table1::L3 =
{
  std::array<double, 3>({289, 5.844, 6283.076}), // 0
  std::array<double, 3>({ 35, 0,        0}),     // 1
  std::array<double, 3>({ 17, 5.49, 12566.15}),  // 2
  std::array<double, 3>({  3, 5.2,    155.42}),  // 3
  std::array<double, 3>({  1, 4.72,     3.52}),  // 4
  std::array<double, 3>({  1, 5.3,  18849.23}),  // 5
  std::array<double, 3>({  1, 5.97,   242.73})   // 6
};

const std::array<std::array<double, 3>, 3> Table1::L4 =
{
  std::array<double, 3>({114, 3.142,    0}),    // 0
  std::array<double, 3>({  8, 4.13,  6283.08}), // 1
  std::array<double, 3>({  1, 3.84, 12566.15})  // 2
};

const std::array<std::array<double, 3>, 1> Table1::L5 =
{
  std::array<double, 3>({1, 3.14, 0}) // 0
};

const std::array<std::array<double, 3>, 5> Table1::B0 =
{
  std::array<double, 3>({280, 3.199, 84334.662}), // 0
  std::array<double, 3>({102, 5.422,  5507.553}), // 1
  std::array<double, 3>({ 80, 3.88,   5223.69}),  // 2
  std::array<double, 3>({ 44, 3.7,    2352.87}),  // 3
  std::array<double, 3>({ 32, 4,      1577.34})   // 4
};

const std::array<std::array<double, 3>, 2> Table1::B1 =
{
  std::array<double, 3>({9, 3.9,  5507.55}), // 0
  std::array<double, 3>({6, 1.73, 5223.69})  // 1
};

const std::array<std::array<double, 3>, 40> Table1::R0 =
{
  std::array<double, 3>({100013989, 0,            0}),       // 0
  std::array<double, 3>({  1670700, 3.0984635, 6283.07585}), // 1
  std::array<double, 3>({    13956, 3.05525,  12566.1517}),  // 2
  std::array<double, 3>({     3084, 5.1985,   77713.7715}),  // 3
  std::array<double, 3>({     1628, 1.1739,    5753.3849}),  // 4
  std::array<double, 3>({     1576, 2.8469,    7860.4194}),  // 5
  std::array<double, 3>({      925, 5.453,    11506.77}),    // 6
  std::array<double, 3>({      542, 4.564,     3930.21}),    // 7
  std::array<double, 3>({      472, 3.661,     5884.927}),   // 8
  std::array<double, 3>({      346, 0.964,     5507.553}),   // 9
  std::array<double, 3>({      329, 5.9,       5223.694}),   // 10
  std::array<double, 3>({      307, 0.299,     5573.143}),   // 11
  std::array<double, 3>({      243, 4.273,     11790.629}),  // 12
  std::array<double, 3>({      212, 5.847,      1577.344}),  // 13
  std::array<double, 3>({      186, 5.022,     10977.079}),  // 14
  std::array<double, 3>({      175, 3.012,     18849.228}),  // 15
  std::array<double, 3>({      110, 5.055,      5486.778}),  // 16
  std::array<double, 3>({       98, 0.89,       6069.78}),   // 17
  std::array<double, 3>({       86, 5.69,      15720.84}),   // 18
  std::array<double, 3>({       86, 1.27,     161000.69}),   // 19
  std::array<double, 3>({       65, 0.27,      17260.15}),   // 20
  std::array<double, 3>({       63, 0.92,        529.69}),   // 21
  std::array<double, 3>({       57, 2.01,      83996.85}),   // 22
  std::array<double, 3>({       56, 5.24,      71430.7}),    // 23
  std::array<double, 3>({       49, 3.25,       2544.31}),   // 24
  std::array<double, 3>({       47, 2.58,        775.52}),   // 25
  std::array<double, 3>({       45, 5.54,       9437.76}),   // 26
  std::array<double, 3>({       43, 6.01,       6275.96}),   // 27
  std::array<double, 3>({       39, 5.36,       4694}),      // 28
  std::array<double, 3>({       38, 2.39,       8827.39}),   // 29
  std::array<double, 3>({       37, 0.83,      19651.05}),   // 30
  std::array<double, 3>({       37, 4.9,       12139.55}),   // 31
  std::array<double, 3>({       36, 1.67,      12036.46}),   // 32
  std::array<double, 3>({       35, 1.84,       2942.46}),   // 33
  std::array<double, 3>({       33, 0.24,       7084.9}),    // 34
  std::array<double, 3>({       32, 0.18,       5088.63}),   // 35
  std::array<double, 3>({       32, 1.78,        398.15}),   // 36
  std::array<double, 3>({       28, 1.21,       6286.6}),    // 37
  std::array<double, 3>({       28, 1.9,        6279.55}),   // 38
  std::array<double, 3>({       26, 4.59,      10447.39})    // 39
};

const std::array<std::array<double, 3>, 10> Table1::R1 =
{
  std::array<double, 3>({103019, 1.10749, 6283.07585}), // 0
  std::array<double, 3>({  1721, 1.0644, 12566.1517}),  // 1
  std::array<double, 3>({   702, 3.142,      0}),       // 2
  std::array<double, 3>({    32, 1.02,    18849.23}),   // 3
  std::array<double, 3>({    31, 2.84,     5507.55}),   // 4
  std::array<double, 3>({    25, 1.32,     5223.69}),   // 5
  std::array<double, 3>({    18, 1.42,     1577.34}),   // 6
  std::array<double, 3>({    10, 5.91,    10977.08}),   // 7
  std::array<double, 3>({     9, 1.42,     6275.96}),   // 8
  std::array<double, 3>({     9, 0.27,     5486.78})    // 9
};

const std::array<std::array<double, 3>, 6> Table1::R2 =
{
  std::array<double, 3>({4359, 5.7846, 6283.0758}), // 0
  std::array<double, 3>({ 124, 5.579, 12566.152}),  // 1
  std::array<double, 3>({  12, 3.14,      0}),      // 2
  std::array<double, 3>({   9, 3.63,  77713.77}),   // 3
  std::array<double, 3>({   6, 1.87,   5573.14}),   // 4
  std::array<double, 3>({   3, 5.47,  18849.23})    // 5
};

const std::array<std::array<double, 3>, 2> Table1::R3 =
{
  std::array<double, 3>({145, 4.273, 6283.076}), // 0
  std::array<double, 3>({  7, 3.92, 12566.15})   // 1
};

const std::array<std::array<double, 3>, 1> Table1::R4 =
{
  std::array<double, 3>({4,2.56,6283.08}) // 0
};

const std::array<std::array<double, 5>, 63> Table2::Y =
{
  std::array<double, 5>({ 0,  0,  0,  0,  1}), // 0
  std::array<double, 5>({-2,  0,  0,  2,  2}), // 1
  std::array<double, 5>({ 0,  0,  0,  2,  2}), // 2
  std::array<double, 5>({ 0,  0,  0,  0,  2}), // 3
  std::array<double, 5>({ 0,  1,  0,  0,  0}), // 4
  std::array<double, 5>({ 0,  0,  1,  0,  0}), // 5
  std::array<double, 5>({-2,  1,  0,  2,  2}), // 6
  std::array<double, 5>({ 0,  0,  0,  2,  1}), // 7
  std::array<double, 5>({ 0,  0,  1,  2,  2}), // 8
  std::array<double, 5>({-2, -1,  0,  2,  2}), // 9
  std::array<double, 5>({-2,  0,  1,  0,  0}), // 10
  std::array<double, 5>({-2,  0,  0,  2,  1}), // 11
  std::array<double, 5>({ 0,  0, -1,  2,  2}), // 12
  std::array<double, 5>({ 2,  0,  0,  0,  0}), // 13
  std::array<double, 5>({ 0,  0,  1,  0,  1}), // 14
  std::array<double, 5>({ 2,  0, -1,  2,  2}), // 15
  std::array<double, 5>({ 0,  0, -1,  0,  1}), // 16
  std::array<double, 5>({ 0,  0,  1,  2,  1}), // 17
  std::array<double, 5>({-2,  0,  2,  0,  0}), // 18
  std::array<double, 5>({ 0,  0, -2,  2,  1}), // 19
  std::array<double, 5>({ 2,  0,  0,  2,  2}), // 20
  std::array<double, 5>({ 0,  0,  2,  2,  2}), // 21
  std::array<double, 5>({ 0,  0,  2,  0,  0}), // 22
  std::array<double, 5>({-2,  0,  1,  2,  2}), // 23
  std::array<double, 5>({ 0,  0,  0,  2,  0}), // 24
  std::array<double, 5>({-2,  0,  0,  2,  0}), // 25
  std::array<double, 5>({ 0,  0, -1,  2,  1}), // 26
  std::array<double, 5>({ 0,  2,  0,  0,  0}), // 27
  std::array<double, 5>({ 2,  0, -1,  0,  1}), // 28
  std::array<double, 5>({-2,  2,  0,  2,  2}), // 29
  std::array<double, 5>({ 0,  1,  0,  0,  1}), // 30
  std::array<double, 5>({-2,  0,  1,  0,  1}), // 31
  std::array<double, 5>({ 0, -1,  0,  0,  1}), // 32
  std::array<double, 5>({ 0,  0,  2,  -2, 0}), // 33
  std::array<double, 5>({ 2,  0, -1,  2,  1}), // 34
  std::array<double, 5>({ 2,  0,  1,  2,  2}), // 35
  std::array<double, 5>({ 0,  1,  0,  2,  2}), // 36
  std::array<double, 5>({-2,  1,  1,  0,  0}), // 37
  std::array<double, 5>({ 0, -1,  0,  2,  2}), // 38
  std::array<double, 5>({ 2,  0,  0,  2,  1}), // 39
  std::array<double, 5>({ 2,  0,  1,  0,  0}), // 40
  std::array<double, 5>({-2,  0,  2,  2,  2}), // 41
  std::array<double, 5>({-2,  0,  1,  2,  1}), // 42
  std::array<double, 5>({ 2,  0, -2,  0,  1}), // 43
  std::array<double, 5>({ 2,  0,  0,  0,  1}), // 44
  std::array<double, 5>({ 0, -1,  1,  0,  0}), // 45
  std::array<double, 5>({-2, -1,  0,  2,  1}), // 46
  std::array<double, 5>({-2,  0,  0,  0,  1}), // 47
  std::array<double, 5>({ 0,  0,  2,  2,  1}), // 48
  std::array<double, 5>({-2,  0,  2,  0,  1}), // 49
  std::array<double, 5>({-2,  1,  0,  2,  1}), // 50
  std::array<double, 5>({ 0,  0,  1, -2,  0}), // 51
  std::array<double, 5>({-1,  0,  1,  0,  0}), // 52
  std::array<double, 5>({-2,  1,  0,  0,  0}), // 53
  std::array<double, 5>({ 1,  0,  0,  0,  0}), // 54
  std::array<double, 5>({ 0,  0,  1,  2,  0}), // 55
  std::array<double, 5>({ 0,  0, -2,  2,  2}), // 56
  std::array<double, 5>({-1, -1,  1,  0,  0}), // 57
  std::array<double, 5>({ 0,  1,  1,  0,  0}), // 58
  std::array<double, 5>({ 0, -1,  1,  2,  2}), // 59
  std::array<double, 5>({ 2, -1, -1,  2,  2}), // 60
  std::array<double, 5>({ 0,  0,  3,  2,  2}), // 61
  std::array<double, 5>({ 2, -1,  0,  2,  2})  // 62
};

const std::array<std::array<double, 4>, 63> Table2::PE =
{
  std::array<double, 4>({-171996, -174.2, 92025,  8.9}), // 0
  std::array<double, 4>( {-13187,   -1.6,  5736, -3.1}), // 1
  std::array<double, 4>({  -2274,   -0.2,   977, -0.5}), // 2
  std::array<double, 4>({   2062,    0.2,  -895,  0.5}), // 3
  std::array<double, 4>({   1426,   -3.4,    54, -0.1}), // 4
  std::array<double, 4>({    712,    0.1,    -7,  0}),   // 5
  std::array<double, 4>({   -517,    1.2,   224, -0.6}), // 6
  std::array<double, 4>({   -386,   -0.4,   200,  0}),   // 7
  std::array<double, 4>({   -301,    0,     129, -0.1}), // 8
  std::array<double, 4>({    217,   -0.5,   -95,  0.3}), // 9
  std::array<double, 4>({   -158,    0,       0,  0}),   // 10
  std::array<double, 4>({    129,    0.1,   -70,  0}),   // 11
  std::array<double, 4>({    123,    0,     -53,  0}),   // 12
  std::array<double, 4>({     63,    0,       0,  0}),   // 13
  std::array<double, 4>({     63,    0.1,   -33,  0}),   // 14
  std::array<double, 4>({    -59,    0,      26,  0}),   // 15
  std::array<double, 4>({    -58,   -0.1,    32,  0}),   // 16
  std::array<double, 4>({    -51,    0,      27,  0}),   // 17
  std::array<double, 4>({     48,    0,       0,  0}),   // 18
  std::array<double, 4>({     46,    0,     -24,  0}),   // 19
  std::array<double, 4>({    -38,    0,      16,  0}),   // 20
  std::array<double, 4>({    -31,    0,      13,  0}),   // 21
  std::array<double, 4>({     29,    0,       0,  0}),   // 22
  std::array<double, 4>({     29,    0,     -12,  0}),   // 23
  std::array<double, 4>({     26,    0,       0,  0}),   // 24
  std::array<double, 4>({    -22,    0,       0,  0}),   // 25
  std::array<double, 4>({     21,    0,     -10,  0}),   // 26
  std::array<double, 4>({     17,   -0.1,     0,  0}),   // 27
  std::array<double, 4>({     16,    0,      -8,  0}),   // 28
  std::array<double, 4>({    -16,    0.1,     7,  0}),   // 29
  std::array<double, 4>({    -15,    0,       9,  0}),   // 30
  std::array<double, 4>({    -13,    0,       7,  0}),   // 31
  std::array<double, 4>({    -12,    0,       6,  0}),   // 32
  std::array<double, 4>({     11,    0,       0,  0}),   // 33
  std::array<double, 4>({    -10,    0,       5,  0}),   // 34
  std::array<double, 4>({     -8,    0,       3,  0}),   // 35
  std::array<double, 4>({      7,    0,      -3,  0}),   // 36
  std::array<double, 4>({     -7,    0,       0,  0}),   // 37
  std::array<double, 4>({     -7,    0,       3,  0}),   // 38
  std::array<double, 4>({     -7,    0,       3,  0}),   // 39
  std::array<double, 4>({      6,    0,       0,  0}),   // 40
  std::array<double, 4>({      6,    0,      -3,  0}),   // 41
  std::array<double, 4>({      6,    0,      -3,  0}),   // 42
  std::array<double, 4>({     -6,    0,       3,  0}),   // 43
  std::array<double, 4>({     -6,    0,       3,  0}),   // 44
  std::array<double, 4>({      5,    0,       0,  0}),   // 45
  std::array<double, 4>({     -5,    0,       3,  0}),   // 46
  std::array<double, 4>({     -5,    0,       3,  0}),   // 47
  std::array<double, 4>({     -5,    0,       3,  0}),   // 48
  std::array<double, 4>({      4,    0,       0,  0}),   // 49
  std::array<double, 4>({      4,    0,       0,  0}),   // 50
  std::array<double, 4>({      4,    0,       0,  0}),   // 51
  std::array<double, 4>({     -4,    0,       0,  0}),   // 52
  std::array<double, 4>({     -4,    0,       0,  0}),   // 53
  std::array<double, 4>({     -4,    0,       0,  0}),   // 54
  std::array<double, 4>({      3,    0,       0,  0}),   // 55
  std::array<double, 4>({     -3,    0,       0,  0}),   // 56
  std::array<double, 4>({     -3,    0,       0,  0}),   // 57
  std::array<double, 4>({     -3,    0,       0,  0}),   // 58
  std::array<double, 4>({     -3,    0,       0,  0}),   // 59
  std::array<double, 4>({     -3,    0,       0,  0}),   // 60
  std::array<double, 4>({     -3,    0,       0,  0}),   // 61
  std::array<double, 4>({     -3,    0,       0,  0})    // 62
};
// clang-format on
} // SPA namespace
} // PikaUtils namespace
