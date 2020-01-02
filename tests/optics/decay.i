depth = 0.25

[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 8
  xmax = ${depth}
  uniform_refine=4
[]

[Variables]
  [u][]
[]

[Kernels]
  [diffusion]
    type = OpticDiffusion
    variable = u
    diffusion_coefficient = 0.014433756729740631
  []
  [absorption]
    type = OpticAbsorption
    variable = u
    absorption_coefficient = 23.09401076758505
  []
[]

[BCs]
  active = 'dirichlet'
  #active = 'dirichlet dirichlet2'
  #active = 'dirichlet griffiths'
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
    diffusion_coefficient = 0.014433756729740631
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
    function = exp(-40*x)
    variable = u
  []
[]

[VectorPostprocessors]
  [line]
    type = LineValueSampler
    start_point = '${depth} 0 0'
    end_point = '0 0 0'
    num_points = 100
    variable = u
    sort_by = x
  []
[]


[Executioner]
  type = Steady
  solve_type = NEWTON
  automatic_scaling = true
[]

[Outputs]
  [out]
    type = CSV
    execute_on = 'timestep_end'
  []
[]
