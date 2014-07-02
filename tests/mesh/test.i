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

[Problem]
  type = FEProblem
  solve = false
[]

[Executioner]
  type = Steady
[]

[ICs]
  [./bmp]
    variable = u
    type = PikaBinaryIC
    file = input_8bit.bmp
  [../]
[]

[Outputs]
  exodus = true
[]
