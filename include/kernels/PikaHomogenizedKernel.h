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

#include "HomogenizedHeatConduction.h"

//PIKA Include
#include "PropertyUserObjectInterface.h"
#include "CoefficientKernelInterface.h"

class PikaHomogenizedKernel : public
  HomogenizedHeatConduction,
  CoefficientKernelInterface
{
public:

  PikaHomogenizedKernel(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

};

template<>
InputParameters validParams<PikaHomogenizedKernel>();
