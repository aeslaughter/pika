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

#ifndef BINARYIMAGEFUNCTION_H
#define BINARYIMAGEFUNCTION_H

#include "libmesh/mesh.h"
#include "libmesh/mesh_generation.h"
#include "libmesh/mesh_function.h"
#include "libmesh/numeric_vector.h"


// MOOSE includes

#include "Function.h"

// Forward declerations
class BinaryImageFunction;

template<>
InputParameters validParams<BinaryImageFunction>();

/**
 *
 */
class BinaryImageFunction : public Function
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  BinaryImageFunction(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~BinaryImageFunction();

  Real value(Real t, const Point & p);


private:
  void readImage();
 std::string _file_name;

  Mesh * _image_mesh_ptr;

  EquationSystems * _image_es_ptr;

  MeshFunction * _image_mesh_function;

  AutoPtr<NumericVector<Number> > _serialized_solution;

};

#endif //BINARYIMAGEFUNCTION_H
