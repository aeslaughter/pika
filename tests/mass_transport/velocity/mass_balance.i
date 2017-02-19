[Mesh]
  type = GeneratedMesh
  dim = 2
[]

[Variables]
  [./nothing]
  [../]
[]

[AuxVariables]
  [./velocity_x]
  [../]
  [./velocity_y]
  [../]
[]

[ICs]
  [./vel_y]
    type = FunctionIC
    variable = velocity_y
    function = y
  [../]
[]

[AuxVariables]
  [./stress_11]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[AuxKernels]
  [./stress_11]
    type = RankTwoAux
    index_j = 1
    index_i = 1
    rank_two_tensor = stress
    variable = stress_11
    execute_on = initial
  [../]
[]

[Materials]
  [./stress]
    type = ComputeIsotropicViscousStress
    velocities = 'velocity_x velocity_y'
    poissons_ratio = 0.49
    viscosity = 1
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
