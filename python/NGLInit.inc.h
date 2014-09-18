#ifndef __NGLINIT_INC_H__
#define __NGLINIT_INC_H__
// import the namespace for convenience
using namespace boost::python;



/// notice no_init and nocopyable as singleton,

class_<NGLInit,boost::noncopyable>("NGLInit",no_init)
    /// we have to define an init method for
    /// each possible version available above

    .def("instance", &NGLInit::instance,
      return_value_policy<reference_existing_object>()).staticmethod("instance")
    .def("initGlew", &NGLInit::initGlew)


 ;



#endif


