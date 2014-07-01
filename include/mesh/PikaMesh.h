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

#include "MooseMesh.h"
#include "libmesh/exodusII_io.h"

//forward declaration
class PikaMesh;

template<>
InputParameters validParams<PikaMesh>();

class PikaMesh : public MooseMesh
{
public:
  PikaMesh(const std::string & name, InputParameters parameters);
  PikaMesh(const PikaMesh & other_mesh);
  virtual ~PikaMesh();

  virtual void buildMesh();

  virtual MooseMesh & clone() const;

protected:
  /// the file_name from whence this mesh came
  std::string _file_name;

  std::vector<Real> readImage(std::string file);

};

#endif // PIKAMESH_H
