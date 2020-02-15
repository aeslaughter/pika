//


namespace PikaUtils
{

// 3.1
// 3.1.1: Eq. 4, Julian Day (JD)
double julian_day(const unsigned int & year, const unsigned int & month, const unsigned int & day);

// 3.1.2: Eq. 5, Julian Ephemeris Day (JDE)
// https://en.wikipedia.org/wiki/%CE%94Ts
double julian_ephemeris_day(const double & jd, const unsigned int & year);

// 3.1.3: Eq. 6, Julian Century (JC)
double julian_century(const double & jd);

// 3.1.4: Eq. 6, Julian Ephemeris Century (JCE)
double julian_ephemeris_century(const double & jde);


} // namespace
