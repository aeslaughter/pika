/**********************************************************************************/
/*                  Pika: Phase field snow micro-structure model                  */
/*                                                                                */
/*                     (C) 2014 Battelle Energy Alliance, LLC                     */
/*                              ALL RIGHTS RESERVED                               */
/*                                                                                */
/*                   Prepared by Battelle Energy Alliance, LLC                    */
/*                      Under Contract No. DE-AC07-05ID14517                      */
/*                      With the U. S. Department of Energy                       */
/**********************************************************************************/

#include "OpticGriffithsBC.h"

registerMooseObject("PikaApp", OpticGriffithsBC);

InputParameters
OpticGriffithsBC::validParams()
{
    InputParameters params = ADIntegratedBC::validParams();
  params.addParam<MaterialPropertyName>("diffusion_coefficient", "optic_diffusion_coefficient",
                                        "The diffusion coefficient (D) name for the radiative transfer equation with a diffusion approximation.");

return params;
}

OpticGriffithsBC::OpticGriffithsBC(const InputParameters & parameters) :
    ADIntegratedBC(parameters),
    _diffusion_coef(getADMaterialProperty<Real>("diffusion_coefficient"))
{
}

ADReal
OpticGriffithsBC::computeQpResidual()
{
  return - _test[_i][_qp] * _diffusion_coef[_qp] * _grad_u[_qp] * _normals[_qp];
}
