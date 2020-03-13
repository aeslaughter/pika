#include <cmath>

#include "Angle.h"

namespace PikaUtils
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

Angle::Angle(const Angle & other)
{
  _degrees = other._degrees;
  _radians = other._radians;
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

} // namespace
