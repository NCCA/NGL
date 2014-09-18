#ifndef __QUATERNION_INC_H__
#define __QUATERNION_INC_H__

// create a python modle

// import the namespace for convenience
using namespace boost::python;
// now we define a python class for the code
// above
class_<Quaternion>("Quaternion")
    /// we have to define an init method for
    /// each possible version available in the header
    .def(init<ngl::Real, ngl::Real,ngl::Real,ngl::Real>())
    .def("set",&Quaternion::set)
    .def("normalise",&Quaternion::normalise)
    //.def("fromMatrix",&Quaternion::fromMatrix)
    .def("fromAxisAngle",&Quaternion::fromAxisAngle)
    .def("fromEulerAngles",&Quaternion::fromEulerAngles)
    .def("magnitude",&Quaternion::magnitude)
    //.def("asMatrix",getMatrix)
    .def("toAxisAngle",&Quaternion::toAxisAngleT)
		.def("rotateX",&Quaternion::rotateX)
		.def("rotateY",&Quaternion::rotateY)
		.def("rotateZ",&Quaternion::rotateZ)

    // prototype the methods
    /// operator overloads
    .def(self * Quaternion())
    .def(self * ngl::Vec4())

    .def("__eq__",&Quaternion::equals)
    .def("__neg__",&Quaternion::negate)

    .def("__getitem__",&Quaternion::getItem)
    .def("__setitem__",&Quaternion::setItem)
    .def("__str__",&Quaternion::pyPrint)
    // finally we define the properties
    // as python allows direct access to the
    // private attributes

;
/*



  friend Quaternion SLERP(
                          const Quaternion &_q1,
                          const Quaternion &_q2,
                          const float &_t
                          );


 */
#endif

