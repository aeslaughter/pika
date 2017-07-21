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

// libMesh includes
#include "libmesh/point.h"
#include "libmesh/plane.h"


namespace PikaUtils
{

class Ray
{
public:
  Ray(const libMesh::Point & origin, const libMesh::Point & direction);

  const libMesh::Point & getOrigin() const { return _origin; }
  const libMesh::Point & getDirection() const { return _direction; }
  
protected:
  const libMesh::Point _origin;
  
  const libMesh::Point _direction;
  
};

Ray::Ray(const libMesh::Point & origin, const libMesh::Point & direction) :
    _origin(origin),
    _direction(direction.unit())
{
}


} // PikaUtils
 
