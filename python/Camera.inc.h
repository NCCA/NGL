#ifndef __CAMERA_INC_H__
#define __CAMERA_INC_H__

// import the namespace for convenience
using namespace boost::python;

class_<Camera>("Camera")
    /// we have to define an init method for
    /// each possible version available above
    .def(init<ngl::Vec3, ngl::Vec3,ngl::Vec3,ngl::CAMERAPROJECTION>())
    .def(init<>())

    .def("setOrthoParams",&Camera::setOrthoParams)
    .def("roll",&Camera::roll)
    .def("pitch",&Camera::pitch)
    .def("yaw",&Camera::yaw)
    .def("slide",&Camera::slide)
    .def("set",&Camera::set)
    .def("setShape",&Camera::setShape)
    .def("setAspect",&Camera::setAspect)
    .def("setDefaultCamera",&Camera::setDefaultCamera)
    .def("move",&Camera::move)
    .def("moveBoth",&Camera::moveBoth)
    .def("moveEye",&Camera::moveEye)
    .def("moveLook",&Camera::moveLook)
    .def("setViewAngle",&Camera::setViewAngle)
    .def("normalisedYaw",&Camera::normalisedYaw)
    .def("normalisedPitch",&Camera::normalisedPitch)
    .def("normalisedRoll",&Camera::normalisedRoll)
    .def("writeRib",&Camera::writeRib)
    .def("set2PointProjPoints",&Camera::set2PointProjPoints)
    .def("set3PointProjPoints",&Camera::set3PointProjPoints)
    .def("getViewMatrix",&Camera::getViewMatrix,return_value_policy<reference_existing_object>())
    .def("getProjectionMatrix",&Camera::getProjectionMatrix,return_value_policy<reference_existing_object>())
    .def("getEye",&Camera::getEye,return_value_policy<reference_existing_object>())
		.def("getFOV",&Camera::getFOV)
		.def("getAspect",&Camera::getAspect)
		.def("getNear",&Camera::getNear)
		.def("getFar",&Camera::getFar)
		.def("calculateFrustum",&Camera::calculateFrustum)
		.def("drawFrustum",&Camera::drawFrustum)
		.def("isPointInFrustum",&Camera::isPointInFrustum)
		.def("isSphereInFrustum",&Camera::isSphereInFrustum)

;


    enum_<CAMERAPROJECTION>("CAMERAPROJECTION")
        .value("ORTHOGRAPHIC", ORTHOGRAPHIC)
        .value("PERSPECTIVE", PERSPECTIVE)
        ;

#endif


