[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 85
  ny = 85
  uniform_refine = 2
[]

[Variables]
  [./u]
  [../]
[]

[Kernels]
  [./u_time]
    type = PikaTimeDerivative
    variable = u
    property = tau
  [../]
  [./u_diff]
    type = ACInterface
    variable = u
    mob_name = mobility
    kappa_name = interface_thickness_squared
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 10
[]

[Adaptivity]
  max_h_level = 2
  initial_steps = 2
  marker = marker
  initial_marker = marker
  [./Indicators]
    [./indicator]
      type = GradientJumpIndicator
      variable = u
    [../]
  [../]
  [./Markers]
    [./marker]
      type = ErrorFractionMarker
      coarsen = 0.7
      indicator = indicator
      refine = 0.3
    [../]
  [../]
[]

[ICs]
  [./bmp]
    variable = u
    type = PikaBinaryIC
    file = input_8bit.bmp
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
[]

[PikaMaterials]
  phi = u
  temperature = 270
[]
