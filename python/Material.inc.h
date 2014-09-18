#ifndef __MATERIAL_INC_H__
#define __MATERIAL_INC_H__

// import the namespace for convenience
using namespace boost::python;


enum_<STDMAT>("STDMAT")
    .value("BLACKPLASTIC", BLACKPLASTIC)
    .value("BRASS", BRASS)
    .value("BRONZE", BRONZE)
    .value("CHROME", CHROME)
    .value("COPPER", COPPER)
    .value("GOLD", GOLD)
    .value("PEWTER", PEWTER)
    .value("SILVER", SILVER)
    .value("POLISHEDSILVER", POLISHEDSILVER)

    ;

// now we define a python class for the code
// above
class_<Material>("Material")
    /// we have to define an init method for
    /// each possible version available in the header

    .def(init< ngl::Colour, ngl::Colour, ngl::Colour, ngl::Colour>())
    .def(init<int>())
    .def(init<STDMAT>())
    // prototype the methods
    .def("set", &Material::set)
    .def("change", &Material::change)
    .def("load", &Material::load)
    .def("setDefault", &Material::setDefault)
    .def("setAmbient", &Material::setAmbient)
    .def("setDiffuse", &Material::setDiffuse)
    .def("setSpecular", &Material::setSpecular)
    .def("setEmisive", &Material::setEmisive)
    .def("setSpecularExponent", &Material::setSpecularExponent)
    .def("setRoughness", &Material::setRoughness)

;

#endif
