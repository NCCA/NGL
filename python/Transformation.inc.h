#ifndef __TRANSFORMATION_INC_H__
#define __TRANSFORMATION_INC_H__


enum_<ACTIVEMATRIX>("ACTIVEMATRIX")
      .value("NORMAL", NORMAL)
      .value("TRANSPOSE", TRANSPOSE)
      .value("INVERSE", INVERSE)

      ;
class_<Transformation>("Transformation")
    /// we have to define an init method for
    /// each possible version available above
    .def(init<>())
    // prototype the methods
    .def("setScale",setScaleV)
    .def("setScale",setScaleF)
    .def("setPosition",setPositionV)
    .def("setPosition",setPositionF)
    .def("setRotation",setRotationV)
    .def("setRotation",setRotationF)

    .def("addScale",addScaleV)
    .def("addScale",addScaleF)
    .def("addPosition",addPositionV)
    .def("addPosition",addPositionF)
    .def("addRotation",addRotationV)
    .def("addRotation",addRotationF)

    .def("getPosition",&Transformation::getPosition,return_value_policy<reference_existing_object>())
    .def("getRotation",&Transformation::getRotation,return_value_policy<reference_existing_object>())
    .def("setMatrix",&Transformation::setMatrix)
    .def("getScale",&Transformation::getScale,return_value_policy<reference_existing_object>())

    .def("getMatrix",&Transformation::getMatrix,return_value_policy<reference_existing_object>())
    .def("getTransposeMatrix",&Transformation::getTransposeMatrix,return_value_policy<reference_existing_object>())
    .def("getInverseMatrix",&Transformation::getInverseMatrix,return_value_policy<reference_existing_object>())


    .def("loadMatrixToShader",&Transformation::loadMatrixToShader)
    .def("loadGlobalAndCurrentMatrixToShader",&Transformation::loadGlobalAndCurrentMatrixToShader)


    /// operator overloads
    .def(self *= Transformation())
    .def(self * Transformation())

 ;


#endif
