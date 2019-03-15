[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
  uniform_refine = 4
[]

[Variables]
  [radiant_fluence][]
[]

[Kernels]
  [diffusion]
    type = OpticDiffusion
    variable = radiant_fluence
    diffusion_coefficient = 1
  []
  [absorption]
    type = OpticAbsorption
    variable = radiant_fluence
    absorption_coefficient = 1
  []
[]



[BCs]
  #active = 'arbree arbree_other'
  #active = 'arbree'
  #active = 'neumann'
  active = 'dirichlet'
  [arbree]
    type = OpticDiffuseSourceBC
    variable = radiant_fluence
    boundary = top
    incoming_flux = 100
  []
  [arbree_other]
    type = OpticDiffuseSourceBC
    variable = radiant_fluence
    boundary = 'left right bottom'
    incoming_flux = 0
  []

  [dirichlet]
    type = DirichletBC
    variable = radiant_fluence
    boundary = left
    value = 100
  []

  [neumann]
    type = ADNeumannBC
    variable = radiant_fluence
    boundary = top
    value = 100
  []
[]

[Postprocessors]
  active = ''
  [top_flux]
    type = SideFluxAverage
    boundary = left
    variable = radiant_fluence
    diffusivity = optic_diffusion_coefficient
  []
  [bottom_flux]
    type = SideFluxAverage
    boundary = right
    variable = radiant_fluence
    diffusivity = optic_diffusion_coefficient
  []
[]

[VectorPostprocessors]
  [line]
    type = LineValueSampler
    start_point = '1 0 0'
    end_point = '0 0 0'
    num_points = 100
    variable = radiant_fluence
    sort_by = x
  []
[]

[Materials]
  active = ''
  [optics]
    type = OpticMaterial
    optic_scattering = 94
    optic_absorption = 40
    optic_anisotropy = 1
  []
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
[]

[Outputs]
  exodus = true
  csv = true
[]
