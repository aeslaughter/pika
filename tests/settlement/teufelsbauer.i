[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 10
  ny = 10
  nz = 10
  ymin = -1
  ymax = 0
  displacements = 'disp_x disp_y disp_z'
[]

[Variables]
  #[./density]
  #[../]
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

[Kernels]
#  [./time]
#    type = TimeDerivative
#    variable = density
#    use_displaced_mesh = true
#  [../]
#  [./diffusive]
#    type = CoupledDiffusion
#    variable = density
#    velocities = 'velocity_x velocity_y velocity_z'
#    use_displaced_mesh = true
#  [../]
  [./momentum_stress_x]
    type = MomentumStress
    variable = velocity_x
    component = x
    use_displaced_mesh = true
  [../]
  [./momentum_stress_y]
    type = MomentumStress
    variable = velocity_y
    component = y
    use_displaced_mesh = true
  [../]
  [./momentum_stress_z]
    type = MomentumStress
    variable = velocity_z
    component = z
    use_displaced_mesh = true
  [../]
  [./gravity]
    type = Gravity
    variable = velocity_y
    use_displaced_mesh = true
    value = -9.81
  [../]
[]

[AuxVariables]
  [./density]
  [../]
  [./disp_x]
    initial_condition = 0
  [../]
  [./disp_y]
    initial_condition = 0
  [../]
  [./disp_z]
    initial_condition = 0
  [../]
  [./stress_yy]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 0
  [../]
[]

[ICs]
  [./density]
    type = FunctionIC
    variable = density
    function = 'if(x>0.5,250,150)'
  [../]
[]

[AuxKernels]
  [./stess_yy]
    type = RankTwoAux
    variable = stress_yy
    index_i = 1
    index_j = 1
    rank_two_tensor = stress
  [../]
  [./disp_y]
    type = VelocityDeformation
    variable = disp_y
    velocity = velocity_y
    use_displaced_mesh = true
    execute_on = 'initial timestep_end'
  [../]
[]

[BCs]
  [./bottom_x]
    type = DirichletBC
    variable = velocity_x
    value = 0
    boundary = left
  [../]
  [./bottom_y]
    type = DirichletBC
    variable = velocity_y
    value = 0
    boundary = bottom
  [../]
  [./bottom_z]
    type = DirichletBC
    variable = velocity_z
    value = 0
    boundary = front
  [../]
[]

[Materials]
  [./snow]
    type = IbexSnowMaterial
    density = density
    temperature = 263.15
    use_displaced_mesh = true
  [../]
  [./stress]
    type = ComputeIsotropicViscousStress
    velocities = 'velocity_x velocity_y velocity_z'
    use_displaced_mesh = true
  [../]
[]

[Preconditioning]
  [./fdp]
    type = FDP
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 10
  dt = 21600
  solve_type = 'PJFNK'
  line_search = none
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre    boomeramg      1000'
#  petsc_options_iname = '-pc_type -ksp_gmres_restart'
#  petsc_options_value = 'lu       10000'
[]

[Outputs]
  exodus = true
[]
