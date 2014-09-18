#ifndef __TEXT_INC_H__
#define __TEXT_INC_H__

// import the namespace for convenience
using namespace boost::python;
/// @note in the example below we only have a single ctor with a param
/// to get this to compile using boost::python we can't use .def and must
/// inline as shown in the class below
class_<Text>("Text", init<const QFont &>())
  .def("renderText",&Text::renderText)
  .def("setScreenSize",&Text::setScreenSize)
  .def("setColour",setColourC)
  .def("setColour",setColourF)
;

#endif
