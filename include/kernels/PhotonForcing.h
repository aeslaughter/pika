#ifndef PHOTONFORCING_H
#define PHOTONFORCING_H

// MOOSE includes
#include "Kernel.h"

//Forward Declarations
class PhotonForcing;

template<>
InputParameters validParams<PhotonForcing>();

/**
 * A photon transport forcing kernel.
 * (see Arridge et al, 1993)
 */
class PhotonForcing : public Kernel
{
public:
  PhotonForcing(const InputParameters & parameters);


protected:

  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _speed_of_light;
  const MaterialProperty<Real> & _absoprtion_coefficient;
};

#endif
