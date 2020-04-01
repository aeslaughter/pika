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

#pragma once

#include "Material.h"

#include "solar.h"
#include "DateTime.h"
#include "Coordinates.h"

class Assembly;

class SolarMaterial;
template<>
InputParameters validParams<SolarMaterial>();

class SolarMaterial : public Material
{
public:
  SolarMaterial(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

private:

  PikaUtils::SPA::SolarTemporalData _temporal_data;

  PikaUtils::DateTime _datetime;

  const unsigned int _zone;
  const PikaUtils::Coordinates::UTM::Hemisphere _hemi;

  Real _temperature = 11;
  Real _pressure = 820;
  Real _atm_refraction = 0.5667;

  int _temporal_data_t_step = std::numeric_limits<int>::min();

  MaterialProperty<Real> & _slope;

};
