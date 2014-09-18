#ifndef __NCCABINMESH_INC_H__
#define __NCCABINMESH_INC_H__

// import the namespace for convenience
using namespace boost::python;
// now we define a python class for the code
// above
/*
class_<NCCABinMesh, bases<AbstractMesh> , boost::noncopyable >("NCCABinMesh")
    /// we have to define an init method for
    /// each possible version available in the header
    .def(init<std::string>())
    .def(init<std::string,std::string>())
    // prototype the methods
    .def("load", &NCCABinMesh::load)
    .def("save", &NCCABinMesh::save)

;
*/
#endif

/*

 */
