
// Pika includes
#include "PikaBinaryIC.h"
#include "PropertyUserObject.h"
#include "PikaImageUtils.h"

#include <stdio.h>


// VTK includes
#include "vtkImageData.h"


template<>
InputParameters validParams<PikaBinaryIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addRequiredParam<MeshFileName>("file", "The name of the image file to read");
  return params;
}

PikaBinaryIC::PikaBinaryIC(const std::string & name, InputParameters parameters) :
    InitialCondition(name, parameters),
    _file_name(getParam<MeshFileName>("file"))

{
}

Real
PikaBinaryIC::value(const Point & /*p*/)
{
  return _centroid_map[_current_elem->id()];
}

void
PikaBinaryIC::initialSetup()
{
  readImage(_file_name);
}

void
PikaBinaryIC::readImage(std::string file)
{

  MooseMesh & mesh = _fe_problem.mesh();

  const PointLocatorBase & pl = mesh.getMesh().point_locator();


  Real r = std::pow(2., (int)mesh.uniformRefineLevel());

  int nx = mesh.getParam<int>("nx");
  int ny = mesh.getParam<int>("ny");
  int nz = mesh.getParam<int>("nz");


  std::vector<Real> voxel(3,0);
  voxel[0] = mesh.dimensionWidth(0) / (nx * r);
  voxel[1] = mesh.dimensionWidth(1) / (ny * r);
  voxel[2] = mesh.dimensionWidth(2) / (nz * r);

/*
  std::cout << "nx = " << nx*r << std::endl;
  std::cout << "mesh.dimensionWidth(0) = " << mesh.dimensionWidth(0) << std::endl;
  std::cout << "mesh.dimensionWidth(1) = " << mesh.dimensionWidth(1) << std::endl;
  std::cout << "mesh.dimensionWidth(2) = " << mesh.dimensionWidth(2) << std::endl;


  std::cout << "voxel[0] = " << voxel[0] << std::endl;
  std::cout << "voxel[1] = " << voxel[1] << std::endl;
*/



  // Read VTK data
//  vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();


//  vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
//  reader->SetFileName(file.c_str());
//  reader->Update();


  vtkImageData * data = PikaImageUtils::readImage(file); //reader->GetOutput();

  int* dims = data->GetDimensions();
  std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << std::endl;

  std::cout << "Number of points: " << data->GetNumberOfPoints() << std::endl;
  std::cout << "Number of cells: " << data->GetNumberOfCells() << std::endl;
std::cout << "Type: " << data->GetScalarTypeAsString() << std::endl;



  std::vector<std::vector<unsigned int> > img(dims[1], std::vector<unsigned int>(dims[0], 0));

  Point centroid;


  for (int z = 0; z < dims[2]; z++)
    for (int y = 0; y < dims[1]; y++)
    {
      for (int x = 0; x < dims[0]; x++)
      {
        double pixel = data->GetScalarComponentAsDouble(x,y,z,0);

std::cout << "pixel(" << x << ", " << y <<  ") = " << pixel << std::endl;

//std::cout << "pixel(" << x << ", " << y <<  ") = " << pixel[0] << " " << pixel[1] << " " << pixel[2] << std::endl;

        centroid(0) = x*voxel[0] + voxel[0]/2;
        centroid(1) = y*voxel[1] + voxel[1]/2;

        int value = 1;
        if (pixel > 20) // add threshold param (auto to 10% the min???)
          value = -1;

        const Elem * elem = pl(centroid);
        if (elem == NULL)
          mooseError("This isn't supposed to happen");
        _centroid_map[elem->id()] = value;
      }
    }
  _console << "Image reading complete" << std::endl;
}
