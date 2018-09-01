#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>


#include "Mat4.h"
#include "Mat3.h"
#include "Vec4.h"
#ifdef USEGLM
  #include <glm/mat4x4.hpp>
#endif
namespace py = pybind11;
namespace ngl
{

  namespace py = pybind11;

  void pyInitMat4(py::module & m)
  {
    py::class_<Mat4>(m, "Mat4")
        .def(py::init<>())
        .def(py::init<Real,Real,Real,Real,
                      Real,Real,Real,Real,
                      Real,Real,Real,Real,
                      Real,Real,Real,Real>())
        .def(py::init<Real>())
        .def(py::init<Mat4 &>())
        .def(py::init<const glm::mat4  &>())
        .def("setAtXY",&Mat4::setAtXY)
        .def("null",&Mat4::null)
        .def("identity",&Mat4::identity)
        .def("transpose",&Mat4::transpose)
        .def("rotateX",&Mat4::rotateX)
        .def("rotateY",&Mat4::rotateY)
        .def("rotateZ",&Mat4::rotateZ)
        .def("translate",&Mat4::translate)
        .def("scale",&Mat4::scale)
        .def("determinant",&Mat4::determinant)
        .def("inverse",&Mat4::inverse)
        .def("euler",&Mat4::euler)
        .def("openGL",&Mat4::openGL, py::return_value_policy::reference)
        .def("getLeftVector",&Mat4::getLeftVector)
        .def("getRightVector",&Mat4::getRightVector)
        .def("getUpVector",&Mat4::getUpVector)
        .def("getDownVector",&Mat4::getDownVector)
        .def("getForwardVector",&Mat4::getForwardVector)
        .def("getBackVector",&Mat4::getBackVector)
        .def("adjacent",(Mat4 (Mat4::*)())&Mat4::adjacent)
        .def("adjacent",(Mat4 (Mat4::*)(const Mat4 &))&Mat4::adjacent)
        .def(py::self == py::self)
        .def(py::self * py::self)
        .def(py::self *= py::self)
        .def(py::self + py::self)
        .def(py::self += py::self)
        .def(py::self * Real())
        //.def(Real() * py::self)
        .def(py::self *= Real())
        .def(py::self * Vec3())
        .def(py::self * Vec4())
        .def("__repr__",
                [](const Mat4 &v) {
                    return
                        "["+std::to_string(v.m_00) + "," + std::to_string(v.m_01) + "," + std::to_string(v.m_02) + "," + std::to_string(v.m_03) + "]\n" +
                        "["+std::to_string(v.m_10) + "," + std::to_string(v.m_11) + "," + std::to_string(v.m_12) + "," + std::to_string(v.m_13) + "]\n" +
                        "["+std::to_string(v.m_20) + "," + std::to_string(v.m_21) + "," + std::to_string(v.m_22) + "," + std::to_string(v.m_23) + "]\n" +
                        "["+std::to_string(v.m_30) + "," + std::to_string(v.m_31) + "," + std::to_string(v.m_32) + "," + std::to_string(v.m_33) + "]\n";})
        //.def_readwrite("m_m", &Mat4::m_m)
        .def_readwrite("m_openGL", &Mat4::m_openGL)
        .def_readwrite("m_00", &Mat4::m_00)
        .def_readwrite("m_01", &Mat4::m_01)
        .def_readwrite("m_02", &Mat4::m_02)
        .def_readwrite("m_03", &Mat4::m_03)
        .def_readwrite("m_10", &Mat4::m_10)
        .def_readwrite("m_11", &Mat4::m_11)
        .def_readwrite("m_12", &Mat4::m_12)
        .def_readwrite("m_13", &Mat4::m_13)
        .def_readwrite("m_20", &Mat4::m_20)
        .def_readwrite("m_21", &Mat4::m_21)
        .def_readwrite("m_22", &Mat4::m_22)
        .def_readwrite("m_23", &Mat4::m_23)
        .def_readwrite("m_30", &Mat4::m_30)
        .def_readwrite("m_31", &Mat4::m_31)
        .def_readwrite("m_32", &Mat4::m_32)
        .def_readwrite("m_33", &Mat4::m_33)



        ;


  }
}
