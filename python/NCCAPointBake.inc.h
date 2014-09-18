#ifndef __NCCAPOINTBAKE_INC_H__
#define __NCCAPOINTBAKE_H__

class_<NCCAPointBake>("NCCAPointBake")
    /// we have to define an init method for
    /// each possible version available above
    .def(init<>())
    .def(init<const std::string &>())

    // prototype the methods
    .def("setFrame",&NCCAPointBake::setFrame)
    .def("loadPointBake",&NCCAPointBake::loadPointBake)
    .def("setFrame",&NCCAPointBake::setFrame)
    .def("attachMesh",&NCCAPointBake::attachMesh)
    .def("setMeshToFrame",&NCCAPointBake::setMeshToFrame)
    .def("getNumFrames",&NCCAPointBake::getNumFrames)

    .def("loadBinaryPointBake",&NCCAPointBake::loadBinaryPointBake)
    .def("saveBinaryPointBake",&NCCAPointBake::saveBinaryPointBake)


;


#endif
