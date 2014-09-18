#ifndef __BEZIERCURVE_INC_H__
#define __BEZIERCURVE_INC_H__


// import the namespace for convenience
using namespace boost::python;
// now we define a python class for the code
// above
class_<BezierCurve>("BezierCurve")
    /// we have to define an init method for
    /// each possible version available in the header
    .def(init<Vec3 const *,const int &,Real const *,const int &>())
    .def(init<Real const *,const unsigned int >())
    .def(init<const BezierCurve &>())
    .def(init<>())
    // prototype the methods
    .def("draw", &BezierCurve::draw)
    .def("drawControlPoints", &BezierCurve::drawControlPoints)
    .def("drawHull", &BezierCurve::drawHull)
    .def("getPointOnCurve", &BezierCurve::getPointOnCurve)
    .def("addPoint", addPointF)
    .def("addPoint", addPointV)

    .def("addKnot", &BezierCurve::addKnot)
    .def("createKnots", &BezierCurve::createKnots)
    .def("coxDeBoor", &BezierCurve::coxDeBoor)
    .def("setLOD", &BezierCurve::setLOD)
;

#endif

