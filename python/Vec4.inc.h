#ifndef __VECTOR_INC_H__
#define __VECTOR_INC_H__

class_<Vec4>("Vec4")
    /// we have to define an init method for
    /// each possible version available above
    .def(init<ngl::Real,ngl::Real,ngl::Real,ngl::Real >())
    .def(init<ngl::Real, ngl::Real,ngl::Real>())

    // prototype the methods
    .def("openGL",&Vec4::getOpenGL)
    .def("dot",&Vec4::dot)
    .def("set", Vec4SetF)
    .def("set", Vec4SetC)
    .def("null",&Vec4::null)
    .def("length",&Vec4::length)
    //.def("reverse",&Vec4::reverse)
    .def("normalize",&Vec4::normalize,return_value_policy<reference_existing_object>())
    .def("cross",cross2)
    .def("cross",cross)
    /// operator overloads
    .def(self + Vec4())
    .def(self - Vec4())
    .def(self += Vec4())
    .def(self -= Vec4())
    .def(self * Vec4())
    .def(Vec4()*self)
    .def(self * ngl::Real())
    .def(self / ngl::Real())
    .def(self /= ngl::Real())
    .def(self * ngl::Mat4())

    .def("__eq__",&Vec4::equals)
    /// this is the same as the [] operators
    .def("__getitem__",&Vec4::getItem)
    .def("__setitem__",&Vec4::setItem)
    .def( self != Vec4())
    .def( self / Vec4())
    .def("angleBetween",&Vec4::angleBetween)
    .def("inner",&Vec4::inner)
    .def("outer",&Vec4::outer)
    .def("lengthSquared",&Vec4::lengthSquared)
    .def("__str__",&Vec4::pyPrint)


;



#endif
