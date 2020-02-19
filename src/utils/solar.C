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
};

// clang-format on


} // namespace
