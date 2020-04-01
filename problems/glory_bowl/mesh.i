[Mesh]
  [elevation]
    type = ElevationMeshGenerator
    file = mount_glory.csv
    nx = 50
    ny = 50
    nz = 5
    grid_size = 3
    depth = 2

    interpolate_distance = 5
    interpolate_count = 5
  []
[]

[Variables]
  [u]
  []
[]

[Problem]
  solve = false
[]

[Executioner]
  type = Steady
[]

[Outputs]
  exodus = true
  [perf]
    type = PerfGraphOutput
    level = 2
  []
[]
