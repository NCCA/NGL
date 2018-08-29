#include <pybind11/pybind11.h>
#include <pybind11/cast.h>

#include "AbstractVAO.h"
namespace py = pybind11;
namespace ngl
{

void pyInitAbstractVAO(py::module & m)
{
  py::class_<AbstractVAO>(m, "AbstractVAO")
    .def("bind", &AbstractVAO::bind)
    .def("unbind", &AbstractVAO::unbind)
    .def("setData", &AbstractVAO::setData)
    .def("setVertexAttributePointer",&AbstractVAO::setVertexAttributePointer,
         py::arg("_id"),py::arg("_size"),py::arg("_type"),py::arg("_stride"),py::arg("_dataOffset"),py::arg("_normalise")=false)
    .def("setNumIndices",&AbstractVAO::setNumIndices)
    .def("numIndices", &AbstractVAO::numIndices)
    .def("getBufferID",&AbstractVAO::getBufferID)
    .def("getMode", &AbstractVAO::getMode)
    .def("setMode",&AbstractVAO::setMode)
      ;

  py::class_<AbstractVAO::VertexData>(m, "VertexData")
      .def(py::init<size_t,const GLfloat &, GLenum >(),
           py::arg("_size"),py::arg("_data"),py::arg("_mode"))
      ;


}
}
