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

#ifndef PIKAUTILS_H
#define PIKAUTILS_H

// libMesh includes
#include "libmesh/point.h"
#include "libmesh/plane.h"


namespace PikaUtils
{

/**
 * Plane defined by a point and a normal.
 *
 * This adds a normal() method that does not require a point, simply to make the
 * code using this class more intuitive.
 */
class Plane: public libMesh::Plane
{
public:

  /**
   * Construct a plane given a point and normal direction.
   *
   * @param p Point on the plane.
   * @param n Outward normal from the plane.
   */ 
  Plane(const libMesh::Point & p, const libMesh::Point & n);

  /**
   * Return the outward normal from the plane.
   */ 
  libMesh::Point normal() const;

private:

  /// Dummy Point for calling need for calling the base class normal method.
  libMesh::Point _zero;
};



/**
 * Function for returning the intersction point of a vector on a plane.
 * @param origin The ray origin.
 * @param direction The ray direction vector.
 * @param plane The plan of interest.
 *
 * If the ray doesn't intersect the plane, then a INVALID_POINT is returned.
 */
libMesh::Point get_intersect(const libMesh::Point & origin, const libMesh::Point & direction, const Plane & plane);


} // PikaUtils

#endif 
