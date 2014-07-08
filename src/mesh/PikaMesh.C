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

// VTK includes
#include "vtkImageData.h"

// Pika includes
#include "PikaMesh.h"
#include "PikaImageUtils.h"

template<>
InputParameters validParams<PikaMesh>()
{
  InputParameters params = validParams<GeneratedMesh>();

  // Suppress parameters that are to be set by this object
  params.suppressParameter<int>("nx");
  params.suppressParameter<int>("ny");
  params.suppressParameter<int>("nz");
  params.suppressParameter<Real>("xmin");
  params.suppressParameter<Real>("ymin");
  params.suppressParameter<Real>("xmin");
  params.suppressParameter<Real>("xmax");
  params.suppressParameter<Real>("ymax");
  params.suppressParameter<Real>("xmax");

  // Limit the element types and dimension
  MooseEnum elem_types("QUAD4, QUAD8, QUAD9, HEX8, HEX20, HEX27"); // no default
  params.set<MooseEnum>("elem_type") = elem_types;

  MooseEnum dims("2=2, 3=3");
  params.set<MooseEnum>("dim") = dims;

  // Add the file name/base
  params.addRequiredParam<FileName>("image", "The image file name (2D) or file base (3D)");

  // Add the height/width/depth that will populate xmax, ymax, zmax
  params.addRequiredParam<Real>("width", "Width of the image (x-dir)");
  params.addRequiredParam<Real>("height", "Height of the image (y-dir)");
  params.addParam<Real>("Depth", "Depth of the image (z-dir)");



  return params;
}

PikaMesh::PikaMesh(const GeneratedMesh & other_mesh) :
  GeneratedMesh(other_mesh)
{
  if (_dim == 2)
  {
    vtkImageData * data = PikaImageUtils::readImage(getParam<FileName>("image"));


    int* dims = data->GetDimensions();
    std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << std::endl;




  }

  else if (_dim == 3)
  {
    mooseError("not yet supported");

  }


  else
    mooseError("Mesh must be have dimension value of 2 or 3");


}

PikaMesh::~PikaMesh()
{
}
