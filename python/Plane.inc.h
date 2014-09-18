#ifndef __PLANE_INC_H__
#define __PLANE_INC_H__

class_<Plane>("Plane")
    /// we have to define an init method for
    /// each possible version available above
    .def(init<ngl::Vec3,ngl::Vec3,ngl::Vec3 >())
    .def(init< >())

		// prototype the methods
    .def("setPoints",&Plane::setPoints)
    .def("setNormalPoint",&Plane::setNormalPoint)
    .def("setFloats",&Plane::setFloats)
    .def("distance",&Plane::distance)
    .def("getNormal",&Plane::getNormal)
    .def("getPoint", &Plane::getPoint)
    .def("getD", &Plane::getD)



;

/*



	*/

#endif
