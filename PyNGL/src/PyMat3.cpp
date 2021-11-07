#include "PyBindIncludes.h"


#include "Mat3.h"
#include "Mat4.h"
#include "Vec3.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitMat3(py::module & m)
  {
    py::class_<Mat3>(m, "Mat3")
        .def(py::init<>())
        .def(py::init<Real,Real,Real,Real,Real,Real,Real,Real,Real>())
        .def(py::init<Mat4 &>())
        .def(py::init<Mat3 &>())
        .def(py::init<Real>())
        .def("setAtXY",&Mat3::setAtXY)
        .def("null",&Mat3::null)
        .def("identity",&Mat3::identity)
        .def("transpose",&Mat3::transpose)
        .def("rotateX",&Mat3::rotateX)
        .def("rotateY",&Mat3::rotateY)
        .def("rotateZ",&Mat3::rotateZ)
        .def("scale",&Mat3::scale)
        .def("determinant",&Mat3::determinant)
        .def("inverse",&Mat3::inverse)
        .def("euler",&Mat3::euler)
        .def("openGL",&Mat3::openGL)
        .def("getLeftVector",&Mat3::getLeftVector)
        .def("getRightVector",&Mat3::getRightVector)
        .def("getUpVector",&Mat3::getUpVector)
        .def("getDownVector",&Mat3::getDownVector)
        .def("getForwardVector",&Mat3::getForwardVector)
        .def("getBackVector",&Mat3::getBackVector)
        .def_static("sizeof",[](){return sizeof(Mat3);})

        .def(py::self == py::self)
        .def(py::self * py::self)
        .def(py::self *= py::self)
        .def(py::self + py::self)
        .def(py::self += py::self)
        .def(py::self * Real())
        //.def(Real() * py::self)
        .def(py::self *= Real())
        .def(py::self * Vec3())
        .def("__repr__",
                [](const Mat3 &v) {
                    return
                        "["+std::to_string(v.m_00) + "," + std::to_string(v.m_01) + "," + std::to_string(v.m_02) + "]\n" +
                        "["+std::to_string(v.m_10) + "," + std::to_string(v.m_11) + "," + std::to_string(v.m_12) + "]\n" +
                        "["+std::to_string(v.m_20) + "," + std::to_string(v.m_21) + "," + std::to_string(v.m_22) + "]\n";})

        .def_readwrite("m_openGL", &Mat3::m_openGL)
        .def_readwrite("m_00", &Mat3::m_00)
        .def_readwrite("m_01", &Mat3::m_01)
        .def_readwrite("m_02", &Mat3::m_02)
        .def_readwrite("m_10", &Mat3::m_10)
        .def_readwrite("m_11", &Mat3::m_11)
        .def_readwrite("m_12", &Mat3::m_12)
        .def_readwrite("m_20", &Mat3::m_20)
        .def_readwrite("m_21", &Mat3::m_21)
        .def_readwrite("m_22", &Mat3::m_22)


        ;

}
}
