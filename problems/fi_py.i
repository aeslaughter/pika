[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 20
  ny = 20
  xmax = 0.5
  ymax = 0.5
[]

[Variables]
  [./phi]
  [../]
  [./dT]
    initial_condition = -0.5
  [../]
[]

[Kernels]
  [./heat_time]
    type = TimeDerivative
    variable = dT
  [../]
  [./heat_diff]
    type = MatDiffusion
    variable = dT
    D_name = D_T
  [../]
  [./heat_phi_time]
    type = TimeDerivative
    variable = phi
  [../]
  [./phi_time]
    type = PikaTimeDerivative
    variable = phi
    property = tau
  [../]
  [./phi_diff]
    type = TensorDiffusion
    variable = phi
    mobility_tensor = D
  [../]
[]

[Materials]
  [./modal_a]
    type = ModelAMaterial
    block = 0
    dimensionless_undercooling_variable = dT
    phase_field_variable = phi
  [../]
[]

[ICs]
  [./phi_ic]
    x1 = 0.25
    y1 = 0.25
    radius = 0.125
    outvalue = 0
    variable = phi
    invalue = 1
    type = SmoothCircleIC
  [../]
[]

