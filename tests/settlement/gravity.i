[Mesh]
  type = GeneratedMesh
  dim = 3
  displacements = 'disp_x disp_y disp_z'
[]

[Variables]
  [./disp_x]
    order = FIRST
    family = LAGRANGE
  [../]
  [./disp_y]
    order = FIRST
    family = LAGRANGE
  [../]
  [./disp_z]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./stress_yy]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./stress_aux]
    type = RankTwoAux
    rank_two_tensor = stress
    index_i = 1
    index_j = 1
    variable = stress_yy
    execute_on = 'timestep_end'
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
[]

[BCs]
  [./no_x]
    type = DirichletBC
    variable = disp_x
    boundary = bottom
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
    boundary = bottom
    value = 0.0
  [../]
[]

[Materials]
  [./elasticity_tensor]
    type = ComputeIsotropicElasticityTensor
    youngs_modulus = 200e6
    poissons_ratio = 0.3
  [../]
  [./strain]
    type = ComputeSmallStrain
    block = 0
    displacements = 'disp_x disp_y disp_z'
  [../]
  [./stress]
    type = ComputeLinearElasticStress
    block = 0
  [../]
  [./density]
    type = GenericConstantMaterial
    block = 0
    prop_names = density
    prop_values = 8050
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Steady
  solve_type = PJFNK
  nl_abs_tol = 1e-10
  l_max_its = 20
[]

[Outputs]
  [./out]
    type = Exodus
    elemental_as_nodal = true
  [../]
[]
