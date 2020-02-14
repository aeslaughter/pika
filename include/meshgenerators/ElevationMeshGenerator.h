//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "GeneratedMeshGenerator.h"
#include "libmesh/replicated_mesh.h"

class ElevationMeshGenerator : public GeneratedMeshGenerator
{
public:
  static InputParameters validParams();
  ElevationMeshGenerator(const InputParameters & parameters);
  std::unique_ptr<MeshBase> generate() override;

protected:

  const FileName & _elevation_file;

  Real interpolate(const Point & point,
                   const std::vector<Real> & x,
                   const std::vector<Real> & y,
                   const std::vector<Real> & z) const;

};
