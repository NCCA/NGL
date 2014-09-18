#ifndef __TEXTURE_INC_H__
#define __TEXTURE_INC_H__


// import the namespace for convenience
using namespace boost::python;
// now we define a python class for the code
// above
class_<Texture>("Texture")
    /// we have to define an init method for
    /// each possible version available in the header
    .def(init<const std::string &>())
    .def(init<>())
    // prototype the methods
    .def("loadImage", &Texture::loadImage)
    .def("getFromXY", &Texture::getFromXY)
    .def("setTextureGL", &Texture::setTextureGL)
    .def("setMultiTexture",&Texture::setMultiTexture)
    .def("getColourFromXY",&Texture::getColourFromXY)
    .def("getColour",&Texture::getColour)
    ;



#endif

