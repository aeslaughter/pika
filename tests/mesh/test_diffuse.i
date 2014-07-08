[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  uniform_refine = 3
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
  [./u_doublewell]
    type = DoubleWellPotential
    variable = u
    mob_name = mobility
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 1
[]

[ICs]
  [./bmp]
    variable = u
    type = PikaBinaryIC
    file = input_8bit_80x80.png
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

