#ifndef __CREATECORECONTEXPY_INC_H__
#define __CREATECORECONTEXPY_INC_H__
// import the namespace for convenience
using namespace boost::python;
// now we define a python class for the code
// above
#include "Types.h"
// class_<Text>("Text", init<const QFont &>())
/*
class_<CreateCoreGLContext, bases<QGLContext>, boost::noncopyable >("CreateCoreGLContext")


    /// we have to define an init method for
    /// each possible version available in the header
   .def(init<const QGLFormat& , QPaintDevice* >())
   .def(init<const QGLFormat& >())
//CreateCoreGLContext() : QGLContext(format,device) {;}
//CreateCoreGLContext(const QGLFormat& format) : QGLContext(format) {;}
;
*/
#endif

