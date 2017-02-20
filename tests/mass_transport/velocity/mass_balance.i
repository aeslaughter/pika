[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 10
  ny = 10
  nz = 10
  displacements = 'disp_x disp_y disp_z'
[]

[Variables]
  [./density]
    initial_condition = 200
  [../]
[]

[AuxVariables]
  [./velocity_x]
    initial_condition = 0
  [../]
  [./velocity_y]
  [../]
  [./velocity_z]
    initial_condition = 0
  [../]
  [./disp_x]
    initial_condition = 0
  [../]
  [./disp_y]
    initial_condition = 0
  [../]
  [./disp_z]
    initial_condition = 0
  [../]
[]

[AuxKernels]
  [./disp_y]
    type = VelocityDeformation
    variable = disp_y
    velocity = velocity_y
    use_displaced_mesh = true
    execute_on = 'initial timestep_end'
  [../]
[]

[ICs]
  [./vel_y]
    type = FunctionIC
    function = '-0.001*y'
    variable = velocity_y
  [../]
[]

[Kernels]
  [./time]
    type = TimeDerivative
    variable = density
    use_displaced_mesh = true
  [../]
  [./diffusive]
    type = CoupledDiffusion
    variable = density
    velocities = 'velocity_x velocity_y velocity_z'
    use_displaced_mesh = true
  [../]
[]

[Functions]
  [./mass]
    type = ParsedFunction
    vars =  'density volume'
    vals =  'density volume'
    value = 'density*volume'
  [../]
[]

[Postprocessors]
  [./density]
    type = ElementAverageValue
    variable = density
    #use_displaced_mesh = true
    execute_on = 'initial timestep_end'
  [../]
  [./volume]
    type = VolumePostprocessor
    use_displaced_mesh = true
    execute_on = 'initial timestep_end'
  [../]
  [./mass]
    type = FunctionValuePostprocessor
    use_displaced_mesh = true
    function = mass
    execute_on = 'initial timestep_end'
  [../]
[]

[Executioner]
  type = Transient
  end_time = 100
  dt = 10
  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre    boomeramg'
[]

[Outputs]
  exodus = true
[]
