/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PIKAWATERVAPORCONCENTRATION_H
#define PIKAWATERVAPORCONCENTRATION_H

// MOOSE includes
#include "AuxKernel.h"

// Pika includes
#include "PropertyUserObjectInterface.h"

// Forward declarations
class PikaWaterVaporConcentration;

template<>
InputParameters validParams<PikaWaterVaporConcentration>();

/**
 *
 */
class PikaWaterVaporConcentration :
  public AuxKernel,
  public PropertyUserObjectInterface
{
public:

  /**
   * Class constructor
   * @param name
   */
  PikaWaterVaporConcentration(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~PikaWaterVaporConcentration();

protected:

  /**
   *  Computes the value of the water vapor concentration
   */
  virtual Real computeValue();

private:

  /// Coupled chemical potential variable
   const VariableValue & _s;

  /// Reference to ice density stored in PropertyUserObject
  const Real _rho_i;

  /// Reference to the reference temperature stored in PropertyUserObject
  const Real & _T_0;

};

#endif //PIKAWATERVAPORCONCENTRATION_H
