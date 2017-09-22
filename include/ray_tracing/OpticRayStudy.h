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

#include "PikaUtils.h"

class OpticRayStudy;

template <>
InputParameters validParams<OpticRayStudy>();

class OpticRayStudy : public RayTracingStudy
{
public:

  OpticRayStudy(const InputParameters & parameters);
  void initialSetup() override;

  bool hasOpticRay();
  void addOpticRay(const Point & origin, const Point & direction,
                  const dof_id_type elem_id, const unsigned int ray_id);

  Point getIntersect(const Point & origin, const Point & direction) const;

protected:
  virtual void generateRays() override;

  std::vector<PikaUtils::NormalPlane> _planes;
  const libMesh::BoundingBox & _bounding_box;

  std::vector<std::shared_ptr<Ray>> _optic_rays;

  unsigned int _id;



};

#endif
