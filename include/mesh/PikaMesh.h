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

#ifndef PIKAMESH_H
#define PIKAMESH_H

// MOOSE includes
#include "GeneratedMesh.h"

// Forward declarations
class PikaMesh;

template<>
InputParameters validParams<PikaMesh>();

/**
 *
 */
class PikaMesh : public GeneratedMesh
{
public:
  PikaMesh(const std::string & name, InputParameters parameters);

  virtual ~PikaMesh();



  int multiplicity(int value, int level=0);

};

#endif //PIKAMESH_H
