[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 5
  xmax = 5
[]

[AuxVariables]
  [./phase]
  [../]
[]

[UserObjects]
  [./ecr]
    type = OpticRayStudy
  [../]
[]

[Problem]
  type = RayProblem
  num_groups = 1
  study = ecr
[]

[Executioner]
  type = Steady
  kernel_check = false
  solve = false
[]

[Outputs]
  exodus = true
[]

[RayKernels]
  [./optics]
    type = OpticRayKernel
  [../]
[]
