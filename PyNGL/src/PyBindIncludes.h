#ifndef PYBINDINCLUDES_H_
#define PYBINDINCLUDES_H_
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>
#include <pybind11/stl_bind.h>
#include <pybind11/pytypes.h>
#include <pybind11/complex.h>

#include <ngl/Vec2.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>

PYBIND11_MAKE_OPAQUE(std::vector<uint32_t, std::allocator<uint32_t>>)
PYBIND11_MAKE_OPAQUE(std::vector<float, std::allocator<float>>)
PYBIND11_MAKE_OPAQUE(std::vector<ngl::Vec2, std::allocator<ngl::Vec2>>)
PYBIND11_MAKE_OPAQUE(std::vector<ngl::Vec3, std::allocator<ngl::Vec3>>)


PYBIND11_MAKE_OPAQUE(std::vector<ngl::Vec4, std::allocator<ngl::Vec4>>)

#endif