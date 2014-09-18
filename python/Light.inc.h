#ifndef __LIGHT_INC_H__
#define __LIGHT_INC_H__

// import the namespace for convenience
using namespace boost::python;

//DIRECTIONALLIGHT, /// @brief directional light from old OPenGL
//  POINTLIGHT,  /// @brief point light
//  SPOTLIGHT=1

enum_<LIGHTMODES>("LIGHTMODES")
    .value("DIRECTIONALLIGHT", DIRECTIONALLIGHT)
    .value("POINTLIGHT", POINTLIGHT)
    .value("SPOTLIGHT", SPOTLIGHT)

    ;

// now we define a python class for the code
// above
class_<Light>("Light")
    /// we have to define an init method for
    /// each possible version available in the header
    .def(init<ngl::Vec3 , ngl::Colour ,LIGHTMODES>())
    .def(init<ngl::Vec3 ,ngl::Colour ,ngl::Colour ,LIGHTMODES>())
    .def(init<>())
    // prototype the methods
    .def("setPosition", &Light::setPosition)
    .def("setColour", &Light::setColour)
    .def("setSpecColour", &Light::setSpecColour)
    .def("setPosition", &Light::setPosition)
    .def("disable", &Light::disable)
    .def("enable", &Light::enable)
    .def("setAttenuation", &Light::setAttenuation)
  //  .def("getNumEnabledLights", &Light::getNumEnabledLights)
    .def("show", &Light::show)
  //  .def("getLightNum", &Light::getLightNum)
    .def("getPos", &Light::getPos,return_value_policy<reference_existing_object>())
    .def("getColour", &Light::getColour,return_value_policy<reference_existing_object>())

;

#endif

