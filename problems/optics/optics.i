kappa0 = 10
kappa1 = 60

alpha0 = 0.94
alpha1 = -0.23

density0 = 174
density1 = 120

q_in = 50
g = 0

[Mesh]
  type = GeneratedMesh
  #second_order = true
  dim = 3
  nx = 10
  ny = 7
  nz = 10
  xmax = 1
  zmax = 1
  ymin = -0.7
  ymax = 0
  uniform_refine = 3
[]

[Adaptivity]
  marker = marker
  max_h_level = 3
  [Indicators]
    [error]
      type = GradientJumpIndicator
      variable = T
    []
  []
  [Markers]
    [marker]
      type = ErrorFractionMarker
      indicator = error
      coarsen = 0.15
      refine = 0.7
    []
  []
[]

[Variables]
 [u]
   #order = SECOND
 []
 [T]
   #order = SECOND
 []
[]

[ICs]
  [T_initial]
    variable = T
    type = ConstantIC
    value = 263.15
  []
[]

[Kernels]
  [T_diffusion]
    # Automatically uses "thermal_conductivity" material property
    type = ADHeatConduction
    variable = T
  []
  [T_time]
    # Automatically uses "density" and "specfic_heat" material properties
    type = ADHeatConductionTimeDerivative
    variable = T
  []

  [T_irradiance]
    type = IrradianceSource
    variable = T
    irradiance = u
  []

  [diffusion]
    type = OpticDiffusion
    variable = u
  []
  [absorption]
    type = OpticAbsorption
    variable = u
  []
[]

[BCs]
  [T_bottom]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 263.15
  []

  [T_top]
    type = SnowSurfaceFluxBC
    variable = T
    boundary = top
    long_wave = 235
  []

  [source]
    type = DirichletBC
    variable = u
    boundary = top
    value = ${q_in}
  []
[]

[Functions]
  [density]
    type = ParsedFunction
    value = if(y>=-0.1&y<=-0.05,${density0}+${density1}*sin(pi*x)*sin(pi*z),${density0})
  []
  [kappa]
    type = ParsedFunction
    value = if(y>=-0.1&y<=-0.05,${kappa0}+${kappa1}*sin(pi*x)*sin(pi*z),${kappa0})
  []
  [alpha]
    type = ParsedFunction
    value = if(y>=-0.1&y<=-0.05,${alpha0}+${alpha1}*sin(pi*x)*sin(pi*z),${alpha0})
  []
[]

[VectorPostprocessors]
  [center]
    type = LineValueSampler
    start_point = '0.5 0 0.5'
    end_point = '0.5 -0.7 0.5'
    num_points = 200
    variable = T
    sort_by = y
  []
[]

[Materials]
  [snow]
    type = GenericFunctionMaterial
    prop_names =  'density effective_attenuation_coefficient single_scattering_albedo'
    prop_values = 'density kappa                             alpha'
    #outputs = out
  []
  [snow_optics]
    type = SnowOpticMaterial
    scattering_anisotropy = ${g}
  []

  [snow2]
    type = SnowMaterial
    temperature = T
  []
[]

[Executioner]
  type = Transient
  solve_type = NEWTON
  automatic_scaling = true
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  dt = 300
  end_time = 28800
[]

[Outputs]
  csv = true
  exodus = true
[]
