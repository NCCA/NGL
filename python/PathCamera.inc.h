#ifndef __PATHCAMERA_INC_H__
#define __PATHCAMERA_INC_H__

// import the namespace for convenience
using namespace boost::python;

class_<PathCamera, bases<Camera> >("PathCamera")
    /// we have to define an init method for
    /// each possible version available above
    .def(init<const Vec3 &,const BezierCurve &,const BezierCurve &,const Real,const CAMERAPROJECTION >())
    .def(init<const Vec3 &,Vec3 const *,int ,Vec3 const  *,int ,Real ,CAMERAPROJECTION >())
    .def(init<const Vec4 &,const std::string &,Real,CAMERAPROJECTION >())
    .def("update",&PathCamera::update)
    .def("updateLooped",&PathCamera::updateLooped)
    .def("drawPaths",&PathCamera::drawPaths)
    .def("loadPath",&PathCamera::loadPath)
    .def("createCurvesForDrawing",&PathCamera::setOrthoParams)

    ;



#endif

