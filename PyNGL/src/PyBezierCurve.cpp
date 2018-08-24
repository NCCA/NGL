#include <pybind11/pybind11.h>

#include "BezierCurve.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitBezierCurve(py::module & m)
  {
    py::class_<BezierCurve>(m, "BezierCurve")
        .def(py::init<>())
        .def(py::init<const Vec3 *,unsigned int ,const Real  *,unsigned int >())
        .def(py::init<const Real  *,unsigned int >())
        .def(py::init<const BezierCurve &>())
        .def("draw", &BezierCurve::draw)
        .def("drawControlPoints",&BezierCurve::drawControlPoints)
        .def("drawHull",&BezierCurve::drawHull)
        .def("getPointOnCurve",&BezierCurve::getPointOnCurve)
        .def("addPoint",(void (BezierCurve::*)(const Vec3 &))&BezierCurve::addPoint)
        .def("addPoint",(void (BezierCurve::*)(Real,Real,Real))&BezierCurve::addPoint)
        .def("addKnot",&BezierCurve::addKnot)
        .def("createKnots",&BezierCurve::createKnots)
        .def("coxDeBoor",&BezierCurve::coxDeBoor)
        .def("setLOD",&BezierCurve::setLOD)
        .def("createVAO",&BezierCurve::createVAO)

        ;

  }

}
