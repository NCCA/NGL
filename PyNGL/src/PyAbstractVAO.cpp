#include "PyBindIncludes.h"

#include "AbstractVAO.h"
namespace py = pybind11;
namespace ngl
{

void pyInitAbstractVAO(py::module & m)
{
  py::class_<AbstractVAO>(m, "AbstractVAO")
    .def("bind", &AbstractVAO::bind)    
    .def("unbind", &AbstractVAO::unbind)
    .def("setVertexAttributePointer",&AbstractVAO::setVertexAttributePointer,
         py::arg("_id"),py::arg("_size"),py::arg("_type"),py::arg("_stride"),py::arg("_dataOffset"),py::arg("_normalise")=false)
    .def("setNumIndices",&AbstractVAO::setNumIndices)
    .def("numIndices", &AbstractVAO::numIndices)
    .def("getBufferID",&AbstractVAO::getBufferID)
    .def("getMode", &AbstractVAO::getMode)
    .def("setMode",&AbstractVAO::setMode)
      ;

/* Note this has been removed so we set values directly as python API doesn't work well
 * with const &
 */
  py::class_<AbstractVAO::VertexData>(m, "VertexData")
      .def(py::init<size_t,const GLfloat &, GLenum >(),
           py::arg("_size"),py::arg("_data"),py::arg("_mode")=GL_STATIC_DRAW)
      .def(py::init<size_t,const std::vector<float> &, GLenum >(),
           py::arg("_size"),py::arg("_data"),py::arg("_mode")=GL_STATIC_DRAW)
      .def(py::init<size_t,const std::vector<Vec2> &, GLenum >(),
           py::arg("_size"),py::arg("_data"),py::arg("_mode")=GL_STATIC_DRAW)
      .def(py::init<size_t,const std::vector<Vec3> &, GLenum >(),
           py::arg("_size"),py::arg("_data"),py::arg("_mode")=GL_STATIC_DRAW)
      .def(py::init<size_t,const std::vector<Vec4> &, GLenum >(),
           py::arg("_size"),py::arg("_data"),py::arg("_mode")=GL_STATIC_DRAW)

      ;

}
}
