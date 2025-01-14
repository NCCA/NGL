#include "PyBindIncludes.h"

#include "VAOPrimitives.h"
namespace py = pybind11;
namespace ngl
{

void pyInitVAOPrimitives(py::module &m)
{
  py::class_< VAOPrimitives, std::unique_ptr< VAOPrimitives, py::nodelete > >(m, "VAOPrimitives")
    .def_static("draw", py::overload_cast< std::string_view >(&VAOPrimitives::draw))
    .def_static("draw", py::overload_cast< std::string_view, GLenum >(&VAOPrimitives::draw))
    .def_static("createSphere", &VAOPrimitives::createSphere)
    .def_static("createLineGrid", &VAOPrimitives::createLineGrid)
    .def_static("createCylinder", &VAOPrimitives::createCylinder)
    .def_static("createCone", &VAOPrimitives::createCone)
    .def_static("createDisk", &VAOPrimitives::createDisk)
    .def_static("createTorus", &VAOPrimitives::createTorus)
    .def_static("createTrianglePlane", &VAOPrimitives::createTrianglePlane)
    .def_static("createCapsule", &VAOPrimitives::createCapsule)
    .def_static("clear", &VAOPrimitives::clear)
    .def_static("getVAOFromName", &VAOPrimitives::getVAOFromName);
}

} // namespace ngl
