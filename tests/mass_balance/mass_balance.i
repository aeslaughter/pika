[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 10
  ny = 10
[]

[Variables]
  [./density]
    initial_condition = 100
  [../]
  [./velocity_x]
    initial_condition = 0
  [../]
  [./velocity_y]
    initial_condition = 0
  [../]
  [./velocity_z]
    initial_condition = 0
  [../]
[]

[AuxVariables]
  [./temperature]
    initial_condition = 263.15
  [../]
[]

[Kernels]
  [./mass_time]
    type = TimeDerivative
    variable = density
  [../]

  [./mass_velocity]
    type = MassBalanceVelocity
    variable = density
    velocity = velocity_y
    component = y
  [../]

  [./momentum_stress_x]
    type = MomentumStress
    variable = velocity_x
    component = x
  [../]

  [./momentum_stress_y]
    type = MomentumStress
    variable = velocity_y
    component = y
  [../]

  [./momentum_stress_z]
    type = MomentumStress
    variable = velocity_z
    component = z
  [../]

  [./momentum_gravity_y]
    type = Gravity
    value = -9.81
    variable = velocity_y
  [../]
[]

[BCs]
  [./bottom_vel_x]
    type = DirichletBC
    boundary = bottom
    variable = 'velocity_x'
    value = 0
  [../]
  [./bottom_vel_y]
    type = DirichletBC
    boundary = bottom
    variable = 'velocity_y'
    value = 0
  [../]
  [./bottom_vel_z]
    type = DirichletBC
    boundary = bottom
    variable = 'velocity_z'
    value = 0
  [../]
[]

[Materials]
  [./snow]
    type = IbexSnowMaterial
    density = density
    temperature = temperature
  [../]
  [./stess]
    type = ComputeIsotropicViscousStress
    velocities = 'velocity_x velocity_y velocity_z'
  [../]
[]

[Preconditioning]
  [./fdp]
    type = FDP
  [../]
[]

[Executioner]
  type = Transient
  dt = 1
  num_steps = 2
  line_search = none
  solve_type = 'NEWTON'
  l_max_its = 100
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre boomeramg 1000'
[]

[Outputs]
  exodus = true
[]
