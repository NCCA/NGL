#include <pybind11/pybind11.h>
#include "Vec4.h"
#include "Mat4.h"
#include "Util.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitUtils(py::module & m)
  {

    m.def("calcNormal",(Vec3(*)(const Vec4 &,const Vec4 &,const Vec4 & ))&calcNormal);
    m.def("calcNormal",(Vec3(*)(const Vec3 &,const Vec3 &,const Vec3 & ))&calcNormal);
    m.def("perspective",&perspective);
    m.def("perspectiveFov",&perspectiveFov);
    m.def("infinitePerspective",&infinitePerspective);
    m.def("lookAt",&lookAt);
    m.def("ortho",(Mat4(*)(Real,Real,Real,Real,Real,Real)) &ortho);
    m.def("ortho",(Mat4(*)(Real,Real,Real,Real)) &ortho);
    m.def("frustum",&frustum);
    m.def("project",&project);
    m.def("unProject",&unProject);
    m.def("radians",&radians);
    m.def("degrees",&degrees);
    m.def("isPowerOfTwo",&isPowerOfTwo);
    m.def("nextPow2",&nextPow2);
    m.def("NGLCheckGLError",&NGLCheckGLError);
  }

}
