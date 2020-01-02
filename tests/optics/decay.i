depth = 0.25
kappa = 40
alpha = 0.94
q_in = 100
g = 0

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
    #diffusion_coefficient = 0.014433756729740631
  []
  [absorption]
    type = OpticAbsorption
    variable = u
    #absorption_coefficient = 23.09401076758505
  []
[]

[BCs]
  [source]
    type = DirichletBC
    variable = u
    boundary = left
    value = ${q_in}
  []
[]

[Postprocessors]
  [h]
    type = AverageElementSize
  []
  [error]
    type = NodalL2Error
    function = '${q_in}*exp(-${kappa}*x)'
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

[Materials]
  [snow]
    type = SnowOpticMaterial
    effective_attenuation_coefficient = ${kappa}
    single_scattering_albedo = ${alpha}
    scattering_anisotropy = ${g}
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
