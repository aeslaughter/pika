kappa0 = 10
kappa1 = 60
alpha0 = 0.94
alpha1 = -0.2
q_in = 50
g = 0

[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 10
  ny = 10
  nz = 7
  xmax = 1
  zmax = 1
  ymin = -0.7
  ymax = 0
[]

[Adaptivity]
  initial_marker = top
  max_h_level = 2
  initial_steps = 2
  [Markers]
    [top]
      type = BoxMarker
      bottom_left = '0 -0.2 0'
      top_right = '1 0 1'
      inside = refine
      outside = coarsen
    []
  []
[]

[Variables]
 [u][]
 [T][]
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
    value = 174
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

[Materials]
  [snow]
    type = GenericFunctionMaterial
    prop_names =  'density effective_attenuation_coefficient single_scattering_albedo'
    prop_values = 'density kappa                             alpha'
    outputs = out
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
  [out]
    type = Exodus
    elemental_as_nodal = true
  []
[]
