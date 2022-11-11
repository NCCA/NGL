#include "PyBindIncludes.h"

#include "Text.h"
namespace py = pybind11;
namespace ngl
{

void pyInitText(py::module &m)
{
  py::class_< Text >(m, "Text")
    .def(py::init< std::string_view, int >())
    .def("renderText", py::overload_cast< float, float, std::string_view >(&Text::renderText, py::const_))
    .def("setScreenSize", &Text::setScreenSize)
    .def("setColour", py::overload_cast< float, float, float >(&Text::setColour));
}
} // namespace ngl
