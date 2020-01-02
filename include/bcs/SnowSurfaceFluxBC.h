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

#ifndef SNOWSURFACEFLUXBC_H
#define SNOWSURFACEFLUXBC_H

// MOOSE includes
#include "ADIntegratedBC.h"

template <ComputeStage compute_stage>
class SnowSurfaceFluxBC : public ADIntegratedBC<compute_stage>
{
public:
  static InputParameters validParams();

  SnowSurfaceFluxBC(const InputParameters & parameters);

protected:

  virtual ADReal computeQpResidual() override;

private:

  ADReal longwave();

  ADReal latent();

  ADReal sensible();

  //ADReal clausiusClapeyron(const ADReal & T);
  //Real clausiusClapeyron(const Real & T);


  ADReal airDensity();

  const Real _boltzmann;

  const Real _gas_constant_air;

  const Real _gas_constant_water_vapor;

  const Real & _air_temperature;

  const Real & _relative_humidity;

  const Real & _atmospheric_pressure;

  const Real & _air_velocity;

  const Function & _long_wave;

  const Real & _emissivity;

  const Real & _ratio_of_molecular_weights;

  const Real & _latent_heat;

  const Real & _water_vapor_transport;

  const Real & _transport_coefficient;

  const Real & _reference_temperature;

  const Real & _reference_vapor_pressure;

  const Real & _specific_heat_air;

  usingIntegratedBCMembers;
};

#endif //SNOWSURFACEFLUXBC_H
