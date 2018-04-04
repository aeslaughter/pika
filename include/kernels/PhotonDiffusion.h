#ifndef PHOTONDIFFUSION_H
#define PHOTONDIFFUSION_H

// MOOSE includes
#include "Diffusion.h"

// Pika includes
#include "PropertyUserObjectInterface.h"
#include "CoefficientKernelInterface.h"

//Forward Declarations
class PhotonDiffusion;

template<>
InputParameters validParams<PhotonDiffusion>();

/**
 * A photon transport diffusion kernel.
 * (see Arridge et al, 1993)
 */
class PhotonDiffusion :
  public Diffusion
{
public:
  PhotonDiffusion(const InputParameters & parameters);

  static Real kappa(const Real & c, const Real & mu_a, const Real & mu_s, const Real & f);

protected:

  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _speed_of_light;
  const MaterialProperty<Real> & _absoprtion_coefficient;
  const MaterialProperty<Real> & _scattering_coefficient;
  const MaterialProperty<Real> & _average_of_cosine_phase_function;

};

#endif
