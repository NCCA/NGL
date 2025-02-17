#include "PyBindIncludes.h"

#include "Vec3.h"
#include "SimpleVAO.h"
#include <vector>


namespace py = pybind11;
namespace ngl
{

  void pyInitSimpleVAO(py::module & m)
  {
    py::class_<SimpleVAO,AbstractVAO>(m, "SimpleVAO")
        .def_static("create",&SimpleVAO::create)
        .def("draw", &SimpleVAO::draw)
        .def("bind", &SimpleVAO::bind)
        .def("unbind", &SimpleVAO::unbind)
        .def("removeVAO", &SimpleVAO::removeVAO)
        .def("setData", py::overload_cast<size_t,const std::vector<Vec3> &>(&SimpleVAO::setData))
        .def("setData", py::overload_cast<size_t,const std::vector<float> &>(&SimpleVAO::setData))
        .def("getBufferID", &SimpleVAO::getBufferID)
        ;

  }


}
