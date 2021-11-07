#include "PyBindIncludes.h"

#include "NGLInit.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitNGLInit(py::module & m)
  {
    py::class_<NGLInit, std::unique_ptr<NGLInit, py::nodelete>>(m, "NGLInit")
        .def("setCommunicationMode",&NGLInit::setCommunicationMode)
        .def_static("initialize",&NGLInit::initialize);

    py::enum_<CommunicationMode>(m, "CommunicationMode")
           .value("NULLCONSUMER",CommunicationMode::NULLCONSUMER )
           .value("STDOUT",CommunicationMode::STDOUT )
           .value("STDERR",CommunicationMode::STDERR )
           .value("FILE",CommunicationMode::FILE );

  }

}
