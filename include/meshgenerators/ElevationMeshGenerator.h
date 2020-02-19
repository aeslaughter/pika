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
#include "PerfGraphInterface.h"
#include "libmesh/replicated_mesh.h"


  // https://opentopography.org

class ElevationMeshGenerator : public GeneratedMeshGenerator, PerfGraphInterface
{
public:
  static InputParameters validParams();
  ElevationMeshGenerator(const InputParameters & parameters);
  std::unique_ptr<MeshBase> generate() override;

protected:

  const FileName & _elevation_file;

  static Real interpolate(const Point & point,
                          const std::vector<Real> & x,
                          const std::vector<Real> & y,
                          const std::vector<Real> & z,
                          const Real & distance,
                          const unsigned int count);

  static Real nearest(const Point & point,
                      const std::vector<Real> & x,
                      const std::vector<Real> & y,
                      const std::vector<Real> & z,
                      const unsigned int count);


private:

  ///@{
  /// PrefGraph timers
  const PerfID _perf_generate;
  const PerfID _perf_read_data;
  const PerfID _perf_build_square;
  const PerfID _perf_interpolate;
  const PerfID _perf_displace;
  const PerfID _perf_extrude;
  ///@}

};
