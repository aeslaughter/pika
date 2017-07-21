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

// Pika includes
#include "PikaTypes.h"

// libMesh includes
#include "libmesh/libmesh_common.h"
#include "libmesh/point.h"

namespace PikaTypes
{
const libMesh::Real min_real = std::numeric_limits<libMesh::Real>::min();
const libMesh::Point INVALID_POINT = libMesh::Point(min_real, min_real, min_real);
}

