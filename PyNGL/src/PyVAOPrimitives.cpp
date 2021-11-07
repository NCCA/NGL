// #include <pybind11/pybind11.h>
// #include <pybind11/operators.h>
// #include <pybind11/stl.h>
// #include <pybind11/cast.h>
#include "PyBindIncludes.h"

#include "VAOPrimitives.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitVAOPrimitives(py::module & m)
  {
    py::class_<VAOPrimitives, std::unique_ptr<VAOPrimitives, py::nodelete>>(m, "VAOPrimitives")
        .def_static("draw", py::overload_cast<const std::string &>(&VAOPrimitives::draw))
        .def_static("draw", py::overload_cast<const std::string &, GLenum>(&VAOPrimitives::draw))
        .def_static("createSphere", &VAOPrimitives::createSphere)
        .def_static("createLineGrid", &VAOPrimitives::createLineGrid)
        .def_static("createCylinder", &VAOPrimitives::createCylinder)
        .def_static("createCone", &VAOPrimitives::createCone)
        .def_static("createDisk", &VAOPrimitives::createDisk)
        .def_static("createTorus", &VAOPrimitives::createTorus)
        .def_static("createTrianglePlane", &VAOPrimitives::createTrianglePlane)
        .def_static("createCapsule", &VAOPrimitives::createCapsule)
        .def_static("clear", &VAOPrimitives::clear)
        .def_static("getVAOFromName", &VAOPrimitives::getVAOFromName)
        ;
  }

}
