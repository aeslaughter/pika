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

#ifndef OPTIC_RAY_H
#define OPTIC_RAY_H

// RayTracing includes
#include "RayKernel.h"

class OpticRayKernel;
class OpticRayStudy;
class OpticRayTracker;

template<>
InputParameters validParams<OpticRayKernel>();


class OpticRayKernel: public RayKernel
{
public:
  OpticRayKernel(const InputParameters & parameters);

  virtual void onSegment(const Elem * elem,
                         const Point & start,
                         const Point & end,
                         bool ends_in_elem) override;

protected:

  const VariableValue & _refractive_index;

  const VariableValue & _phase;
  const VariableGradient & _grad_phase;

  const OpticRayStudy & _study;

  std::shared_ptr<OpticRayTracker> _tracker;


};

#endif
