[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 15
  ny = 35
  nz = 15
  xmax = 0.3
  ymax = 0.7
  zmax = 0.3
[]

[Variables]
  [u]
  []
[]

[Kernels]
  [time]
    type = OpticTimeDerivative
    variable = u
    light_speed = 2.29e8
  []
  [diffusion]
    type = OpticDiffusion
    variable = u
  []
  [absoprtion]
    type = OpticAbsorption
    variable = u
  []
[]

[BCs]
  #active = 'top'
  [top]
    type = DirichletBC
    variable = u
    boundary = top
    value = 100
  []
  [bottom]
    type = DirichletBC
    variable = u
    boundary = bottom
    value = 0
  []
[]

[Materials]
  [mat]
    type = GenericFunctionMaterial
    prop_values = '4.2                    19                     0.5'
    prop_names =  'absorption_coefficient scattering_coefficient scattering_anisotropy'
  []
[]

[Executioner]
  type = Transient
  dt = 1e-10
  num_steps = 10
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  execute_on = 'initial timestep_end'
  exodus = true
[]
