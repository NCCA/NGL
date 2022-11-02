#include "PyBindIncludes.h"


#include "Mat2.h"
#include "Mat3.h"
#include "Mat4.h"
#include "Vec3.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitMat2(py::module & m)
  {
    py::class_<Mat2>(m, "Mat2")
        .def(py::init<>())
        .def(py::init<const Mat2&>())
        .def(py::init<Real,Real,Real,Real>())
        .def(py::init<Real>())
        .def("null",&Mat2::null)
        .def("identity",&Mat2::identity)
        .def("transpose",&Mat2::transpose)
        .def_static("rotate",&Mat2::rotate)
        .def_static("scale",&Mat2::scale)
        .def("openGL",&Mat2::openGL)
        .def_static("sizeof",[](){return sizeof(Mat2);})
        .def(py::self == py::self)
        .def(py::self * py::self)
        .def(py::self *= py::self)
        .def(py::self + py::self)
        .def(py::self += py::self)
        .def(py::self * Real())
        .def(py::self * Vec2())

        //.def(Real() * py::self)
        .def(py::self *= Real())
        .def(py::self * Vec2())
        .def("__repr__",
                [](const Mat2 &v) {
                    return
                        "["+std::to_string(v.m_00) + "," + std::to_string(v.m_01)  + "]\n" +
                        "["+std::to_string(v.m_10) + "," + std::to_string(v.m_11)  + "]\n" ;})

        .def_readwrite("m_openGL", &Mat2::m_openGL)
        .def_readwrite("m_00", &Mat2::m_00)
        .def_readwrite("m_01", &Mat2::m_01)
        .def_readwrite("m_10", &Mat2::m_10)
        .def_readwrite("m_11", &Mat2::m_11)


        ;

}
}
