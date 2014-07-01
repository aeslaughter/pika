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
#include "Parser.h"
#include "MooseUtils.h"
#include "Moose.h"
#include "MooseApp.h"

// libMesh includes
#include "libmesh/exodusII_io.h"
#include "libmesh/nemesis_io.h"
#include "libmesh/parallel_mesh.h"

template<>
InputParameters validParams<PikaMesh>()
{
  InputParameters params = validParams<MooseMesh>();

  params.addRequiredParam<MeshFileName>("file", "Name of the image file to build mesh from");
  params.addParam<Real>("x_min", 0, "The starting position for the mesh (x-dir)");
  params.addParam<Real>("x_max", 1, "The ending position for the mesh (x-dir)");
  params.addParam<Real>("y_min", 0, "The starting position for the mesh (y-dir)");
  params.addParam<Real>("y_max", 1, "The ending position for the mesh (y-dir)");
  params.addParam<Real>("z_min", 0, "The starting position for the mesh (z-dir)");
  params.addParam<Real>("z_max", 1, "The ending position for the mesh (z-dir)");
  return params;
}

PikaMesh::PikaMesh(const std::string & name, InputParameters parameters) :
    MooseMesh(name, parameters),
    _file_name(getParam<MeshFileName>("file"))
{
}

PikaMesh::PikaMesh(const PikaMesh & other_mesh) :
    MooseMesh(other_mesh),
    _file_name(other_mesh._file_name)
{
}

PikaMesh::~PikaMesh()
{
}
void
PikaMesh::buildMesh()
{
  readImage(_file_name);


}


MooseMesh &
PikaMesh::clone() const
{
  return *(new PikaMesh(*this));
}

std::vector<Real>
PikaMesh::readImage(std::string file)
{
  /*
    int i;
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

    for(i = 0; i < size; i += 3)
    {
      unsigned char tmp = data[i];
      data[i] = data[i+2];
      data[i+2] = tmp;
    }

    return std::vector<Real>();//data;
  */

      int i;
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
    unsigned char tmp;


    std::vector<std::vector<unsigned int> > vec(height, std::vector<unsigned int>(width, 0));
    //std::vector<int> rgb(3,0);
    //std::vector<std::vector<int> > w(width, rgb);
    //std::vector<std::vector<std::vector<int> > > vec_data(height, w);


    for (int i = 0; i < height; i++)
    {
        fread(data, sizeof(unsigned char), row_padded, f);
        for (int j = 0; j < width*3; j += 3)
        {
          int value = (int)data[j] + (int)data[j+1] + (int)data[j+2];
          if (value > 0)
            vec[i][j] = 1;

          // std::cout << "vec[" << i << "][" << j << "] = " << vec[i][j] << std::endl;

          //vec_data[i][j][0] = (int)data[j];
          //vec_data[i][j][1] = (int)data[j+1];
          //vec_data[i][j][2] = (int)data[j+2];

          // Convert (B, G, R) to (R, G, B)
          //    tmp = data[j];
          //  data[j] = data[j+2];
          //  data[j+2] = tmp;

          //  cout << "R: "<< vec_data[i][j][0] << " G: " << vec_data[i][j][1]<< " B: " << (int)data[j+2]<< endl;
        }
    }

    fclose(f);

    delete data;
    return std::vector<Real>();

}
