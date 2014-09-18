#ifndef __OBJ_INC_H__
#define __OBJ_INC_H__

// import the namespace for convenience
using namespace boost::python;
// now we define a python class for the code
// above

class_<Obj, bases<AbstractMesh>, boost::noncopyable >("Obj")
    /// we have to define an init method for
    /// each possible version available in the header
    .def(init<std::string>())
    .def(init<std::string,std::string>())
    // prototype the methods
    .def("load", &Obj::load)
    .def("save", &Obj::save)



;

#endif

