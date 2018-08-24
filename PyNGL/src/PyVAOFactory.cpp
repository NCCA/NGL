#include <pybind11/pybind11.h>

#include "VAOFactory.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitVAOFactory(py::module & m)
  {
    py::class_<VAOFactory>(m, "VAOFactory")
      .def_static("registerVAOCreator",&VAOFactory::registerVAOCreator)
      .def_static("unregisterVAOCreator",&VAOFactory::unregisterVAOCreator)
      .def_static("createVAO",&VAOFactory::createVAO)
      .def_static("listCreators",&VAOFactory::listCreators)
        ;

  }

}
