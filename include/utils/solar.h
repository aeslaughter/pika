#include <array>
//#include <regex>

namespace PikaUtils
{
namespace SPA
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

/*
 * Class for computing the various times required for solar incident angle calculations.
 */
class DateTime
{
public:
  enum class Format{ISO8601};
  DateTime(const std::string & date, Format format = Format::ISO8601);
  void add(int years, int months, int day, int hours, int minutes, double seconds);

  int year() const {return _tinfo.tm_year + 1900;}
  int month() const {return _tinfo.tm_mon + 1;}
  int day() const {return _tinfo.tm_mday;}
  int hour() const {return _tinfo.tm_hour;}
  int minute() const {return _tinfo.tm_min;}
  double second() const {return _fraction_sec + static_cast<double>(_tinfo.tm_sec);}

private:
  struct tm _tinfo;
  double _fraction_sec = 0;
};

// 3.1.1: Eq. 4
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
double limit_degrees(double deg);

// 3.2.1 - 3.2.6: Eq. 9, 10, 11, 12
double earth_heliocentric_longitude(double jme);

// 3.2.7: Eq. 9, 10, 11, 12
double earth_heliocentric_latitude(double jme);

// 3.2.8: Eq. 9, 10, 11, 12
double earth_radius_vector(double jme);

// 3.3.1, 3.3.2: Eq. 13
double geocentric_longitude(double L);

// 3.3.3: Eq. 14
double geocentric_latitude(double B);

// 3.4.1: Eq. 15
double mean_elongation_moon(double jce);

// 3.4.2: Eq. 16
double mean_anomaly_sun(double jce);

// 3.4.3, Eq. 17
double mean_anomaly_moon(double jce);

// 3.4.4: Eq. 18
double argument_latitute_moon(double jce);

// 3.4.5: Eq. 19
double ascending_longitude_moon(double jce);

// 3.4.7: Eq. 22
double nutation_longitude(double jce);

// 3.4.8: Eq. 23
double nutation_obliquity(double jce);

// 3.5.1: Eq. 24
double mean_obliquity_ecliptic(double jme);

// 3.5.2: Eq. 25
double true_obliquity_ecliptic(double eps0, double delta_eps);

// 3.6: Eq. 26
double aberration_correction(double R);

// 3.7: Eq. 27
double apparent_sun_longitude(double theta, double delta_psi, double delta_tau);

// 3.8.1, 3.8.2: Eq. 28
double mean_sidereal_time_greenwich(double jd, double jc);

// 3.8.3: Eq. 29
double apparent_sidereal_time_greenwich(double nu0, double delta_psi, double eps);

// 3.9: Eq. 30
double sun_right_ascension(double lambda, double eps, double beta);

// 3.10: Eq. 31
double geocentric_sun_declination(double lambda, double eps, double beta);

// 3.11: Eq. 32
double observer_local_hour_angle(double nu, double longitude, double alpha);

// 3.12.1: Eq. 33
double equatorial_horizontal_parallax(double R);

// 3.12.2-3.12.5: Eq. 34, 35, 36, 37
double parallax_sun_right_ascension(double latitude, double elevation, double xi, double H, double delta);

// 3.12.6: Eq. 38
double topocentric_sun_right_ascension(double alpha, double delta_alpha);

// 3.12.7: Eq. 39
double topocentric_sun_declination(double latitude, double elevation, double delta, double xi, double delta_alpha, double H);

// 3.13: Eq. 40
double topocentric_local_hour_angle(double H, double delta_alpha);

// 3.14.1: Eq. 41
double topocentric_zenith_angle_no_correction(double latitude, double delta_prime, double H_prime);

// 3.14.2: Eq. 42
double atomspheric_refraction_correction(double P, double T, double e0, double atm_refraction);

// 3.14.3: Eq. 43
double topocentric_elevation_angle(double e0, double delta_e);

// 3.14.4: Eq. 44
double topocentric_zenith_angle(double e);

// 3.15.1: Eq. 45
double topocentric_astronomers_azimuth(double latitude, double H_prime, double delta_prime);

// 3.15.2: Eq. 46
double topocentric_azimuth_angle(double gamma);

// 3.16: Eq. 47
double incidence_angle(double zenith, double slope, double azimuth, double gamma);

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

namespace Table2
{
extern const std::array<std::array<double, 5>, 63> Y;
extern const std::array<std::array<double, 4>, 63> PE;
}

} // SPA namespace
} // PikaUtils namespace
