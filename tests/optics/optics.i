[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  uniform_refine = 1
[]

[Variables]
  [radiant_fluence][]
[]

[Kernels]
  [diffusion]
    type = OpticDiffusion
    variable = radiant_fluence
  []
  [absorption]
    type = OpticAbsorption
    variable = radiant_fluence
  []
[]

[BCs]
  [incoming]
    type = OpticDiffuseSourceBC
    variable = radiant_fluence
    boundary = top
    incoming_flux = 100
  []
[]

[Materials]
  [optics]
    type = OpticMaterial
  []
[]

[Executioner]
  type = Steady
[]

[Outputs]
  exodus = true
[]
