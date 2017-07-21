[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 5
  xmax = 5
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./refract]
  [../]
[]

[ICs]
  [./phase]
    type = FunctionIC
    function = phase_ic
    variable = refract
  [../]
[]

[Functions]
  [./phase_ic]
    type = ParsedFunction
    value = 'if(x<2.5,0.3,0.2)'
  [../]
[]

[UserObjects]
  [./ecr]
    type = OpticRayStudy
    num_rays = 1
    ray_distance = 1
    start_points = '0, 0.5, 0.5'
    start_directions = '1 0 0'
  [../]
[]

[Problem]
  type = RayProblem
  kernel_coverage_check = false
  num_groups = 1
  study = ecr
  solve = false
[]

[Executioner]
  type = Steady
[]

[Outputs]
  exodus = true
[]

[RayKernels]
  [./optics]
    type = OpticRayKernel
    refractive_index = refract
  [../]
[]

[RayMaterials]
  [./ray]
    type = ConstantRayMaterial
  [../]
[]