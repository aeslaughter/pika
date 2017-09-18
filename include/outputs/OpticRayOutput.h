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

#include "Output.h"

class OpticRayOutput;

template<>
InputParameters
validParams<OpticRayOutput>();

class OpticRayOutput : public Output
{
public:
  OpticRayOutput(const InputParameters & params);
  virtual void output(const ExecFlagType & type);
};
