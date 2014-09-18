#ifndef __RANDOM_INC_H__
#define __RANDOM_INC_H__

enum_<RANDDIST>("RANDDIST")
      .value("uniform_smallint", uniform_smallint)
      .value("uniform_int", uniform_int)
      .value("uniform_real", uniform_real)
      .value("bernoulli_distribution", bernoulli_distribution)
      .value("binomial_distribution", binomial_distribution)
      .value("cauchy_distribution", cauchy_distribution)
      .value("gamma_distribution", gamma_distribution)
      .value("poisson_distribution", poisson_distribution)
      .value("geometric_distribution", geometric_distribution)
      .value("triangle_distribution", triangle_distribution)
      .value("exponential_distribution", exponential_distribution)
      .value("normal_distribution", normal_distribution)
      .value("lognormal_distribution", lognormal_distribution)
      ;


class_<Random,boost::noncopyable>("Random",no_init)
    /// we have to define an init method for
    /// each possible version available above

    .def("instance", &Random::instance,
      return_value_policy<reference_existing_object>()).staticmethod("instance")


    .def("randomNumber",&Random::randomNumber)

// prototype the methods
    .def("setSeed",setSeedV)
    .def("setSeed",setSeedI)
    .def("getFloatFromGeneratorName",&Random::getFloatFromGeneratorName)
    .def("getRandomColour",&Random::getRandomColour)
    .def("getRandomColourAndAlpha",&Random::getRandomColourAndAlpha)
    .def("getRandomVec4",&Random::getRandomVec4)
    .def("getRandomNormalizedVec3",&Random::getRandomNormalizedVec3)
    .def("getRandomPoint",&Random::getRandomPoint)
    .def("randomNumber",&Random::randomNumber)
    .def("randomPositiveNumber",&Random::randomPositiveNumber)
    .def("addGenerator",&Random::addGenerator)

;

#endif
