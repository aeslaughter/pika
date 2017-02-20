[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 15
  ny = 3
  nz = 15
  xmax = 100
  zmax = 100
  ymax = 0
  ymin = -1
[]

[Variables]
  [./temperature]
  [../]
[]

[AuxVariables]
  [./shortwave_in]
  [../]
  [./longwave_in]
  [../]
[]

[Functions]
  [./shortwave]
    type = ParsedFunction
    value = sin(2*pi*t/(h*3600))*(SW/w*sin(pi*x/w)*z+300)
    vals = '950 100 12'
    vars = 'SW w h'
  [../]
  [./longwave]
    type = ParsedFunction
    value = LW/w*sin(pi*z/w)*(w-x)+175
    vals = '50 100'
    vars = 'LW w'
  [../]
[]

[Kernels]
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
[]

[Materials]
  [./snow]
    type = IbexSnowMaterial
    temperature = temperature
    density = 300
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  scheme = crank-nicolson
  end_time = 43200
  dtmax = 300
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 30
  [../]
[]

[Adaptivity]
  max_h_level = 2
  marker = marker
  [./Markers]
    [./marker]
      type = ErrorFractionMarker
      indicator = error
      refine = 0.9
      coarsen = 0.1
    [../]
  [../]
  [./Indicators]
    [./error]
      type = GradientJumpIndicator
      variable = temperature
    [../]
  [../]
[]

[Outputs]
  exodus = true
[]
