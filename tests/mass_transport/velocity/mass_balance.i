[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
[]

[Variables]
  [./velocity_x]
    initial_condition = 0
  [../]
  [./velocity_y]
    initial_condition = 0
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
  [../]
[]

[Kernels]
  [./gravity_x]
    type = Gravity
    value = 0.0
    variable = velocity_x
  [../]
  [./gravity_y]
    type = Gravity
    value = 9.81
    variable = velocity_y
  [../]
[]

[BCs]
  [./velocity_x]
    type = DirichletBC
    variable = velocity_x
    value = 0
    boundary = bottom
  [../]
  [./velocity_y]
    type = DirichletBC
    variable = velocity_y
    value = 0
    boundary = bottom
  [../]
[]

[Materials]
  [./snow]
    type = IbexSnowMaterial
    density = 200
    temperature = 263.15
  [../]
  [./stress]
    type = ComputeIsotropicViscousStress
    velocities = 'velocity_x velocity_y'
  [../]
[]

[Preconditioning]
  [./fdp]
    type = FDP
  [../]
[]

[Executioner]
  type = Steady
  l_max_its = 100
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre boomeramg 1000'
[]

[Outputs]
  exodus = true
[]
