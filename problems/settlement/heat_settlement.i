[GlobalParams]
#  use_displaced_mesh = true
  displacements = 'disp_x disp_y disp_z'
  velocities = 'velocity_x velocity_y velocity_z'
[]

[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 10
  ny = 8
  nz = 10
  xmax = 100
  zmax = 100
  ymax = 0
  ymin = -1
[]

[Variables]
  [./temperature]
  [../]
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

[ICs]
  [./density]
    type = FunctionIC
    variable = density
    function = 150-(x/100*z/100*(y-1)/2)*200
  [../]
[]

[AuxVariables]
  [./shortwave_in]
  [../]
  [./longwave_in]
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
  [./stress_xx]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 0
  [../]
  [./stress_yy]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 0
  [../]
  [./stress_zz]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 0
  [../]
[]

[Functions]
  [./shortwave]
    type = ParsedFunction
    value = 'if(-cos(2*pi*t/(24*60*60))<0, 0, -cos(2*pi*t/(24*60*60))*(SW*(z/w)*sin(pi*x/w)+300))'
    vals = '950 100'
    vars = 'SW w'
  [../]
  [./longwave]
    type = ParsedFunction
    value = sin(2*pi*t/(24*60*60))*LW/w*sin(pi*z/w)*(w-x)+180
    vals = '50 100'
    vars = 'LW w'
  [../]
[]

[Kernels]

  # HEAT EQUATION
  [./temperature_diffusion]
    # Automatically uses "thermal_conductivity" material property
    type = HeatConduction
    variable = temperature
  [../]
  [./temperature_time]
    # Automatically uses "density" and "specfic_heat" material properties
    type = HeatConductionTimeDerivative
    variable = temperature
  [../]
  [./temperature_shortwave]
    type = IbexShortwaveForcingFunction
    variable = temperature
    short_wave = shortwave
    nir_albedo = 0.81
    vis_albedo = 0.96
  [../]

  # MASS BALANCE
  [./mass_time]
    type = CoefficientMaterialDerivative
    variable = density
    coefficient = 1
  [../]
  [./mass_div_term]
    type = MassBalanceDivergence
    variable = density
  [../]

  # MOMENTUM CONSERVATION
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
  [./gravity_z]
    type = Gravity
    variable = velocity_z
    value = 0
  [../]
[]

[AuxKernels]
  [./shortwave_in_aux]
    type = FunctionAux
    variable = shortwave_in
    function = shortwave
    boundary = top
    execute_on = 'initial timestep_end'
  [../]
  [./longwave_in_aux]
    type = FunctionAux
    variable = longwave_in
    function = longwave
    boundary = top
    execute_on = 'initial timestep_end'
  [../]
  [./stess_xx]
    type = RankTwoAux
    variable = stress_xx
    index_i = 0
    index_j = 0
    rank_two_tensor = stress
    execute_on = 'initial timestep_end'
  [../]
  [./stess_yy]
    type = RankTwoAux
    variable = stress_yy
    index_i = 1
    index_j = 1
    rank_two_tensor = stress
    execute_on = 'initial timestep_end'
  [../]
  [./stess_zz]
    type = RankTwoAux
    variable = stress_zz
    index_i = 2
    index_j = 2
    rank_two_tensor = stress
    execute_on = 'initial timestep_end'
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


[ICs]
  [./temperature_initial]
    variable = temperature
    type = FunctionIC
    function = '272.15-10*(1+y)'
  [../]
[]

[BCs]
  [./top]
    type = IbexSurfaceFluxBC
    variable = temperature
    boundary = top
    air_temperature = 253.15 # -20C
    air_velocity = 5         # m/s
    relative_humidity = 50   # %
    long_wave = longwave
    short_wave = shortwave
  [../]
  [./bottom]
    type = DirichletBC
    variable = temperature
    boundary = bottom
    value = 272.15
  [../]
  [./bottom_x]
    type = DirichletBC
    variable = velocity_x
    value = 0
    boundary = 'left right'
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
    boundary = 'front back'
  [../]
[]

[Materials]
  [./snow]
    type = IbexSnowMaterial
    temperature = temperature
    density = density
  [../]
  [./stress]
    type = ComputeIsotropicViscousStress
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
  end_time = 259200 # 72 hours
  solve_type = 'NEWTON'
  petsc_options_iname = '-pc_type -ksp_gmres_restart'
  petsc_options_value = 'lu       10000'
  dt = 30
[]

[Outputs]
  checkpoint = true
  exodus = true
[]
