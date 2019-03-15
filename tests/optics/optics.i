[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  #ymax = 1
  #xmax = 1
  uniform_refine = 3
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
  #active = 'arbree arbree_other'
  active = 'neumann'
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

  [neumann]
    type = ADNeumannBC
    variable = radiant_fluence
    boundary = top
    value = 100
  []
[]

[Postprocessors]
  [top_flux]
    type = SideFluxAverage
    boundary = top
    variable = radiant_fluence
    diffusivity = optic_diffusion_coefficient
  []
  [bottom_flux]
    type = SideFluxAverage
    boundary = bottom
    variable = radiant_fluence
    diffusivity = optic_diffusion_coefficient
  []
[]

[VectorPostprocessors]
  [line]
    type = LineValueSampler
    start_point = '0.5 1 0'
    end_point = '0.5 0 0'
    num_points = 100
    variable = radiant_fluence
    sort_by = y
  []
[]

[Materials]
  [optics]
    type = OpticMaterial
    optic_scattering = 190
    optic_absorption = 0.5
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
