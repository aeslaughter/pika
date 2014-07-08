[Mesh]
  type = PikaMesh
  image = input_8bit_80x80.png
  dim = 2
  width = 0.005
  height = 0.005
  variable = u
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
