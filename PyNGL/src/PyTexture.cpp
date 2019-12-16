#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "Texture.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitTexture(py::module & m)
  {
    py::class_<Texture>(m, "Texture")
        .def(py::init<const std::string>())
        .def("loadImage", &Texture::loadImage)
        .def("getPixels", &Texture::getPixels)
        .def("setTextureGL", &Texture::setTextureGL)
        .def("setMultiTexture", &Texture::setMultiTexture)
        .def("getWidth", &Texture::getWidth)
        .def("getHeight", &Texture::getHeight)
        .def("getFormat", &Texture::getFormat)
        .def("getImage", &Texture::getImage)

        ;

  }
}
