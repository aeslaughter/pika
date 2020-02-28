//
#include <array>

namespace PikaUtils
{

// 3.1
// 3.1.1: Eq. 4, Julian Day (JD)
double julian_day(unsigned int year, unsigned int month, unsigned int day, unsigned int hour,
                  unsigned int min, double sec, double timezone, double dut1);

// This is an optional estimate of dt for equation below
// https://eclipse.gsfc.nasa.gov/SEcat5/deltat.html
double delta_t(unsigned int year);

// 3.1.2: Eq. 5, Julian Ephemeris Day (JDE)
double julian_day_ephemeris(double jd, double dt);

// 3.1.3: Eq. 6, Julian Century (JC)
double julian_century(double jd);

// 3.1.3: Eq. 7, Julian Ephemeris Century (JCE)
double julian_century_ephemeris(double jde);

// 3.1.4: Eq. 8, Julian Ephemeris Millennium (JME)
double julian_millennium_ephemeris(double jce);

// 3.2.1: Eq. 10
template<std::size_t N>
double equation_ten(const std::array<std::array<double, 3>, N> & data, double jme)
{
  double out = 0.;
  for (std::size_t i = 0; i < N; ++i)
    out += data[i][0] * cos(data[i][1] + data[i][2] * jme);
  return out;
}

// 3.2.6
double rad_to_degrees(double rad);

// 3.2.7: Limits degree calculation to 360
double limit_to_360(double deg);

// 3.2.1 - 3.2.6: Eq. 9, 10, 11, 12
double earth_heliocentric_longitude(double jme);

// 3.2.7: Eq. 9, 10, 11, 12
double earth_heliocentric_latitude(double jme);

// 3.2.8: Eq. 9, 10, 11, 12
double earth_radius_vector(double jme);

// 3.3.1, 3.3.2: Eq. 13
double geocentric_longitude(double L);

// 3.3.3, Eq. 14
double geocentric_latitude(double B);

// 3.4.1, Eq. 15
double mean_elongation_moon(double jce);

// 3.4.2, Eq. 16
double mean_elongation_sun(double jce);

// 3.4.3, Eq. 17
double mean_anomaly_moon(double jce);

// 3.4.4, Eq. 18
double argument_latitute_moon(double jce);

// 3.4.5, Eq. 19
double ascending_longitude_moon(double jce);


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
extern const std::array<std::array<double, 3>, 40> R0;
extern const std::array<std::array<double, 3>, 10> R1;
extern const std::array<std::array<double, 3>, 6> R2;
extern const std::array<std::array<double, 3>, 2> R3;
extern const std::array<std::array<double, 3>, 1> R4;
} // table 1

} // namespace
