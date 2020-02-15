//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElevationMeshGenerator.h"
#include "DelimitedFileReader.h"
#include "CastUniquePointer.h"
#include "BicubicInterpolation.h"

#include "libmesh/string_to_enum.h"
#include "libmesh/mesh_generation.h"
#include "libmesh/boundary_info.h"
#include "libmesh/elem.h"


registerMooseObject("MooseApp", ElevationMeshGenerator);

InputParameters
ElevationMeshGenerator::validParams()
{
  InputParameters params = GeneratedMeshGenerator::validParams();
  params.addRequiredParam<FileName>("file", "Elevation data file.");
  params.addRequiredParam<Real>("depth", "Snow depth [m]");

  params.set<MooseEnum>("dim") = 2;
  MooseEnum elem_types("QUAD4 QUAD8 QUAD9 TRI3 TRI6", "QUAD4");
  params.set<MooseEnum>("elem_type") = elem_types;

  // Suppress parameters to be set by file information
  params.suppressParameter<MooseEnum>("dim");
  params.suppressParameter<Real>("xmin");
  params.suppressParameter<Real>("ymin");
  params.suppressParameter<Real>("zmin");
  params.suppressParameter<Real>("xmax");
  params.suppressParameter<Real>("ymax");
  params.suppressParameter<Real>("zmax");

  return params;
}

ElevationMeshGenerator::ElevationMeshGenerator(const InputParameters & parameters)
: GeneratedMeshGenerator(parameters),
  _elevation_file(getParam<FileName>("file"))
{
}

std::unique_ptr<MeshBase>
ElevationMeshGenerator::generate()
{
  // https://opentopography.org

  MooseUtils::DelimitedFileReader csv_reader(_elevation_file, &_communicator);
  csv_reader.read();
  const std::vector<Real> & x = csv_reader.getData("x");
  const std::vector<Real> & y = csv_reader.getData("y");
  const std::vector<Real> & z = csv_reader.getData("z");

  const Real xmin = *std::min_element(x.begin(), x.end());
  const Real xmax = *std::max_element(x.begin(), x.end());
  const Real ymin = *std::min_element(y.begin(), y.end());
  const Real ymax = *std::max_element(y.begin(), y.end());











  const MooseEnum & elem_name = getParam<MooseEnum>("elem_type");
  const ElemType elem_type = Utility::string_to_enum<ElemType>(elem_name);

  const Real & depth = getParam<Real>("depth");

  /*
  const Real n = 5;
  unsigned int nx = std::ceil((xmax - xmin)/n);
  unsigned int ny = std::ceil((ymax - ymin)/n);
  unsigned int nz = 10*std::ceil(depth/n);

  std::cout << nx << " " << ny << " " << nz << std::endl;
  */

  auto source_mesh = libmesh_make_unique<ReplicatedMesh>(comm());
  MeshTools::Generation::build_square(static_cast<UnstructuredMesh &>(*source_mesh),
                                      _nx,
                                      _ny,
                                      xmin,
                                      xmax,
                                      ymin,
                                      ymax,
                                      elem_type,
                                      _gauss_lobatto_grid);


  std::unique_ptr<MeshBase> dest_mesh = source_mesh->clone();
  dest_mesh->clear();

  MeshTools::Generation::build_extrusion(dynamic_cast<libMesh::UnstructuredMesh &>(*dest_mesh),
                                         *source_mesh,
                                         _nz,
                                         {0,0,depth},
                                         nullptr);


  for (auto & node : as_range(dest_mesh->active_nodes_begin(), dest_mesh->active_nodes_end()))
    (*node)(2) += interpolate(*node, x ,y, z);


  BoundaryInfo & binfo = dest_mesh->get_boundary_info();
  binfo.sideset_name(0) = "south";
  binfo.sideset_name(1) = "east";
  binfo.sideset_name(2) = "north";
  binfo.sideset_name(3) = "west";
  binfo.sideset_name(4) = "ground";
  binfo.sideset_name(5) = "surface";



  return dynamic_pointer_cast<MeshBase>(dest_mesh);
}

Real
ElevationMeshGenerator::interpolate(const Point & point,
                                    const std::vector<Real> & x,
                                    const std::vector<Real> & y,
                                    const std::vector<Real> & z) const
{
  Real value;
  Real distance = std::numeric_limits<Real>::max();
  for (std::size_t i = 0; i < x.size(); ++i)
  {
    Real local = std::min(std::sqrt(std::pow(point(0) - x[i], 2) + std::pow(point(1) - y[i], 2)), distance);
    if (local < distance)
    {
      value = z[i];
      distance = local;
    }
  }
  return value;


}

// TODO: parallelize interpolate; add radius to interpolate as an option: 'nearest', 'radius'
//       add option for sizing mesh automatically to a grid size (1m, etc.) this same size should begin
//       used for the radius option in interpolate method
