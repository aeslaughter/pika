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

  params.set<unsigned int>("nx") = 0;
  params.set<unsigned int>("ny") = 0;
  params.set<unsigned int>("nz") = 0;

  params.addParam<Real>("grid_size", 1, "The grid size to used for auto computing the number of elements, when nx and/or ny are zero.");

  params.addParam<Real>("interpolate_distance", 2, "The distance to consider when interpolating grid points.");
  params.addParam<unsigned int>("interpolate_count", 3, "The number of nearest points to consider when interpolating and distance is not satisfied.");


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
  PerfGraphInterface(this),
  _elevation_file(getParam<FileName>("file")),
  _perf_generate(registerTimedSection("generate", 1)),
  _perf_read_data(registerTimedSection("read topography", 2)),
  _perf_build_square(registerTimedSection("build 2D grid", 2)),
  _perf_interpolate(registerTimedSection("interpolate points", 2)),
  _perf_displace(registerTimedSection("interpolate points", 2)),
  _perf_extrude(registerTimedSection("extrude", 2))
{
}

std::unique_ptr<MeshBase>
ElevationMeshGenerator::generate()
{
  TIME_SECTION(_perf_generate);

  MooseUtils::DelimitedFileReader csv_reader(_elevation_file, &_communicator);
  {
    TIME_SECTION(_perf_read_data);
    csv_reader.read();
  }

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
  const Real & n = getParam<Real>("grid_size");

  unsigned int nx = getParam<unsigned int>("nx");
  if (nx == 0)
    nx = std::ceil((xmax - xmin)/n);

  unsigned int ny = getParam<unsigned int>("ny");
  if (ny == 0)
    ny = std::ceil((xmax - xmin)/n);

  // TODO: compute the depth to result in cubes
  unsigned int nz = getParam<unsigned int>("nz");
  if (nz == 0)
    nz = std::ceil(depth/n);

  auto source_mesh = libmesh_make_unique<ReplicatedMesh>(comm());
  {
    TIME_SECTION(_perf_build_square);
    MeshTools::Generation::build_square(static_cast<UnstructuredMesh &>(*source_mesh),
                                        nx,
                                        ny,
                                        xmin,
                                        xmax,
                                        ymin,
                                        ymax,
                                        elem_type,
                                        _gauss_lobatto_grid);
  }

  std::unique_ptr<MeshBase> dest_mesh = source_mesh->clone();
  dest_mesh->clear();

  const Real & distance = getParam<Real>("interpolate_distance");
  const unsigned int & count = getParam<unsigned int>("interpolate_count");

  std::set<std::pair<dof_id_type, Real>> elev;
  {
    TIME_SECTION(_perf_interpolate);
    for (auto & node : as_range(source_mesh->local_nodes_begin(), source_mesh->local_nodes_end()))
      elev.emplace(node->id(), interpolate(*node, x ,y, z, distance, count));
    _communicator.set_union(elev);
  }

  {
    TIME_SECTION(_perf_displace);
    for (auto & pair : elev)
    {
      auto node = source_mesh->node_ptr(pair.first);
      (*node)(2) += pair.second;
    }
  }

  {
    TIME_SECTION(_perf_extrude);
    MeshTools::Generation::build_extrusion(dynamic_cast<libMesh::UnstructuredMesh &>(*dest_mesh),
                                           *source_mesh,
                                           nz,
                                           {0,0,depth},
                                           nullptr);
  }



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
                                    const std::vector<Real> & z,
                                    const Real & distance,
                                    const unsigned int near)
{
  Real value = 0;
  std::size_t count = 0;
  for (std::size_t i = 0; i < x.size(); ++i)
  {
    Real local = std::sqrt(std::pow(point(0) - x[i], 2) + std::pow(point(1) - y[i], 2));
    if (local < distance)
    {
      value += z[i];
      count += 1;
    }
  }

  if (count == 0)
    return nearest(point, x ,y, z, near);
  return value / count;


}

Real
ElevationMeshGenerator::nearest(const Point & point,
                                    const std::vector<Real> & x,
                                    const std::vector<Real> & y,
                                    const std::vector<Real> & z,
                                    const unsigned int count)
{
  std::deque<Real> values;
  Real distance = std::numeric_limits<Real>::max();
  for (std::size_t i = 0; i < x.size(); ++i)
  {
    Real local = std::sqrt(std::pow(point(0) - x[i], 2) + std::pow(point(1) - y[i], 2));
    if (local < distance)
    {
      distance = local;
      values.emplace_front(z[i]);
    }

    if (values.size() > count)
      values.pop_back();
  }

  return std::accumulate(values.begin(), values.end(), 0.) / count;
}

// TODO: parallelize interpolate; add radius to interpolate as an option: 'nearest', 'radius'
//       add option for sizing mesh automatically to a grid size (1m, etc.) this same size should begin
//       used for the radius option in interpolate method
