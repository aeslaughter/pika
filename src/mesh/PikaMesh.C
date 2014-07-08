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

#include "PikaMesh.h"

template<>
InputParameters validParams<PikaMesh>()
{
  InputParameters params = validParams<GeneratedMesh>();

  // Suppress parameters that are to be set by this object
  params.suppressParameter("nx");
  params.suppressParameter("ny");
  params.suppressParameter("nz");
  params.suppressParameter("xmin");
  params.suppressParameter("ymin");
  params.suppressParameter("xmin");
  params.suppressParameter("xmax");
  params.suppressParameter("ymax");
  params.suppressParameter("xmax");

  // Limit the element types and dimension
  MooseEnum elem_types("QUAD4, QUAD8, QUAD9, HEX8, HEX20, HEX27"); // no default
  params.set<MooseEnum>("elem_type") = elem_types;

  MooseEnum dims("2=2, 3=3");
  params.set<MooseEnum>("dim") = dims;

  // Add the file name/base
  params.addRequiredParam<FileName>("image", "The image file name (2D) or file base (3D)");

  // Add the height/width/depth that will populate xmax, ymax, zmax

  return params;
}

PikaMesh::PikaMesh(const GeneratedMesh & other_mesh) :
  GeneratedMesh(other_mesh)
{


}

PikaMesh::~PikaMesh()
{
}
