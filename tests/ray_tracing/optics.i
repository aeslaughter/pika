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
  [./phase]
  [../]
  [./refract]
  [../]
[]

[ICs]
  active = 'refract_ic'
  [./phase_ic]
    type = FunctionIC
    function = phase_func
    variable = phase
  [../]
  [./refract_ic]
    type = FunctionIC
    function = refract_func
    variable = refract
  [../]
[]

[Functions]
  active = 'refract_func'
  [./phase_func]
    type = ParsedFunction
    value = 'if(x<2.5,0,1)'
  [../]
  [./refract_func]
    type = ParsedFunction
    value = 'if(x<2.5,1.0,1.3)'
  [../]
[]

[UserObjects]
  [./study]
    type = OpticRayStudy
    num_rays = 1
    ray_distance = 5
    start_points = '0, 0.5, 0'
    start_directions = '1 0.05 0'
  [../]
[]

[Problem]
  type = RayProblem
  kernel_coverage_check = false
  num_groups = 1
  study = study
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
  #  phase = phase
  [../]
[]

[RayMaterials]
  [./ray]
    type = ConstantRayMaterial
  [../]
[]
