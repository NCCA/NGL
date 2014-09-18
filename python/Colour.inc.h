#ifndef __COLOUR_INC_H__
#define __COLOUR_INC_H__

// create a python modle
//BOOST_PYTHON_MODULE(ngl)

// import the namespace for convenience
using namespace boost::python;
// now we define a python class for the code
// above
class_<Colour>("Colour")
    /// we have to define an init method for
    /// each possible version available in the header
    .def(init<ngl::Real, ngl::Real,ngl::Real,ngl::Real>())
    .def(init<ngl::Real, ngl::Real,ngl::Real>())
    .def(init<ngl::Real, ngl::Real>())
    .def(init<ngl::Real>())
    .def(init<>())

    // prototype the methods
    .def("clamp", &Colour::clamp)
    .def("set", coloursetF)
    .def("set", coloursetC)
    .def("add", &Colour::add)
    .def("openGL",&Colour::getOpenGL)
    /// operator overloads
    .def(self + Colour())
    .def(self - Colour())
    .def(self += Colour())
    .def(self * Colour())
    .def(self * ngl::Real())
    .def(self *= Colour())
    .def(self *= ngl::Real())

    .def("__getitem__",&Colour::getItem)
    .def("__setitem__",&Colour::setItem)
    .def("__str__",&Colour::pyPrint)
    // finally we define the properties
    // as python allows direct access to the
    // private attributes
    .add_property("m_r",getR, setR)
    .add_property("m_g",getG, setG)
    .add_property("m_b",getB, setB)
    .add_property("m_a",getA, setA)

;

#endif

