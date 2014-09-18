#ifndef __VAOPrimitives_INC_H__
#define __VAOPrimitives_INC_H__
// import the namespace for convenience
using namespace boost::python;

/// notice no_init and nocopyable as singleton,

class_<VAOPrimitives,boost::noncopyable>("VAOPrimitives",no_init)
    /// we have to define an init method for
    /// each possible version available above

    .def("instance", &VAOPrimitives::instance,
      return_value_policy<reference_existing_object>()).staticmethod("instance")

    .def("createSphere",&VAOPrimitives::createSphere)
    .def("createTrianglePlane",&VAOPrimitives::createTrianglePlane)
    .def("createCone",&VAOPrimitives::createCone)
    .def("createCylinder",&VAOPrimitives::createCylinder)
    .def("createDisk",&VAOPrimitives::createDisk)
    .def("createTorus",&VAOPrimitives::createTorus)

    .def("clearVAOs",&VAOPrimitives::clear)
    .def("draw",&VAOPrimitives::draw)

 ;

/// @todo implement the following
///  .def("RemoveVBO",&VAOPrimitives::RemoveVBO)
// .def("MapVBO",&VAOPrimitives::MapVBO)
// .def("UnMapVBO",&VAOPrimitives::UnMapVBO)



#endif


