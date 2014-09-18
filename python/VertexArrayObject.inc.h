#ifndef __VERTEXARRAYOBJECT_INC_H__
#define __VERTEXARRAYOBJECT_INC_H__

// import the namespace for convenience
using namespace boost::python;
/// @note in the example below we only have a single ctor with a param
/// to get this to compile using boost::python we can't use .def and must
/// inline as shown in the class below

class_<VertexArrayObject, boost::noncopyable>("VertexArrayObject",no_init)
  .def("createVOA", &VertexArrayObject::createVOA, return_value_policy<reference_existing_object>()).staticmethod("createVOA")
  .def("bind",&VertexArrayObject::bind)
  .def("unbind",&VertexArrayObject::unbind)
  .def("removeVAO",&VertexArrayObject::removeVOA)
  .def("getID",&VertexArrayObject::getID)
  .def("isAllocated",&VertexArrayObject::isAllocated)
  .def("isBound",&VertexArrayObject::isBound)
  .def("setData",&VertexArrayObject::setData)
  .def("setIndexedData",&VertexArrayObject::setIndexedData)
  .def("setVertexAttributePointer",&VertexArrayObject::setVertexAttributePointer)
  .def("draw",drawN)
  .def("draw",drawE)
  .def("setNumIndices",&VertexArrayObject::setNumIndices)

;

#endif
