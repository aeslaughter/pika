[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 8
  xmax = 10
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
  [dirichlet]
    type = DirichletBC
    variable = u
    boundary = left
    value = 1
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
