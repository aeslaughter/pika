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

#ifndef OPTICRAYSTUDY_H
#define OPTICRAYSTUDY_H

#include "RayTracingStudy.h"

class OpticRayStudy;
namespace PikaUtils{class NormalPlane;}

template <>
InputParameters validParams<OpticRayStudy>();

class OpticRayStudy : public RayTracingStudy
{
public:
  OpticRayStudy(const InputParameters & parameters);
  void initialSetup() override;
  void addOpticRay(const Point & origin, const Point & direction);

  Point getIntersect(const Point & origin, const Point & direction) const;

protected:
  virtual void generateRays() override;

  std::vector<PikaUtils::NormalPlane> _planes;
  std::vector<Point> _start_points;
  std::vector<Point> _start_directions;
  const libMesh::BoundingBox & _bounding_box;

  unsigned int _id;
};

#endif
