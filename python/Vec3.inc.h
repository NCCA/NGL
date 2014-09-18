#ifndef __VEC3_INC_H__
#define __VEC3_INC_H__

class_<Vec3>("Vec3")
    /// we have to define an init method for
    /// each possible version available above
    .def(init<ngl::Real, ngl::Real,ngl::Real>())

    // prototype the methods
    .def("openGL",&Vec3::getOpenGL)
    .def("dot",&Vec3::dot)
    .def("set", Vec3SetF)
    .def("set", Vec3SetC)
    .def("set", Vec3SetC4)
    .def("set", Vec3SetP)

    .def("null",&Vec3::null)
    .def("length",&Vec3::length)
    .def("normalize",&Vec3::normalize)
    .def("cross",vec3cross2)
    .def("cross",vec3cross)
    /// operator overloads
    .def(self + Vec3())
    .def(self - Vec3())
    .def(self += Vec3())
    .def(self -= Vec3())
    .def(self * Vec3())
    .def(Vec3()*self)
    .def(self * ngl::Real())
    .def(self / ngl::Real())
    .def(self /= ngl::Real())

    .def("__eq__",&Vec3::equals)
    /// this is the same as the [] operators
    .def("__getitem__",&Vec3::getItem)
    .def("__setitem__",&Vec3::setItem)
    .def( self != Vec3())
    .def( self / Vec3())
    .def("inner",&Vec3::inner)
    .def("outer",&Vec3::outer)
    .def("__str__",&Vec3::pyPrint)
;



#endif
