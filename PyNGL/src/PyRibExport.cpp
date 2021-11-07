#include "PyBindIncludes.h"

#include "RibExport.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitRibExport(py::module & m)
  {
    py::class_<RibExport>(m, "RibExport")
        .def(py::init<const std::string &,bool>())
        .def("writeTabs", &RibExport::writeTabs)
        .def("comment", &RibExport::comment)
        .def("open", &RibExport::open)
        .def("close", &RibExport::close)
        .def("WorldBegin", &RibExport::WorldBegin)
        .def("WorldEnd", &RibExport::WorldEnd)
        .def("AttributeBegin", &RibExport::AttributeBegin)
        .def("AttributeEnd", &RibExport::AttributeEnd)
        .def("TransformBegin", &RibExport::TransformBegin)
        .def("TransformEnd", &RibExport::TransformEnd)
        .def("writeToFile", &RibExport::writeToFile)
        .def("Translate", &RibExport::Translate)
        .def("Rotate", &RibExport::Rotate)
        .def("Scale", &RibExport::Scale)
        .def("Sphere", &RibExport::Sphere)
        .def("Cylinder", &RibExport::Cylinder)
        .def("Cone", &RibExport::Cone)
        .def("Paraboloid", &RibExport::Paraboloid)
        .def("Hyperboloid", &RibExport::Hyperboloid)
        .def("Disk", &RibExport::Disk)
        .def("Torus", &RibExport::Torus)
        .def("isOpen", &RibExport::isOpen)
        .def("getStream", &RibExport::getStream)
        ;
}

}
