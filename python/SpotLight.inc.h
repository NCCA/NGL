#ifndef __SPOTLIGHT_INC_H__
#define __SPOTLIGHT_INC_H__

// import the namespace for convenience
using namespace boost::python;


// now we define a python class for the code
// above
class_<SpotLight, bases<Light>  >("SpotLight")
    /// we have to define an init method for
    /// each possible version available in the header

    .def(init<ngl::Vec3 ,ngl::Vec3, ngl::Colour>())
    .def(init<>())
    // prototype the methods
    .def("set", &SpotLight::set)
    .def("show", &SpotLight::show)
    .def("enable", &SpotLight::enable)
    .def("setParams", &SpotLight::setParams)
    .def("aim", &SpotLight::aim)
;

#endif

