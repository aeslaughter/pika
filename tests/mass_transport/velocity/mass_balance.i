[GlobalParams]
  displacements = 'disp_x disp_y disp_z'
  use_displaced_mesh = true
[]

[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 10
  ny = 10
  nz = 10
[]

[Variables]
  [./density]
    initial_condition = 200
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

[AuxVariables]
  [./velocity_x]
    initial_condition = 0
  [../]
  [./velocity_y]
  [../]
  [./velocity_z]
    initial_condition = 0
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
  [./TensorMechanics]
    displacements = 'disp_x disp_y disp_z'
  [../]
  [./gravity_y]
    type = Gravity
    variable = disp_y
    value = -9.81
  [../]
  [./time]
    type = CoefficientMaterialDerivative
    variable = density
    velocities = 'velocity_x velocity_y velocity_z'
  [../]
  [./diffusive]
    type = MassBalanceDivergence
    variable = density
    velocities = 'velocity_x velocity_y velocity_z'
  [../]
[]

[BCs]
[./no_x]
  type = DirichletBC
  variable = disp_x
  boundary = left
  value = 0.0
[../]
[./no_y]
  type = DirichletBC
  variable = disp_y
  boundary = bottom
  value = 0.0
[../]
[./no_z]
  type = DirichletBC
  variable = disp_z
  boundary = front
  value = 0.0
[../]
[]

[Materials]
  [./snow]
    type = IbexSnowMaterial
    density = density
    temperature = 263.15
  [../]
  [./Elasticity_tensor]
    type = ComputeElasticityTensor
    fill_method = symmetric_isotropic
    C_ijkl = '0 0.5e6'
  [../]
  [./strain]
    type = ComputeFiniteStrain
    displacements = 'disp_x disp_y disp_z'
  [../]
  [./stress]
    type = ComputeFiniteStrainElasticStress
  [../]


#  [./stress]
#    type = ComputeIsotropicViscousStress
#    velocities = 'velocity_x velocity_y velocity_z'
#  [../]
[]

[Postprocessors]
  [./mass]
    type = Mass
    variable = density
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
