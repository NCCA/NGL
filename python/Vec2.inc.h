#ifndef __VEC2_INC_H__
#define __VEC2_INC_H__

class_<Vec2>("Vec2")
    /// we have to define an init method for
    /// each possible version available above
    .def(init<ngl::Real,ngl::Real >())
    // prototype the methods
    .def("openGL",&Vec2::getOpenGL)
    .def("set", Vec2SetF)
    .def("set", Vec2SetC)
    /// operator overloads
    .def(self + Vec2())
    .def(self - Vec2())
    .def(self += Vec2())
    .def(self -= Vec2())
    .def(self * Vec2())
    .def(Vec2()*self)
    //.def(self * ngl::Real())
    .def(self / ngl::Real())
    .def(self /= ngl::Real())

    .def("__eq__",&Vec2::equals)
    /// this is the same as the [] operators
    .def("__getitem__",&Vec2::getItem)
    .def("__setitem__",&Vec2::setItem)
    .def( self != Vec2())
    .def( self / Vec2())
    .def("__str__",&Vec2::pyPrint)


;



#endif
