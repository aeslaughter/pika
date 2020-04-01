[Mesh]
  file = mesh_in.e
[]

[Variables]
  [u]
  []
[]

[Problem]
  solve = false
[]

[Executioner]
  type = Transient
  dt = 600
[]

[Outputs]
  exodus = true
  [perf]
    type = PerfGraphOutput
    level = 2
  []
[]
