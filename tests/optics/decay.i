[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 8
  xmax = 2
[]

[Variables]
  [u][]
[]

[Kernels]
  [diffusion]
    type = OpticDiffusion
    variable = u
    diffusion_coefficient = 1
  []
  [absorption]
    type = OpticAbsorption
    variable = u
    absorption_coefficient = 1
  []
[]

[BCs]
  #active = 'dirichlet'
  active = 'dirichlet dirichlet2'
  #active = 'dirichlet griffiths'
  #active = 'dirichlet arbree_out'
  #active = 'arbree_in arbree_out'
  #active = 'arbree_in'
  [dirichlet]
    type = DirichletBC
    variable = u
    boundary = left
    value = 1
  []
  [dirichlet2]
    type = DirichletBC
    variable = u
    boundary = right
    value = 0.135335
  []

  [griffiths]
    type = OpticGriffithsBC
    variable = u
    boundary = right
    diffusion_coefficient = 1
  []
  [arbree_in]
    type = OpticDiffuseSourceBC
    variable = u
    boundary = left
    incoming_flux = 0.5
  []
  [arbree_out]
    type = OpticDiffuseSourceBC
    variable = u
    boundary = right
    incoming_flux = 0
  []
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Postprocessors]
  [h]
    type = AverageElementSize
  []
  [dofs]
    type = NumDOFs
  []
  [error]
    type = NodalL2Error
    function = exp(-x)
    variable = u
  []
[]

[Materials]
  active = ''
  [optics]
    type = OpticMaterial
    optic_scattering = .94
    optic_absorption = .40
    optic_anisotropy = 1
  []
[]

[VectorPostprocessors]
  [line]
    type = LineValueSampler
    start_point = '2 0 0'
    end_point = '0 0 0'
    num_points = 100
    variable = u
    sort_by = x
  []
[]


[Executioner]
  type = Transient
  solve_type = NEWTON
  num_steps = 5
[]

[Adaptivity]
  marker = marker
  [Markers/marker]
      type = UniformMarker
      mark = refine
  []
[]

[Outputs]
  [out]
    type = CSV
    execute_on = 'timestep_end'
  []
[]
