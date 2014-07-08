#ifndef PIKABINARYIC_H
#define PIKABINARYIC_H

#include "libmesh/mesh.h"
#include "libmesh/mesh_generation.h"
#include "libmesh/mesh_function.h"
#include "libmesh/numeric_vector.h"



// MOOSE includes
#include "InitialCondition.h"

//Forward Declarations
class PikaBinaryIC;

template<>
InputParameters validParams<PikaBinaryIC>();

class PikaBinaryIC :
  public InitialCondition
{
public:
  PikaBinaryIC(const std::string & name, InputParameters parameters);

  virtual ~PikaBinaryIC();

  virtual void initialSetup();

protected:

  /**
   * The value of the variable at a point.
   *
   * This must be overridden by derived classes.
   */
  virtual Real value(const Point & p);

private:
  void readImage();

  std::map<dof_id_type, double> _centroid_map;

  std::string _file_name;

  Mesh * _image_mesh_ptr;

  EquationSystems * _image_es_ptr;

  MeshFunction * _image_mesh_function;

};

#endif // PIKABINARYIC_H
