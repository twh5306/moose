[Mesh]
  type = GeneratedMesh
  dim = 2

  nx = 10
  ny = 100

  xmin = 0.0
  xmax = 1.0

  ymin = 0.0
  ymax = 10.0

  [./Partitioner]
    type = LibmeshPartitioner
    partitioner = linear
  [../]
  distribution = serial
[]


[Variables]
  active = 'u'

  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./proc_id]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  active = 'diff'

  [./diff]
    type = Diffusion
    variable = u
  [../]
[]

[AuxKernels]
  [./proc_id]
    type = ProcessorIDAux
    variable = proc_id
  [../]
[]

[BCs]
  active = 'left right'

  [./left]
    type = DirichletBC
    variable = u
    boundary = 3
    value = 0
  [../]

  [./right]
    type = DirichletBC
    variable = u
    boundary = 1
    value = 1
  [../]
[]

[Executioner]
  type = Steady

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'
[]

[Outputs]
  file_base = custom_linear_partitioner_test_out
  [./exodus]
    type = Exodus
    elemental_as_nodal = true
  [../]
[]
