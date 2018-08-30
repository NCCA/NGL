#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "Image.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitImage(py::module & m)
  {
    py::class_<Image>(m, "Image")
        .def(py::init<>())
        .def(py::init<const std::string &>())
        .def(py::init<const Image  &>())
        .def("load",&Image::load)
        .def("getPixels",&Image::getPixels)
        .def("saveFrameBufferToFile",&Image::saveFrameBufferToFile)
        .def("width",&Image::width)
        .def("height",&Image::height)
        .def("format",&Image::format)
        .def("channels",&Image::channels)
//        .def("getColour",(Colour(Image::*)(const GLuint,const GLuint) const) &Image::getColour)
//        .def("getColour",(Colour(Image::*)(const Real,const Real) const)&Image::getColour)

        ;

    py::enum_<Image::ImageModes>(m, "ImageModes")
        .value("RGB",Image::ImageModes::RGB )
        .value("RGBA",Image::ImageModes::RGBA);

  }

}
