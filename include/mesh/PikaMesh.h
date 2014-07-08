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

// Forward declerations
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
  PikaMesh(const GeneratedMesh & other_mesh);
  virtual ~PikaMesh();


};

#endif //PIKAMESH_H
