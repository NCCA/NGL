#ifndef __HoudiniGeo_INC_H__
#define __HoudiniGeo_INC_H__

// import the namespace for convenience
using namespace boost::python;
// now we define a python class for the code
// above

class_<HoudiniGeo, bases<AbstractMesh> , boost::noncopyable>("HoudiniGeo")
    /// we have to define an init method for
    /// each possible version available in the header
    .def(init<const std::string&>())
    .def(init<std::string &,std::string&>())
    // prototype the methods
    .def("drawDebugPoints", &HoudiniGeo::drawDebugPoints)


;

#endif

