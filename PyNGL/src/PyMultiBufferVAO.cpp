#include "PyBindIncludes.h"

#include "MultiBufferVAO.h"
#include "Vec3.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitMultiBufferVAO(py::module & m)
  {
    py::class_<MultiBufferVAO,AbstractVAO>(m, "MultiBufferVAO")
        .def_static("create",&MultiBufferVAO::create)
        .def("draw", &MultiBufferVAO::draw)
        .def("removeVAO", &MultiBufferVAO::removeVAO)
        .def("setData", py::overload_cast<size_t,const std::vector<Vec3> &>(&MultiBufferVAO::setData))
        .def("setData", py::overload_cast<size_t,const std::vector<float> &>(&MultiBufferVAO::setData))
        .def("setData", py::overload_cast<size_t,size_t,const std::vector<Vec3> &>(&MultiBufferVAO::setData))
        .def("setData", py::overload_cast<size_t,size_t,const std::vector<float> &>(&MultiBufferVAO::setData))
        .def("setData", py::overload_cast<size_t,const std::vector<Vec4> &>(&MultiBufferVAO::setData))
        .def("setData", py::overload_cast<size_t,size_t,const std::vector<Vec4> &>(&MultiBufferVAO::setData))

        .def("getBufferID", &MultiBufferVAO::getBufferID);
  }
}
