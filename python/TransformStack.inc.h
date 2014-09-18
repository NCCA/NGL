#ifndef __TRANSFORMSTACK_INC_H__
#define __TRANSFORMSTACK_INC_H__

class_<TransformStack>("TransformStack")
    /// we have to define an init method for
    /// each possible version available above
    .def(init<TransformStack&>())
    .def(init<>())
    // prototype the methods
    .def("pushTransform",&TransformStack::pushTransform)
    .def("pushTransformAndCopy",&TransformStack::pushTransformAndCopy)
    .def("popTransform",&TransformStack::popTransform)
    .def("getCurrentTransform",&TransformStack::getCurrentTransform,return_value_policy<reference_existing_object>())
    .def("getCurrAndGlobal",&TransformStack::getCurrAndGlobal,return_value_policy<reference_existing_object>())
    .def("setCurrent",setCurrentT)
    .def("setCurrent",setCurrentM)
    .def("setGlobal",&TransformStack::setGlobal)
    .def("loadMatrixToShader",&TransformStack::loadMatrixToShader)
    .def("loadGlobalAndCurrentMatrixToShader",&TransformStack::loadGlobalAndCurrentMatrixToShader)
    .def("__str__",&TransformStack::pyPrint)
    .def("loadGlobalMatrixToShader",&TransformStack::loadGlobalMatrixToShader)
    .def("getGlobalMatrix",&TransformStack::getGlobalMatrix,return_value_policy<reference_existing_object>())
	.def("setScale",setScaleV)
	.def("setScale",setScaleF)
	.def("setPosition",setPositionV)
	.def("setPosition",setPositionF)
	.def("setRotation",setRotationV)
	.def("setRotation",setRotationF)

 ;

/*

      void setPosition(
											 ngl::Vector _pos
											);
      void setPosition(
											 ngl::Real _x,
											 ngl::Real _y,
											 ngl::Real _z
			                 );

      void setScale(
										ngl::Vector _scale
									 );
      void setScale(
											 ngl::Real _x,
											 ngl::Real _y,
											 ngl::Real _z
			                 );
      void setRotation(
											 ngl::Vector _rot
											);
       void setRotation(
											 ngl::Real _x,
											 ngl::Real _y,
											 ngl::Real _z
			                 );

 */

#endif
