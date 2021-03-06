/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "TensorMechanicsHardeningCubic.h"

template<>
InputParameters validParams<TensorMechanicsHardeningCubic>()
{
  InputParameters params = validParams<TensorMechanicsHardeningModel>();
  params.addRequiredParam<Real>("value_0", "The value of the parameter for all internal_parameter <= internal_0");
  params.addParam<Real>("value_residual", "The value of the parameter for internal_parameter >= internal_limit.  Default = value_0, ie perfect plasticity");
  params.addParam<Real>("internal_0", 0, "The value of the internal_parameter when hardening begins");
  params.addParam<Real>("internal_limit", 1, "The value of the internal_parameter when hardening ends.  This hardening forms a cubic between (internal_0, value_0) and (internal_limit, value_residual) that is smooth at internal_0 and internal_limit");
  params.addClassDescription("Hardening is Cubic");
  return params;
}

TensorMechanicsHardeningCubic::TensorMechanicsHardeningCubic(const InputParameters & parameters) :
  TensorMechanicsHardeningModel(parameters),
  _val_0(getParam<Real>("value_0")),
  _val_res(parameters.isParamValid("value_residual") ? getParam<Real>("value_residual") : _val_0),
  _intnl_0(getParam<Real>("internal_0")),
  _intnl_limit(getParam<Real>("internal_limit")),
  _half_intnl_limit(0.5*(_intnl_limit - _intnl_0)),
  _alpha((_val_0 - _val_res)/4.0/std::pow(_half_intnl_limit, 3)),
  _beta(-3.0*_alpha*std::pow(_half_intnl_limit, 2))
{
  if (_intnl_limit <= _intnl_0)
    mooseError("internal_limit must be greater than internal_0 in Cubic Hardening");
}

Real
TensorMechanicsHardeningCubic::value(const Real & intnl) const
{
  Real x = intnl - _intnl_0;
  if (x <= 0)
    return _val_0;
  else if (intnl >= _intnl_limit)
    return _val_res;
  else
    return _alpha*std::pow(x - _half_intnl_limit, 3) + _beta*(x - _half_intnl_limit) + 0.5*(_val_0 + _val_res);
}

Real
TensorMechanicsHardeningCubic::derivative(const Real & intnl) const
{
  Real x = intnl - _intnl_0;
  if (x <= 0)
    return 0;
  else if (intnl >= _intnl_limit)
    return 0;
  else
    return 3*_alpha*std::pow(x - _half_intnl_limit, 2) + _beta;
}

std::string
TensorMechanicsHardeningCubic::modelName() const
{
  return "Cubic";
}
