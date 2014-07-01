#include "PikaBinaryIC.h"
#include "PropertyUserObject.h"
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

/*
    FILE* f = fopen(file.c_str(), "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    std::cout << "w = " << width << std::endl;
    std::cout << "h = " << height << std::endl;

    for(unsigned int i = 0; i < size; i += 3)
    {
      unsigned char tmp = data[i];
      data[i] = data[i+2];
      data[i+2] = tmp;
    }


    for (unsigned int i = 0; i < width; ++i)
    {
      for (unsigned int j = 0; j < height; ++j)
      {
        int R = data[j * width + i];
        int G = data[j * width + i + 1];
        int B = data[j * width + i + 2];

      }
    }
*/







// int i;
  FILE* f = fopen(file.c_str(), "rb");

  if(f == NULL)
    throw "Argument Exception";

  unsigned char info[54];
  fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

  // extract image height and width from header
  int width = *(int*)&info[18];
  int height = *(int*)&info[22];

  using namespace std;
  cout << endl;
  cout << "  Name: " << file << endl;
  cout << " Width: " << width << endl;
  cout << "Height: " << height << endl;

  int row_padded = (width*3 + 3) & (~3);
  unsigned char* data = new unsigned char[row_padded];
  //unsigned char tmp;


  std::vector<std::vector<unsigned int> > vec(height, std::vector<unsigned int>(width, 0));
  //std::vector<int> rgb(3,0);
  //std::vector<std::vector<int> > w(width, rgb);
  //std::vector<std::vector<std::vector<int> > > vec_data(height, w);

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


  std::cout << "nx = " << nx*r << std::endl;
  std::cout << "mesh.dimensionWidth(0) = " << mesh.dimensionWidth(0) << std::endl;
  std::cout << "mesh.dimensionWidth(1) = " << mesh.dimensionWidth(1) << std::endl;
  std::cout << "mesh.dimensionWidth(2) = " << mesh.dimensionWidth(2) << std::endl;


  std::cout << "voxel[0] = " << voxel[0] << std::endl;
  std::cout << "voxel[1] = " << voxel[1] << std::endl;


  Point centroid;

  for (int i = 0; i < height; i++)
  {
    int jj = 0;

    fread(data, sizeof(unsigned char), row_padded, f);
    for (int j = 0; j < width*3; j += 3)
    {
//      (Red * 0.3 + Green * 0.59 + Blue * 0.11)
      int value = 2*(0.3*(int)data[j]/255 + 0.59*(int)data[j+1]/255 + 0.11*(int)data[j+2]/255) - 1;


      centroid(0) = jj*voxel[0] + voxel[0]/2;
      centroid(1) = i*voxel[1] + voxel[1]/2;

      //centroid.print();
      //std::cout << std::endl;

      const Elem * elem = pl(centroid);
      if (elem == NULL)
        mooseError("This isn't supposed to happen");
      _centroid_map[elem->id()] = (int)data[j];

      std::cout << "i = " << i << "; jj = " << jj << "; value = " << (int)data[j] << "; id = " << elem->id()<< std::endl;


      jj++;



    }
  }
  fclose(f);

  delete data;


}
