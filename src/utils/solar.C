#include "solar.h"
#include <cmath>

namespace PikaUtils
{

double
julian_day(unsigned int year,unsigned int month, unsigned int day)
{
  if (month < 3)
  {
    year -= 1;
    month += 12;
  }
  double A = std::floor(year/100);
  double B = 2 - A + std::floor(A/4);
  return std::floor(365.25*(year + 4716)) + std::floor(30.6001*(month+1)) + day + B - 1524.5;
}

double
julian_day_ephemeris(const double & jd, unsigned int year)
{
  const double dt = 32. * std::pow(year - 1820./100., 2.) - 20.;
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


// Table 1 Values
// clang-format off
const std::array<std::array<double, 3>, 64> L0 =
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

// clang-format on


} // namespace
