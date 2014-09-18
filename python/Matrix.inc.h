#ifndef __MATRIX_INC_H__
#define __MATRIX_INC_H__

class_<Mat4>("Mat4")
    /// we have to define an init method for
    /// each possible version available above
    .def(init<>())
    .def(init<ngl::Real>())
    .def(init<int>())
    .def(init<double>())
    // prototype the methods

    .def("openGL",&Mat4::getOpenGL)
    .def("identity",&Mat4::identity,return_value_policy<reference_existing_object>())
    .def("transpose",&Mat4::transpose,return_value_policy<reference_existing_object>())
    .def("rotateX",&Mat4::rotateX)
    .def("rotateY",&Mat4::rotateY)
    .def("rotateZ",&Mat4::rotateZ)
    .def("translate",&Mat4::translate)
    .def("scale",&Mat4::scale)
    .def("null",&Mat4::null,return_value_policy<reference_existing_object>())
    .def("determinant",&Mat4::determinant)
    .def("euler",&Mat4::euler)
    .def("inversePossible",&Mat4::inversePossible)
    .def("getInverse",&Mat4::getInverse)

    /// operator overloads
    .def(self *  ngl::Mat4())
    .def(self *= ngl::Mat4())
    .def(self +  ngl::Mat4())
    .def(self +=  ngl::Mat4())
    .def(self * ngl::Real())
    .def(self *= ngl::Real())
    .def(self * ngl::Vec4())
  //  .def(ngl::Vector() * self)

    /// this is the same as the [] operators
    .def("__getitem__",&Mat4::getItem)
    .def("__setitem__",&Mat4::setItem)
    .def("__str__",&Mat4::pyPrint)


    ;

#endif


/*
  void SubMatrix3x3(
                    const int _i,
                    const int _j,
                    Real o_mat[]
                   ) const;


  Quaternion AsQuaternion() const;
  Vector operator * (
                     const Vector &_v
                    ) const;

 */


