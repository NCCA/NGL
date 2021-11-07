// #include <pybind11/pybind11.h>
// #include <pybind11/operators.h>
// #include <pybind11/stl.h>
// #include <pybind11/cast.h>
#include "PyBindIncludes.h"

#include "Random.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitRandom(py::module & m)
  {
    py::class_<Random, std::unique_ptr<Random, py::nodelete>>(m, "Random")
        .def_static("setSeed",py::overload_cast<> (&Random::setSeed))
        .def_static("setSeed",py::overload_cast<unsigned int>(&Random::setSeed))
        .def_static("getFloatFromGeneratorName",&Random::getFloatFromGeneratorName)
        .def_static("getIntFromGeneratorName",&Random::getIntFromGeneratorName)
        .def_static("getRandomVec4",&Random::getRandomVec4)
        .def_static("getRandomNormalizedVec4",&Random::getRandomNormalizedVec4)
        .def_static("getRandomVec3",&Random::getRandomVec3)
        .def_static("getRandomNormalizedVec3",&Random::getRandomNormalizedVec3)
        .def_static("getRandomVec2",&Random::getRandomVec2)
        .def_static("getRandomNormalizedVec2",&Random::getRandomNormalizedVec2)
        .def_static("getRandomPoint",&Random::getRandomPoint)
        .def_static("randomNumber",&Random::randomNumber ,py::arg("_mult") = 1)
        .def_static("randomPositiveNumber",&Random::randomPositiveNumber, py::arg("_mult") = 1)

        ;

  }

}
