// part of the python bindings
#ifdef NO_PYTHON_LIB
  #include "Python.h"
  #include <boost/python.hpp>
  #include <boost/format.hpp>
  #include "Types.h"
  #include "Colour.h"
  #include "Vec4.h"
  #include "Mat4.h"
  #include "Quaternion.h"
  #include "BBox.h"
  #include "Camera.h"
  #include "VAOPrimitives.h"
  #include "Light.h"
  #include "Material.h"
  #include "AbstractMesh.h"
  #include "Obj.h"
  #include "ShaderLib.h"
  #include "Transformation.h"
  #include "TransformStack.h"
  #include "Texture.h"
  #include "BezierCurve.h"
  #include "PathCamera.h"
  #include "NCCABinMesh.h"
  #include "SpotLight.h"
  #include "Random.h"
  #include "NCCAPointBake.h"
  #include "NGLInit.h"
  #include "Shader.h"
  #include "ShaderProgram.h"
	#include "Plane.h"
  #include "Text.h"
  #include "Vec3.h"
  #include "Vec2.h"
  #include "VertexArrayObject.h"


#endif
/// @file PythonWrapper.cpp
/// @brief this is the python wrapper for the ngl library
/// this is quite convoluted as we need to have access to the methods etc
/// as well as wrapping other stuff into the BOOST_PYTHON_MODULE element
/// where we must have all the classes defined in the same module
/// So to break it all down we have .inc.cpp files with the access and
/// methods needed for the library access
/// in the .inc.h files is the boost::python class wrappers
/// the inc.cpp elements must be bundled in the namespace ngl{
/// the .inc.h elements are just the python code as the MODULE element
/// is already wrapped in the namespace
#include "Colour.inc.cpp"
#include "Matrix.inc.cpp"
#include "Quaternion.inc.cpp"
#include "Material.inc.cpp"
#include "Transformation.inc.cpp"
#include "TransformStack.inc.cpp"
#include "BezierCurve.inc.cpp"
#include "Random.inc.cpp"
#include "ShaderLib.inc.cpp"
#include "AbstractMesh.inc.cpp"
#include "Text.inc.cpp"
#include "Vec4.inc.cpp"
#include "Vec3.inc.cpp"
#include "Vec2.inc.cpp"
#include "VertexArrayObject.inc.cpp"

namespace ngl
{
  // create a python module
  BOOST_PYTHON_MODULE(PyNGL)
  {
    #include "../python/Colour.inc.h"
    #include "../python/Vec4.inc.h"
    #include "../python/Matrix.inc.h"
    #include "../python/Quaternion.inc.h"
    #include "../python/BBox.inc.h"
    #include "../python/Camera.inc.h"
    #include "../python/VAOPrimitives.inc.h"
    #include "../python/Light.inc.h"
    #include "../python/Material.inc.h"
    #include "../python/AbstractMesh.inc.h"
    #include "../python/Obj.inc.h"
    #include "../python/ShaderLib.inc.h"
    #include "../python/Transformation.inc.h"
    #include "../python/TransformStack.inc.h"
    #include "../python/Texture.inc.h"
    #include "../python/BezierCurve.inc.h"
    #include "../python/PathCamera.inc.h"
    #include "../python/NCCABinMesh.inc.h"
    #include "../python/SpotLight.inc.h"
    #include "../python/Random.inc.h"
    #include "../python/NCCAPointBake.inc.h"
    #include "../python/NGLInit.inc.h"
    #include "../python/Shader.inc.h"
    #include "../python/ShaderProgram.inc.h"
		#include "../python/Plane.inc.h"
    #include "../python/Text.inc.h"
    #include "../python/VertexArrayObject.inc.h"
    #include "../python/Vec3.inc.h"
    #include "../python/Vec2.inc.h"
    #include "../python/CreateCoreGLContext.inc.h"

  };

} // end ngl namespace
