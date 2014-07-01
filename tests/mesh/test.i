[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 340
  ny = 340
  uniform_refine = 0
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
    file = input.bmp
  [../]
[]

[Outputs]
  exodus = true
[]
