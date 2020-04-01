/**********************************************************************************/
/*                  Pika: Phase field snow micro-structure model                  */
/*                                                                                */
/*                     (C) 2014 Battelle Energy Alliance, LLC                     */
/*                              ALL RIGHTS RESERVED                               */
/*                                                                                */
/*                   Prepared by Battelle Energy Alliance, LLC                    */
/*                      Under Contract No. DE-AC07-05ID14517                      */
/*                      With the U. S. Department of Energy                       */
/**********************************************************************************/

#include "SolarMaterial.h"

registerMooseObject("PikaApp", SolarMaterial);




template<>
InputParameters validParams<SolarMaterial>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredRangeCheckedParam<unsigned int>("zone", "zone>0&zone<61", "The UTM zone number from 1 through 60.");

  MooseEnum hemi("NORTHERN=1 SOUTHERN=-1", "NORTHERN");
  params.addRequiredParam<MooseEnum>("hemisphere", hemi, "The hemisphere");
  params.addRequiredParam<std::string>("datetime", "The starting date and time for the solar calculation in ISO8601 UTC format (YYYY-MM-DDTHH:MM:SS.S+HH:MM)");
  return params;


  // TODO: limit to boundary only
}

SolarMaterial::SolarMaterial(const InputParameters & parameters) :
    Material(parameters),
    _datetime(getParam<std::string>("datetime")),
    _zone(getParam<unsigned int>("zone")),
    _hemi(getParam<MooseEnum>("hemisphere") == "NORTHERN" ? PikaUtils::Coordinates::UTM::Hemisphere::NORTH : PikaUtils::Coordinates::UTM::Hemisphere::SOUTH),
    _slope(declareProperty<Real>("slope")),
    _surface_azimuth(declareProperty<Real>("surface_azimuth")),
    _normal(declareProperty<RealVectorValue>("normal")),
    _solar_zenith(declareProperty<Real>("solar_zenith")),
    _solar_azimuth(declareProperty<Real>("solar_azimuth")),
    _solar_incidence(declareProperty<Real>("solar_incidence"))


{
}


void
SolarMaterial::computeQpProperties()
{
  if (_t_step != _temporal_data_t_step)
  {
    _datetime.add(0., 0., 0., 0., 0., _dt);
    _temporal_data = PikaUtils::SPA::compute_temporal_data(_datetime);
    _temporal_data_t_step = _t_step;
  }

  const Point & pt = _q_point[_qp];

  const PikaUtils::Coordinates::UTM utm(pt(0), pt(1), _zone, _hemi);
  PikaUtils::Coordinates::WGS84 wgs = PikaUtils::Coordinates::convert(utm);

  const Point & n = _normals[_qp];
  _normal[_qp] = n;
  PikaUtils::Angle slope(atan(n(2) / std::sqrt(n(0)*n(0) + n(1)*n(1))), PikaUtils::Angle::RAD);
  PikaUtils::Angle surface_azimuth(atan(std::abs(n(1))/std::abs(n(0))), PikaUtils::Angle::RAD);

  if (n(0) >= 0 && n(1) >= 0)
    _surface_azimuth[_qp] = 90. + surface_azimuth.deg();  // alpha_1 = atan2(dy, dx) + 90.
  else if (n(0) < 0 && n(1) >=0)
    _surface_azimuth[_qp] = 270. - surface_azimuth.deg(); // alpha_2 = 270. - atan2(dy, dx).
  else if (n(0) < 0 && n(1) < 0)
    _surface_azimuth[_qp] = 360. - surface_azimuth.deg(); // alpha_3 = 270. + atan2(dy, dx).
  else // if (n(0) >= 0 && n(1) < 0)
    _surface_azimuth[_qp] = 90. - surface_azimuth.deg();  // alpha_4 = 90. - atan2(dy, dx)

  _slope[_qp] = 90. - slope.deg();

  PikaUtils::SPA::LocationData location(pt(2), wgs.latitude.deg(), wgs.longitude.deg(), _temperature, _pressure, slope.deg(), surface_azimuth.deg(), _atm_refraction);
  std::pair<PikaUtils::Angle, PikaUtils::Angle> angles = PikaUtils::SPA::compute_azimuth_and_zenith(location, _temporal_data);

  _solar_azimuth[_qp] = angles.first.deg();
  _solar_zenith[_qp] = angles.second.deg();

  // TODO: Combine the two functions and return a data structure with the three angles (SolarAngles)
  PikaUtils::Angle incidence = PikaUtils::SPA::compute_incidence(location, _temporal_data);
  _solar_incidence[_qp] = incidence.deg();

}
