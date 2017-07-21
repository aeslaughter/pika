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

template <>
InputParameters validParams<OpticRayStudy>();

class OpticRayStudy : public RayTracingStudy
{
public:
  OpticRayStudy(const InputParameters & parameters);
//  void initialSetup() override;

  void addOpticRay(const Point & origin, const Point & direction);

  
protected:
  virtual void generateRays() override;


  
  std::vector<Point> _start_points;
  std::vector<Point> _start_directions;
};

#endif
