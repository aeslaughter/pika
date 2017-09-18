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

#include "OpticRayOutput.h"

template <>
InputParameters
validParams<OpticRayOutput>()
{
  InputParameters params = validParams<Output>();
  return params;
}

OpticRayOutput::OpticRayOutput(const InputParameters & params) :
Output(params)
{

}

void
OpticRayOutput::output(const ExecFlagType & type)
{

}
