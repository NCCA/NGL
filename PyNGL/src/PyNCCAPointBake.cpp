// #include <pybind11/pybind11.h>
// #include <pybind11/operators.h>
// #include <pybind11/stl.h>
// #include <pybind11/cast.h>
#include "PyBindIncludes.h"

#include "NCCAPointBake.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitPointBake(py::module & m)
  {
    py::class_<NCCAPointBake>(m, "NCCAPointBake")
        .def(py::init<>())
        .def(py::init<const std::string &>())
        .def("setFrame", &NCCAPointBake::setFrame)
        .def("loadPointBake", &NCCAPointBake::loadPointBake)
        .def("loadBinaryPointBake", &NCCAPointBake::loadBinaryPointBake)
        .def("saveBinaryPointBake", &NCCAPointBake::saveBinaryPointBake)
        .def("attachMesh", &NCCAPointBake::attachMesh)
        .def("setMeshToFrame", &NCCAPointBake::setMeshToFrame)
        .def("getNumFrames", &NCCAPointBake::getNumFrames)
        .def("getNumVerts", &NCCAPointBake::getNumVerts)
        .def("getRawDataPointer", &NCCAPointBake::getRawDataPointer)
        .def("getRawDataPointerAtFrame", &NCCAPointBake::getRawDataPointerAtFrame)
        ;
  }

}
