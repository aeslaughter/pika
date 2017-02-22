[GlobalParams]
  use_displaced_mesh = true
  displacements = 'disp_x disp_y disp_z'
  velocities = 'velocity_x velocity_y velocity_z'
[]

[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 8
  ny = 8
  nz = 8
  ymin = -1
  ymax = 0
[]

[Variables]
  [./density]
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
#  [./density]
#  [../]
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

[Kernels]
  [./mass_time]
    type = CoefficientMaterialDerivative
    variable = density
    coefficient = 1
  [../]
  [./mass_div_term]
    type = MassBalanceDivergence
    variable = density
  [../]
  [./momentum_time_x]
    type = CoefficientMaterialDerivative
    variable = velocity_x
    coefficient = density
  [../]
  [./momentum_time_y]
    type = CoefficientMaterialDerivative
    variable = velocity_y
    coefficient = density
  [../]
  [./momentum_time_z]
    type = CoefficientMaterialDerivative
    variable = velocity_z
    coefficient = density
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
  [./gravity_x]
    type = Gravity
    variable = velocity_x
    value = 1
    function = -sin(30*2*pi/360)*9.81
  [../]
  [./gravity_y]
    type = Gravity
    variable = velocity_y
    value = 1
    function = -cos(30*2*pi/360)*9.81
  [../]
#  [./gravity_z]
#    type = Gravity
#    variable = velocity_z
#    value = 0
#  [../]
[]

[ICs]
  [./density]
    type = FunctionIC
    variable = density
    function = 300-x*z*-y*100
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
  [./disp_x]
    type = VelocityDeformation
    variable = disp_x
    velocity = velocity_x
    execute_on = 'initial linear'
  [../]
  [./disp_y]
    type = VelocityDeformation
    variable = disp_y
    velocity = velocity_y
    execute_on = 'initial timestep_end'
  [../]
  [./disp_z]
    type = VelocityDeformation
    variable = disp_z
    velocity = velocity_z
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
  [../]
[]

[Postprocessors]
  [./mass]
    type = Mass
    variable = density # not used
    execute_on = 'initial timestep_end'
  [../]
[]

[Preconditioning]
  [./fdp]
    type = FDP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  end_time = 86400
  dt = 7200 # 30 minutes
  solve_type = 'NEWTON'
#  line_search = none
#  l_max_its = 30
#  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
#  petsc_options_value = 'hypre    boomeramg      1000'
  petsc_options_iname = '-pc_type -ksp_gmres_restart'
  petsc_options_value = 'lu       10000'
[]

[Outputs]
  exodus = true
[]
