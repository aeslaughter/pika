[Mesh]
  type = GeneratedMesh
  dim = 2
[]

[Variables]
  [./nothing]
  [../]
[]

[AuxVariables]
  [./poissons_ratio]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./viscosity]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./lambda]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[AuxKernels]
  [./poissons_ratio]
    type = MaterialRealAux
    variable = poissons_ratio
    property = poissons_ratio
    execute_on = initial
  [../]
  [./viscosity]
    type = MaterialRealAux
    variable = viscosity
    property = viscosity
    execute_on = initial
  [../]
  [./lambda]
    type = MaterialRealAux
    variable = lambda
    property = lambda
    execute_on = initial
  [../]
[]

[Materials]
  [./snow]
    type = IbexSnowMaterial
    density = 200
    temperature = 263.15
  [../]
[]

[Problem]
  kernel_coverage_check = false
[]

[Executioner]
  type = Steady
[]

[Outputs]
  exodus = true
[]
