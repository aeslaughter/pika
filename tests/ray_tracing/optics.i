[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 6
  ny = 6
  xmax = 5
  ymax = 5
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
  #active = 'refract_ic'
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
  #active = 'refract_func'
  [./phase_func]
    type = ParsedFunction
    value = 'if(y<2.5,0,1)'
  [../]
  [./refract_func]
    type = ParsedFunction
    value = 'if(y<2.5,1,0.9)'
  [../]
[]

[UserObjects]
  [./study]
    type = OpticRayStudy
    num_rays = 1
    ray_distance = 50
    start_points = '0 0 0'
    start_directions = '1 1 0'
    tolerate_failure=true
  [../]
  [./tracker]
    type = OpticRayTracker
  [../]
[]

[Problem]
  type = OpticRayProblem
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
  [./rays]
    type = OpticRayOutput
    tracker = tracker
    execute_on = 'TIMESTEP_END'
  [../]
[]

[RayKernels]
  [./optics]
    type = OpticRayKernel
    refractive_index = refract
    phase = phase
    tracker = tracker
  [../]
[]

[RayMaterials]
  [./ray]
    type = ConstantRayMaterial
  [../]
[]
