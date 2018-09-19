[Mesh]
  type = GeneratedMesh
  dim = 2
  ymax = 0
  ymin = -10
  nx = 10
  ny = 100
[]

[Variables]
  [./u]
  [../]
[]

[Kernels]
  inactive = time
  [./time]
    type = TimeDerivative
    variable = u
  [../]
  [./diff]
    type = PhotonDiffusion
    variable = u
  [../]
  [./force]
    type = PhotonForcing
    variable = u
  [../]
[]

[ICs]
  inactive = 'top'
  [./top]
    type = ConstantIC
    value = 1
    boundary = top
    variable = u
  [../]
[]

[BCs]
  inactive = 'bottom'
  [./top]
    type = NeumannBC
    variable = u
    boundary = top
    value = 10000
  [../]
  [./bottom_flux]
    type = PhotonBC
    variable = u
    boundary = 'left right bottom'
  [../]
  [./bottom]
    type = DirichletBC
    value = 0
    variable = u
    boundary = bottom
  [../]
[]

[VectorPostprocessors]
  [./vertical]
    type = LineValueSampler
    num_points = 100
    start_point = '0.5 0 0'
    end_point = '0.5 -10 0'
    variable = u
    sort_by = 'y'
   [../]
[]

[Materials]
  [./constant]
    type = GenericConstantMaterial
    prop_names =  'speed_of_light absorption_coefficient scattering_coefficient average_of_cosine_phase_function'
    prop_values = '2.28e8         0.011                  0.55                   1'
  [../]
[]

[Executioner]
  type = Steady
  #type = Transient
  #num_steps = 100
  #dt = 1e-10
  #steady_state_detection = True
  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
  csv = true
[]
