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

#ifndef PHOTONBC_H
#define PHOTONBC_H

// MOOSE includes
#include "IntegratedBC.h"

// Forward declarations
class PhotonBC;

template<>
InputParameters validParams<PhotonBC>();

class PhotonBC : public IntegratedBC
{
public:
  PhotonBC(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  const MaterialProperty<Real> & _speed_of_light;
  const MaterialProperty<Real> & _absoprtion_coefficient;
  const MaterialProperty<Real> & _scattering_coefficient;
  const MaterialProperty<Real> & _average_of_cosine_phase_function;

};

#endif //IBEXSURFACEFLUXBC_H
