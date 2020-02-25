//
#include <array>

namespace PikaUtils
{

// 3.1
// 3.1.1: Eq. 4, Julian Day (JD)
double julian_day(unsigned int year, unsigned int month, unsigned int day);

// 3.1.2: Eq. 5, Julian Ephemeris Day (JDE)
// https://en.wikipedia.org/wiki/%CE%94T
double julian_day_ephemeris(const double & jd, unsigned int year);

// 3.1.3: Eq. 6, Julian Century (JC)
double julian_century(const double & jd);

// 3.1.3: Eq. 7, Julian Ephemeris Century (JCE)
double julian_century_ephemeris(const double & jde);

// 3.1.4: Eq. 8, Julian Ephemeris Millennium (JME)
double julian_millennium_ephemeris(const double & jce);

extern const std::array<std::array<double, 3>, 64> L0;



} // namespace
