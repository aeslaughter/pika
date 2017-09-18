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

#ifndef OpticRayTracker_H
#define OpticRayTracker_H

#include "GeneralUserObject.h"

#include "PikaUtils.h"

class OpticRayTracker;

template <>
InputParameters validParams<OpticRayTracker>();

class OpticRayTracker : public GeneralUserObject
{
public:
  OpticRayTracker(const InputParameters & parameters);
  virtual void initialize() override final {}
  virtual void finalize() override final {}
  virtual void execute() override final {}
  virtual void initialSetup() override;
  virtual void timestepSetup() override;

  void addSegment(const Point & start, const Point & end, unsigned int id);

  const std::map<unsigned int, std::vector<std::pair<Point, Point>>> & getSegments() const;
  std::size_t numSegments() const { return _segments.size(); }

protected:

  // TODO: Make this parallel/threaded
  std::map<unsigned int, std::vector<std::pair<Point, Point>>> _segments;

};

#endif
