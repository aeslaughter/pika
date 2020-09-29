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


// MOOSE includes
#include "InitialCondition.h"

// PIKA includes
#include "PropertyUserObjectInterface.h"

//Forward Declarations
class PikaChemicalPotentialIC;

template<>
InputParameters validParams<PikaChemicalPotentialIC>();

class PikaChemicalPotentialIC :
  public InitialCondition,
  public PropertyUserObjectInterface
{
public:
  PikaChemicalPotentialIC(const InputParameters & parameters);

protected:

  /**
   * Returns the phase adjusted chemical potential at equilibrium
   */
  virtual Real value(const Point & /*p*/);

private:

  /// The coupled temperature variable
  const VariableValue & _temperature;

  /// The coupled phase-field variable
  const VariableValue & _phase;
};
