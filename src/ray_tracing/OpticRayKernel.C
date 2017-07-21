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

// Pika includes
#include "OpticRayKernel.h"

template<>
InputParameters
validParams<OpticRayKernel>()
{
  InputParameters params = validParams<RayKernel>();
  return params;
}


OpticRayKernel::OpticRayKernel(const InputParameters & parameters) :
    RayKernel(parameters)
{
}

void
OpticRayKernel::onSegment(const Elem * elem, const Point & start, const Point & end, bool ends_in_elem)
{
}


