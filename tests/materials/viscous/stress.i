[Mesh]
  type = GeneratedMesh
  dim = 3
[]

[Variables]
  [./nothing]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[AuxVariables]
  [./velocity_x]
  [../]
  [./velocity_y]
  [../]
  [./velocity_z]
  [../]
  [./stress_00]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./stress_11]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./stress_22]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./stress_01]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./stress_02]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./stress_12]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[AuxKernels]
  [./vel_x]
    type = FunctionAux
    variable = velocity_x
    function = x*y*z
    execute_on = initial
  [../]
  [./vel_y]
    type = FunctionAux
    variable = velocity_y
    function = 2*x*y*z
    execute_on = initial
  [../]
  [./vel_z]
    type = FunctionAux
    variable = velocity_z
    function = 3*x*y*z
    execute_on = initial
  [../]
  [./stress_00]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_11
    index_i = 0
    index_j = 0
    execute_on = initial
  [../]
  [./stress_11]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_22
    index_i = 1
    index_j = 1
    execute_on = initial
  [../]
  [./stress_22]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_22
    index_i = 2
    index_j = 2
    execute_on = initial
  [../]
  [./stress_01]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_01
    index_i = 0
    index_j = 1
    execute_on = initial
  [../]
  [./stress_02]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_02
    index_i = 0
    index_j = 2
    execute_on = initial
  [../]
  [./stress_12]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_12
    index_i = 1
    index_j = 2
    execute_on = initial
  [../]
[]

[Materials]
  [./snow]
    type = IbexSnowMaterial
    density = 200
    temperature = 263.15
  [../]
  [./stress_rate]
    type = ComputeIsotropicViscousStress
    velocities = 'velocity_x velocity_y velocity_z'
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
