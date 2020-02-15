
#include <cmath>

namespace PikaUtils
{

double
julian_day(const unsigned int & year, const unsigned int & month, const unsigned int & day)
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
julian_ephemeris_day(const double & jd, const unsigned int & year)
{
  const double dt = 32 * std::pow(year - 1820/100, 2) - 20;
  return jd + dt / 86400;
}

double
julian_century(const double & jd)
{


}

double
julian_ephemeris_century(const double & jde)
{


}




} // namespace
