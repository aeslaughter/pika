#pragma once

namespace PikaUtils
{

/*
 * Class for defining an angle that automatically computes the value in degrees and radians and
 * optionally limits the angle between 0 and 360.
 */
class Angle
{
public:
  enum class Type{RAD=1, DEG=2};
  enum class Limit{LIMIT=1, NOLIMIT=0};

  static const Type RAD = Type::RAD;
  static const Type DEG = Type::DEG;
  static const Limit LIMIT = Limit::LIMIT;

  Angle(double value, Type type, Limit limit = Limit::NOLIMIT);
  Angle(const Angle & other);
  ~Angle() = default;

  double deg() const;
  double rad() const;

  static double radians_to_degrees(double rad);
  static double degrees_to_radians(double deg);
  static double limit_degrees(double deg);

private:
  double _radians;
  double _degrees;
};

} // namespace
