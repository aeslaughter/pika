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


#include "Output.h"
#include "UserObjectInterface.h"

#include "libmesh/replicated_mesh.h"
#include "libmesh/exodusII_io.h"

class OpticRayOutput;
class OpticRayTracker;

template<>
InputParameters
validParams<OpticRayOutput>();

class OpticRayOutput : public Output, public UserObjectInterface
{
public:
  OpticRayOutput(const InputParameters & params);
  virtual void output(const ExecFlagType & type);

protected:
  std::unique_ptr<ReplicatedMesh> _output_mesh;
  std::unique_ptr<EquationSystems> _output_equation_systems;
  std::unique_ptr<ExodusII_IO> _exodus_io_ptr;
  const OpticRayTracker & _tracker;

};
