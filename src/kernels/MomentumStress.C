
#include "RankTwoTensor.h"
#include "MomentumStress.h"

template<>
InputParameters validParams<MomentumStress>()
{
  MooseEnum component("x=0 y=1 z=2");
  InputParameters params = validParams<Kernel>();
  params.addParam<MaterialPropertyName>("stress", "stress", "The stress tensor property name.");
  params.addRequiredParam<MooseEnum>("component", component, "The component to consider.");
  return params;
}

MomentumStress::MomentumStress(const InputParameters & parameters) :
    Kernel(parameters),
    _stress(getMaterialProperty<RankTwoTensor>("stress")),
    _component(getParam<MooseEnum>("component"))
{
}

Real
MomentumStress::computeQpResidual()
{
  return _grad_test[_i][_qp] * _stress[_qp].row(_component);
}

Real
MomentumStress::computeQpJacobian()
{
  return 0;
}
