[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
[]

[Variables]
  [./u]
  [../]
[]

[Kernels]
  [./diff]
    type = PhotonDiffusion
    speed_of_light = 2.28e8
    absorption_coefficient = 0.011
    scattering_coefficient = 0.55
    average_of_cosine_phase_function = 0
    variable = u
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = bottom
    value = 0
  [../]
  [./right]
    type = NeumannBC
    variable = u
    boundary = top
    value = 100
  [../]
[]

[Executioner]
  type = Steady
  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
[]
