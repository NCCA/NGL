#include <pybind11/pybind11.h>

#include "VAOPrimitives.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitVAOPrimitives(py::module & m)
  {
    py::class_<VAOPrimitives, std::unique_ptr<VAOPrimitives, py::nodelete>>(m, "VAOPrimitives")
        .def_static("instance",VAOPrimitives::instance)
        .def("draw", (void (VAOPrimitives::*)(const std::string_view &))&VAOPrimitives::draw)
        .def("draw", (void (VAOPrimitives::*)(const std::string_view &, GLenum))&VAOPrimitives::draw)
        .def("createSphere", &VAOPrimitives::createSphere)
        .def("createLineGrid", &VAOPrimitives::createLineGrid)
        .def("createCylinder", &VAOPrimitives::createCylinder)
        .def("createCone", &VAOPrimitives::createCone)
        .def("createDisk", &VAOPrimitives::createDisk)
        .def("createTorus", &VAOPrimitives::createTorus)
        .def("createTrianglePlane", &VAOPrimitives::createTrianglePlane)
        .def("createCapsule", &VAOPrimitives::createCapsule)
     //   .def("loadBinary", &VAOPrimitives::loadBinary)
        .def("clear", &VAOPrimitives::clear)
        .def("getVAOFromName", &VAOPrimitives::getVAOFromName)
        ;
  }

}
