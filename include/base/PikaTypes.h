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

#ifndef PIKATYPES_H
#define PIKATYPES_H

// Forward declare
namespace libMesh{ class Point; }

namespace PikaTypes
{
/// An invalid Point, this is used when locating intersections that might not exist
extern const libMesh::Point INVALID_POINT;
}

#endif
