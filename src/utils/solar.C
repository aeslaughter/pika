
#include <cmath>

namespace PikaUtils
{

double
julian_day(unsigned int Y, unsigned int M, unsigned int D)
{
  if (M < 3)
  {
    Y -= 1;
    M += 12;
  }
  double A = std::floor(Y/100);
  double B = 2 - A + std::floor(A/4);
  return std::floor(365.25*(Y + 4716)) + std::floor(30.6001*(M+1)) + D + B - 1524.5;
}

} // namespace
