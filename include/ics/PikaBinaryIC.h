#ifndef PIKABINARYIC_H
#define PIKABINARYIC_H

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

  virtual ~PikaBinaryIC(){};

  virtual void initialSetup();

protected:

  /**
   * The value of the variable at a point.
   *
   * This must be overridden by derived classes.
   */
  virtual Real value(const Point & p);

private:
  void readImage(std::string file);

  std::map<dof_id_type, int> _centroid_map;

  std::string _file_name;
};

#endif // PIKABINARYIC_H
