rho = 0.3
d_opt = 0.001
[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
[]

[Variables/u][]

[Materials]
  [vis]
    type = SnowOpticMaterial
    density = ${rho}
    optical_diameter =${d_opt}
    band = VIS
    outputs = exodus
  []
  [nir]
    type = SnowOpticMaterial
    density = ${rho}
    optical_diameter =${d_opt}
    band = NIR
    outputs = exodus
  []
  [swir]
    type = SnowOpticMaterial
    density = ${rho}
    optical_diameter =${d_opt}
    band = SWIR
    outputs = exodus
  []
[]

[Problem]
  type = FEProblem
  kernel_coverage_check = false
  solve = false
[]

[Executioner]
  type = Steady
[]

[Outputs]
  exodus = true
[]
