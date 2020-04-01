[Mesh]
  file = mesh_out.e
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
  dt = 600 # 10 min.
  num_steps = 144
[]

[Materials]
  [solar]
    type = SolarMaterial
    boundary = surface
    datetime = '2020-03-26T00:00:00-06:00'
    zone = 12
    outputs = exodus
  []
[]

[Outputs]
  exodus = true
  [perf]
    type = PerfGraphOutput
    level = 2
  []
[]
