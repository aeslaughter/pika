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
}

SolarMaterial::SolarMaterial(const InputParameters & parameters) :
    Material(parameters),
    _datetime(getParam<std::string>("datetime")),
    _zone(getParam<unsigned int>("zone")),
    _hemi(getParam<MooseEnum>("hemisphere") == "NORTHERN" ? PikaUtils::Coordinates::UTM::Hemisphere::NORTH : PikaUtils::Coordinates::UTM::Hemisphere::SOUTH),
    _slope(declareProperty<Real>("slope"))
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
  PikaUtils::Angle slope(atan(n(2) / std::sqrt(n(0)*n(0) + n(1)*n(1))), PikaUtils::Angle::RAD);
  PikaUtils::Angle azimuth(atan(n(0)/n(1)), PikaUtils::Angle::RAD);


  _slope[_qp] = slope.deg();

  //std::pair<PikaUtils::Angle, PikaUtils::Angle> angles = PikaUtils::SPA::compute_azimuth_and_zenith(
  // PikaUtils::SPA::LocationData location(pt(2), wgs.latitude, wgs.longitude, 20, );


}
