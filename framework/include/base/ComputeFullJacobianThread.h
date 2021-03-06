/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef COMPUTEFULLJACOBIANTHREAD_H
#define COMPUTEFULLJACOBIANTHREAD_H

#include "ComputeJacobianThread.h"

// Forward declarations
class FEProblem;
class NonlinearSystem;

class ComputeFullJacobianThread : public ComputeJacobianThread
{
public:
  ComputeFullJacobianThread(FEProblem & fe_problem, NonlinearSystem & sys, SparseMatrix<Number> & jacobian);

  // Splitting Constructor
  ComputeFullJacobianThread(ComputeFullJacobianThread & x, Threads::split split);

  virtual ~ComputeFullJacobianThread();

  void join(const ComputeJacobianThread & /*y*/)
  {}


protected:
  virtual void computeJacobian();
  virtual void computeFaceJacobian(BoundaryID bnd_id);
  virtual void computeInternalFaceJacobian(const Elem * neighbor);
  virtual void computeInternalInterFaceJacobian(BoundaryID bnd_id);

  // Reference to BC storage structures
  const MooseObjectWarehouse<IntegratedBC> & _integrated_bcs;

  // Reference to DGKernel storage
  const MooseObjectWarehouse<DGKernel> & _dg_kernels;

  // Reference to interface kernel storage
  const MooseObjectWarehouse<InterfaceKernel> & _interface_kernels;

  // Reference to Kernel storage
  const KernelWarehouse & _kernels;
};

#endif //COMPUTEFULLJACOBIANTHREAD_H
