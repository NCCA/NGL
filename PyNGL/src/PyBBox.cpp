#include "PyBindIncludes.h"

#include "BBox.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitBBox(py::module & m)
  {
    py::class_<BBox>(m, "BBox")
        .def(py::init<>())
        .def(py::init<const Vec3 &, Real ,Real , Real >())
        .def(py::init<Real,Real,Real,Real,Real,Real>())
        .def(py::init<const BBox&>())
        .def("draw",&BBox::draw)
        .def("setDrawMode",&BBox::setDrawMode)
        .def("minX",&BBox::minX)
        .def("maxX",&BBox::maxX)
        .def("minY",&BBox::minY)
        .def("maxY",&BBox::maxY)
        .def("minZ",&BBox::minZ)
        .def("maxZ",&BBox::maxZ)
        .def("center",&BBox::center)
        .def("width",(Real (BBox::*)() const)&BBox::width)
        .def("width",(void (BBox::*)(Real, bool) )&BBox::width)
        .def("height",(Real (BBox::*)() const)&BBox::height)
        .def("height",(void (BBox::*)(Real, bool) )&BBox::height)
        .def("depth",(Real (BBox::*)() const)&BBox::depth)
        .def("depth",(void (BBox::*)(Real, bool) )&BBox::depth)
        .def("getNormalArray", &BBox::getNormalArray)
        .def("getVertexArray", &BBox::getVertexArray)
        .def("setCenter",&BBox::setCenter)
        .def("recalculate",&BBox::recalculate)
        ;

  }

}
