#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "Random.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitRandom(py::module & m)
  {
    py::class_<Random, std::unique_ptr<Random, py::nodelete>>(m, "Random")
        .def_static("instance",&Random::instance)
        .def("setSeed",(void(Random::*)() ) &Random::setSeed)
        .def("setSeed",(void(Random::*)(unsigned int)  ) &Random::setSeed)
        .def("getFloatFromGeneratorName",&Random::getFloatFromGeneratorName)
        .def("getRandomVec4",&Random::getRandomVec4)
        .def("getRandomNormalizedVec4",&Random::getRandomNormalizedVec4)
        .def("getRandomVec3",&Random::getRandomVec3)
        .def("getRandomNormalizedVec3",&Random::getRandomNormalizedVec3)
        .def("getRandomVec2",&Random::getRandomVec2)
        .def("getRandomNormalizedVec2",&Random::getRandomNormalizedVec2)
        .def("getRandomPoint",&Random::getRandomPoint)
        .def("randomNumber",&Random::randomNumber)
        .def("randomPositiveNumber",&Random::randomPositiveNumber)

        ;

  }

}
