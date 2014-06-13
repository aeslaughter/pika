/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef MODELAKERNEL_H
#define MODELAKERNEL_H

#include "Kernel.h"

//Forward Declarations
class ModelAKernel;

template<>
InputParameters validParams<ModelAKernel>();

/**
 *
 */
class ModelAKernel : public Kernel
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  ModelAKernel(const std::string & name, InputParameters parameters);

  virtual ~ModelAKernel() {}

protected:
  virtual Real computeQpResidual();

  /// Material Property being used to multiply with the function of this kernel
  MaterialProperty<Real> & _m;
};

#endif // MODELAKERNEL
