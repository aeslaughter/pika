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

#include "vtkSmartPointer.h"
#include "vtkBMPReader.h"
#include "vtkPNGReader.h"


// Pika includes
#include "PikaMesh.h"
#include "PikaImageUtils.h"

template<>
InputParameters validParams<PikaMesh>()
{
  InputParameters params = validParams<GeneratedMesh>();

  // Suppress parameters that are to be set by this object

  //params.suppressParameter<int>("nx");
  //params.suppressParameter<int>("ny");
  //params.suppressParameter<int>("nz");
  params.suppressParameter<Real>("xmin");
  params.suppressParameter<Real>("ymin");
  params.suppressParameter<Real>("xmin");
  //params.suppressParameter<Real>("xmax");
  //params.suppressParameter<Real>("ymax");
  //params.suppressParameter<Real>("xmax");

  // Limit the element types and dimension
//  MooseEnum elem_types("QUAD4, QUAD8, QUAD9, HEX8, HEX20, HEX27"); // no default
//  params.set<MooseEnum>("elem_type") = elem_types;

  MooseEnum dims("2=2, 3=3");
  params.set<MooseEnum>("dim") = dims;

  // Add the file name/base
  params.addRequiredParam<FileName>("image", "The image file name (2D) or file base (3D)");

  params.addRequiredParam<VariableName>("variable", "The variable to populate");

  // Add the height/width/depth that will populate xmax, ymax, zmax
  params.addRequiredParam<Real>("width", "Width of the image (x-dir)");
  params.addRequiredParam<Real>("height", "Height of the image (y-dir)");
  params.addParam<Real>("depth", "Depth of the image (z-dir)");



  return params;
}

PikaMesh::PikaMesh(const std::string & name, InputParameters parameters) :
    GeneratedMesh(name, parameters)
{
    // PikaImageUtils::PikaImage image(getParam<FileName>("image"));
    //vtkImageData * data = image.data();

  /*
    vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
    reader->SetFileName(getParam<FileName>("image").c_str());
    reader->Update();
    vtkImageData * data = reader->GetOutput();

    int* dims = data->GetDimensions();

    parameters.set<int>("nx") = dims[0];
    parameters.set<int>("ny") = dims[1];
    parameters.set<int>("nz") = dims[2];
  */
    parameters.set<Real>("xmax") = getParam<Real>("width");
    parameters.set<Real>("ymax") = getParam<Real>("height"); // thickness ??
    parameters.set<Real>("zmax") = getParam<Real>("depth");


    //std::cout << "multiplicity = " << getMaximumMultiplicity(dims) << std::endl;


}

PikaMesh::~PikaMesh()
{
}


int
PikaMesh::multiplicity(int value, int level)
{

  if (value % 2 == 0)
    level = multiplicity(value/2, level + 1);

  return level;


}
