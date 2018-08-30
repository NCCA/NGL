#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "Transformation.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitTransformation(py::module & m)
  {
    py::class_<Transformation>(m, "Transformation")
        .def(py::init<>())
        .def(py::init<const Transformation &>())
        .def("setScale", (void (Transformation::*)(const Vec3 &)) &Transformation::setScale)
        .def("setScale", (void (Transformation::*)(const Vec4 &)) &Transformation::setScale)
        .def("setScale", (void (Transformation::*)(Real,Real,Real)) &Transformation::setScale)
        .def("addScale", (void (Transformation::*)(const Vec3 &)) &Transformation::addScale)
        .def("addScale", (void (Transformation::*)(Real,Real,Real)) &Transformation::addScale)

        .def("setPosition", (void (Transformation::*)(const Vec3 &)) &Transformation::setPosition)
        .def("setPosition", (void (Transformation::*)(const Vec4 &)) &Transformation::setPosition)
        .def("setPosition", (void (Transformation::*)(Real,Real,Real)) &Transformation::setPosition)
        .def("addPosition", (void (Transformation::*)(const Vec3 &)) &Transformation::addPosition)
        .def("addPosition", (void (Transformation::*)(Real,Real,Real)) &Transformation::addPosition)

        .def("setRotation", (void (Transformation::*)(const Vec3 &)) &Transformation::setRotation)
        .def("setRotation", (void (Transformation::*)(const Vec4 &)) &Transformation::setRotation)
        .def("setRotation", (void (Transformation::*)(Real,Real,Real)) &Transformation::setRotation)
        .def("addRotation", (void (Transformation::*)(const Vec3 &)) &Transformation::addRotation)
        .def("addRotation", (void (Transformation::*)(Real,Real,Real)) &Transformation::addRotation)

        .def("setMatrix",&Transformation::setMatrix)
        .def("reset",&Transformation::reset)
        .def("getScale",&Transformation::getScale)
        .def("getPosition",&Transformation::getPosition)
        .def("getRotation",&Transformation::getRotation)
        .def("getMatrix",&Transformation::getMatrix)
        .def("getTransposeMatrix",&Transformation::getTransposeMatrix)
        .def("getInverseMatrix",&Transformation::getInverseMatrix)
  //      .def(py::self * py::self)
        .def(py::self *= py::self)
        //.def("loadMatrixToShader",&Transformation::loadMatrixToShader)
        //.def("loadGlobalAndCurrentMatrixToShader",&Transformation::loadGlobalAndCurrentMatrixToShader)
        ;

  }
}
