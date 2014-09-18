#ifndef __BBOX_INC_H__
#define __BBOX_INC_H__

// import the namespace for convenience
using namespace boost::python;

class_<BBox>("BBox")
    /// we have to define an init method for
    /// each possible version available above
    .def(init<ngl::Real, ngl::Real,ngl::Real,ngl::Real,ngl::Real,ngl::Real>())
    .def(init<ngl::Vec3 , ngl::Real, ngl::Real,ngl::Real>())
    .def(init<ngl::BBox>())
    .def(init<>())
    .def("draw",&BBox::draw)
    .def("setDrawMode",&BBox::setDrawMode)
    .def("minX",&BBox::minX)
    .def("minX",&BBox::minX)
    .def("minY",&BBox::minY)
    .def("maxY",&BBox::maxY)
    .def("minZ",&BBox::minZ)
    .def("maxZ",&BBox::maxZ)
    .def("center",&BBox::center)
    //.def("width",&BBox::width)
    //.def("height",&BBox::height)
    //.def("depth",&BBox::depth)
    .def("setCenter",&BBox::setCenter)




;



#endif


