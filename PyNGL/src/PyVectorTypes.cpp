#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/cast.h>

#include "Vec4.h"
#include "Mat4.h"
namespace py = pybind11;
PYBIND11_MAKE_OPAQUE(std::vector<uint32_t, std::allocator<uint32_t>>);

namespace ngl
{

  void pyInitVectorTypes(py::module & m)
  {

      using VectorUInt = std::vector<GLuint, std::allocator<GLuint>>;

      py::class_<std::vector<uint32_t>>(m, "VectorUInt")
        .def(py::init<>())
        .def("push_back", (void (VectorUInt::*)(const uint32_t &)) &VectorUInt::push_back)
        .def("__iter__", [](std::vector<uint32_t> &v) {
                return py::make_iterator(v.begin(), v.end());
             }, py::keep_alive<0, 1>())
          .def("__getitem__", [](const VectorUInt &s, size_t i) {
                      if (i >= s.size()) throw py::index_error();
                      return s[i];
                  })
          .def("__setitem__", [](VectorUInt &s, size_t i, uint32_t v) {
              if (i >= s.size()) throw py::index_error();
              s[i] = v;
          })
         .def("__len__",&VectorUInt::size)
          ;



   }
}
