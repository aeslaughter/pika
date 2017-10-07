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

#include "OpticRayOutput.h"
#include "OpticRayTracker.h"

#include "libmesh/explicit_system.h"

template <>
InputParameters
validParams<OpticRayOutput>()
{
  InputParameters params = validParams<Output>();
  params.addRequiredParam<UserObjectName>("tracker", "OpticRayTracker object for output (optional).");
  params.addParam<std::string>("file_base",
                             "The desired solution output name without an extension");
  return params;
}

OpticRayOutput::OpticRayOutput(const InputParameters & params) :
Output(params),
UserObjectInterface(this),
_output_mesh(libmesh_make_unique<ReplicatedMesh>(_communicator, 3)),
_output_equation_systems(libmesh_make_unique<EquationSystems>(*(_output_mesh))),
_exodus_io_ptr(libmesh_make_unique<ExodusII_IO>(*_output_mesh)),
_tracker(getUserObject<OpticRayTracker>("tracker"))
{
  _output_equation_systems->add_system<ExplicitSystem>("optics");
}

void
OpticRayOutput::output(const ExecFlagType & type)
{
  //TODO: Error if not segments

  std::cout << "COUNT: " << _tracker.numSegments() << std::endl;

  const std::map<unsigned int, std::vector<std::pair<Point, Point>>> & segments = _tracker.getSegments();

  for (auto & pair : segments)
  {
    for (const std::pair<Point, Point> & points : pair.second)
    {
      std::unique_ptr<Node> node0 = libmesh_make_unique<Node>(points.first);
      std::unique_ptr<Node> node1 = libmesh_make_unique<Node>(points.second);
      Node * n0 = _output_mesh->add_node(node0.release());
      Node * n1 = _output_mesh->add_node(node1.release());

      std::unique_ptr<Elem> elem = Elem::build(ElemType::EDGE2);
      elem->set_node(0) = n0;
      elem->set_node(1) = n1;

      _output_mesh->add_elem(elem.release());

    }
  }

  _output_mesh->prepare_for_use();
  _output_mesh->print_info();

  _output_equation_systems->init();

//  std::unique_ptr<ExodusII_IO> exodus_io_ptr = libmesh_make_unique<ExodusII_IO>(*_output_mesh);
  _exodus_io_ptr->write_timestep(filename(), *_output_equation_systems, timeStep(), time());


}

std::string
OpticRayOutput::filename()
{
  return "ray_out.e";
}
