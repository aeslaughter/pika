
#include "libmesh/equation_systems.h"
#include "libmesh/explicit_system.h"

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
    _file_name(getParam<MeshFileName>("file")),
    _image_mesh_ptr(NULL),
    _image_es_ptr(NULL),
    _image_mesh_function(NULL)
{
}

PikaBinaryIC::~PikaBinaryIC()
{
  delete _image_mesh_ptr;
  delete _image_es_ptr;
  delete _image_mesh_function;
}


Real
PikaBinaryIC::value(const Point & p)
{
  return (*_image_mesh_function)(p);

  //return _centroid_map[_current_elem->id()];
}

void
PikaBinaryIC::initialSetup()
{
  // Read the image
  vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
  reader->SetFileName(_file_name.c_str());
  reader->Update();
  vtkImageData * data = reader->GetOutput();
  int* dims = data->GetDimensions();

  // create mesh from dims read from file (see Generated Mesh)

  _image_mesh_ptr = new Mesh(_communicator);

  MeshTools::Generation::build_square(*_image_mesh_ptr,
                                      dims[0], dims[1],
                                      0, 1, // TODO: add params for xmax,ymax,zmax...
                                      0, 1,
                                      QUAD4);



  // create a EquationSystems
  _image_es_ptr = new EquationSystems(*_image_mesh_ptr);

  // add ExplicitSystem
  ExplicitSystem & image_sys = _image_es_ptr->add_system<ExplicitSystem>("_pika_mesh_system");

  // add constant monomial variable
  image_sys.add_variable("_pika_mesh_variable", FEType(CONSTANT, MONOMIAL));

  _image_es_ptr->init();


  // Need to figure out population of the local_solution
  //  In readImage the idx == elem->id(), so this could be used to only update values on the local solution

  readImage();




  _image_es_ptr->print_info(std::cout);


  std::cout << "n_dofs = " << image_sys.n_dofs() << std::endl;


  // create mesh function
  AutoPtr<NumericVector<Number> > serialized_solution = NumericVector<Number>::build(_communicator);
  serialized_solution->init(image_sys.n_dofs(), false, SERIAL);
  image_sys.solution->localize(*serialized_solution);


  _image_mesh_function = new MeshFunction(*_image_es_ptr, *serialized_solution, image_sys.get_dof_map(), 0);
  _image_mesh_function->init();

//  readImage(_file_name);
}

void
PikaBinaryIC::readImage()
{
  ExplicitSystem & image_sys = _image_es_ptr->get_system<ExplicitSystem>("_pika_mesh_system");

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


  vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
  reader->SetFileName(_file_name.c_str());
  reader->Update();
  vtkImageData * data = reader->GetOutput();

  //  PikaImageUtils::PikaImage image(getParam<FileName>("image"));
  //  vtkImageData * data = image.data();

  int* dims = data->GetDimensions();
  std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << std::endl;

  std::cout << "Number of points: " << data->GetNumberOfPoints() << std::endl;
  std::cout << "Number of cells: " << data->GetNumberOfCells() << std::endl;
std::cout << "Type: " << data->GetScalarTypeAsString() << std::endl;



// std::vector<std::vector<unsigned int> > img(dims[1], std::vector<unsigned int>(dims[0], 0));

  Point centroid;

  unsigned int idx;

  for (int z = 0; z < dims[2]; z++)
    for (int y = 0; y < dims[1]; y++)
    {
      for (int x = 0; x < dims[0]; x++)
      {
        double pixel = data->GetScalarComponentAsDouble(x,y,z,0);


        //std::cout << "pixel(" << x << ", " << y <<  ") = " << pixel << std::endl;

//std::cout << "pixel(" << x << ", " << y <<  ") = " << pixel[0] << " " << pixel[1] << " " << pixel[2] << std::endl;

        centroid(0) = x*voxel[0] + voxel[0]/2;
        centroid(1) = y*voxel[1] + voxel[1]/2;

        int value = 1;
        if (pixel > 20) // add threshold param (auto to 2 * min???)
          value = -1;

        // This needs to be fixed to work in parallel
//        image_sys.current_local_solution->set(idx, pixel);
        idx++;


        const Elem * elem = pl(centroid);
        if (elem == NULL)
          mooseError("This isn't supposed to happen");
        _centroid_map[elem->id()] = value;
      }
    }
  _console << "Image reading complete" << std::endl;
}
