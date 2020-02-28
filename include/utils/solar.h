//
#include <array>

namespace PikaUtils
{

// 3.1
// 3.1.1: Eq. 4, Julian Day (JD)
double julian_day(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int min, double sec);

// 3.1.2: Eq. 5, Julian Ephemeris Day (JDE)
// https://en.wikipedia.org/wiki/%CE%94T
double julian_day_ephemeris(const double & jd, unsigned int year);

// 3.1.3: Eq. 6, Julian Century (JC)
double julian_century(const double & jd);

// 3.1.3: Eq. 7, Julian Ephemeris Century (JCE)
double julian_century_ephemeris(const double & jde);

// 3.1.4: Eq. 8, Julian Ephemeris Millennium (JME)
double julian_millennium_ephemeris(const double & jce);

// 3.2.1: Eq. 10
template<std::size_t N>
double equation_ten(const std::array<std::array<double, 3>, N> & data, const double & jme)
{
  double out = 0.;
  for (std::size_t i = 0; i < N; ++i)
    out += data[i][0] * cos(data[i][1] + data[i][2] * jme);
  return out;
}

// 3.2.6
double rad_to_degrees(const double & rad);

// 3.2.1 - 3.2.6: Eq. 9, 10, 11, 12
double earth_heliocentric_longitude(const double & jme);


namespace Table1
{
extern const std::array<std::array<double, 3>, 64> L0;
extern const std::array<std::array<double, 3>, 34> L1;
extern const std::array<std::array<double, 3>, 20> L2;
extern const std::array<std::array<double, 3>, 7> L3;
extern const std::array<std::array<double, 3>, 3> L4;
extern const std::array<std::array<double, 3>, 1> L5;
extern const std::array<std::array<double, 3>, 5> B0;
extern const std::array<std::array<double, 3>, 2> B1;

} // table 1

} // namespace
