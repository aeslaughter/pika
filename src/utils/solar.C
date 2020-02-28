#include "solar.h"
#include <cmath>
#include <iostream>
#include <iomanip>

namespace PikaUtils
{

double
julian_day(unsigned int year,unsigned int month, unsigned int day, unsigned int hour, unsigned int min, double sec)
{
  if (month < 3)
  {
    year -= 1;
    month += 12;
  }
  double A = std::floor(year/100);
  double B = 2 - A + std::floor(A/4);
  double jd = std::floor(365.25*(year + 4716)) + std::floor(30.6001*(month+1)) + day + B - 1524.5;

  assert(hour < 24);
  assert(min < 60);
  assert(sec < 60);

  jd += hour/24. + min/1440. + sec/86400.;
  return jd;
}

double
julian_day_ephemeris(const double & jd, unsigned int year)
{
  const double dt = 32. * std::pow((year - 1820.)/100., 2.) - 20.;
  return jd + dt / 86400.;
}

double
julian_century(const double & jd)
{
  return (jd - 2451545.) / 36525.;
}

double
julian_century_ephemeris(const double & jde)
{
  return (jde - 2451545.) / 36525.;
}

double julian_millennium_ephemeris(const double & jce)
{
  return jce / 10.;
}

double rad_to_degrees(const double & rad)
{
  double deg = (rad * 180.)/M_PI;
  double not_used;
  double f = modf(deg/360., &not_used);
  if (deg > 0)
    deg = 360. * f;
  else if (deg < 0)
    deg = 360. - 360. * f;
  return deg;
}


double earth_heliocentric_longitude(const double & jme)
{
  double L0 = equation_ten<64>(Table1::L0, jme);
  double L1 = equation_ten<34>(Table1::L1, jme);
  double L2 = equation_ten<20>(Table1::L2, jme);
  double L3 = equation_ten<7>(Table1::L3, jme);
  double L4 = equation_ten<3>(Table1::L4, jme);
  double L5 = equation_ten<1>(Table1::L5, jme);
  double L_rad = (L0 + L1 * jme + L2 * std::pow(jme, 2) + L3 * std::pow(jme, 3) + L4 * std::pow(jme, 4) + L5 * std::pow(jme, 5)) / 1e8;
  return rad_to_degrees(L_rad);
}


// Table 1 Values
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
  std::array<double, 3>({      202, 2.4458,    6069.777}),    // 25
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
  std::array<double, 3>({       71, 1.76,       5088.63}),    // 40
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
  std::array<double, 3>({628331966747, 0,            0}),      // 0
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
  std::array<double, 3>({          36, 0.47,      775.52 }),   // 13
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
  std::array<double, 3>({          10, 1.3,      3286.6}),     // 27
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
  std::array<double, 3>({289, 5.844, 6283.076}),
  std::array<double, 3>({ 35, 0,        0}),
  std::array<double, 3>({ 17, 5.49, 12566.15}),
  std::array<double, 3>({  3, 5.2,    155.42}),
  std::array<double, 3>({  1, 4.72,     3.52}),
  std::array<double, 3>({  1, 5.3,  18849.23}),
  std::array<double, 3>({  1, 5.97,   242.73})
};

const std::array<std::array<double, 3>, 3> Table1::L4 =
{
  std::array<double, 3>({114, 3.142,    0}),
  std::array<double, 3>({  8, 4.13,  6283.08}),
  std::array<double, 3>({  1, 3.84, 12566.15})
};

const std::array<std::array<double, 3>, 1> Table1::L5 =
{
  std::array<double, 3>({1, 3.14, 0})
};

const std::array<std::array<double, 3>, 5> Table1::B0 =
{
  std::array<double, 3>({280, 3.199, 84334.662}),
  std::array<double, 3>({102, 5.422,  5507.553}),
  std::array<double, 3>({ 80, 3.88,   5223.69}),
  std::array<double, 3>({ 44, 3.7,    2352.87}),
  std::array<double, 3>({ 32, 4,      1577.34})
};

const std::array<std::array<double, 3>, 2> Table1::B1 =
{
  std::array<double, 3>({9, 3.9,  5507.55}),
  std::array<double, 3>({6, 1.73, 5223.69})
};




// clang-format on


} // namespace
