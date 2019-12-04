#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

#include "AbstractMesh.h"
#include <vector>
namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<uint32_t, std::allocator<uint32_t>>);


namespace ngl
{


void pyInitAbstractMesh(py::module & m)
{


  using VectorUInt = std::vector<uint32_t, std::allocator<uint32_t>>;

  py::class_<std::vector<uint32_t>>(m, "VectorUInt")
    .def(py::init<>())
    .def("push_back", (void (VectorUInt::*)(const uint32_t &)) &VectorUInt::push_back)
    .def("__iter__", [](std::vector<uint32_t> &v) {
            return py::make_iterator(v.begin(), v.end());
         }, py::keep_alive<0, 1>())
      .def("__getitem__", [](const VectorUInt &s, size_t i) {
                  if (i >= s.size()) throw py::index_error();
                  return s[i];
              })
      .def("__setitem__", [](VectorUInt &s, size_t i, float v) {
          if (i >= s.size()) throw py::index_error();
          s[i] = v;
      })
     .def("__len__",&VectorUInt::size)
      ;

  py::class_<AbstractMesh>(m, "AbstractMesh")
      .def("drawBBox", &AbstractMesh::drawBBox)
      .def("draw", &AbstractMesh::draw)
      .def("loadTexture", &AbstractMesh::loadTexture)
      .def("scale", &AbstractMesh::scale)
      .def("calcDimensions", &AbstractMesh::calcDimensions)
      .def("calcBoundingSphere",&AbstractMesh::calcBoundingSphere)
      .def("writeToRibSubdiv", &AbstractMesh::writeToRibSubdiv)
      .def("createVAO", &AbstractMesh::createVAO)
      .def("getTextureID",&AbstractMesh::getTextureID)
      .def("mapVAOVerts", &AbstractMesh::mapVAOVerts)
      .def("unMapVAO", &AbstractMesh::unMapVAO)
      //.def("getIndices", &AbstractMesh::getIndices)
      .def("saveNCCABinaryMesh", &AbstractMesh::saveNCCABinaryMesh)
      .def("getBBox", &AbstractMesh::getBBox)
      .def("getVertexList", &AbstractMesh::getVertexList)
      .def("getVertexAtIndex",&AbstractMesh::getVertexAtIndex)
      .def("getNormalList",&AbstractMesh::getNormalList)
      .def("getUVList",&AbstractMesh::getUVList)
      .def("getFaceList", &AbstractMesh::getFaceList)
      .def("getNumVerts",&AbstractMesh::getNumVerts)
      .def("getNumNormals",&AbstractMesh::getNumNormals)
      .def("getNumTexCords", &AbstractMesh::getNumTexCords)
      .def("getNumFaces", &AbstractMesh::getNumFaces)
      .def("getMeshSize",&AbstractMesh::getMeshSize)
      .def("getSphereCenter",&AbstractMesh::getSphereCenter)
      .def("getSphereRadius",&AbstractMesh::getSphereRadius)
      .def("getCenter",&AbstractMesh::getCenter)
      .def("isTriangular",&AbstractMesh::isTriangular)
      ;



  py::enum_<AbstractMesh::CalcBB>(m, "CalcBB")
      .value("True",AbstractMesh::CalcBB::True )
      .value("False",AbstractMesh::CalcBB::False)
    ;

  py::class_<Face>(m, "Face")
    .def(py::init<>())
    .def(py::init<const Face &>())
    .def_readwrite("m_vert",&Face::m_vert)
    .def_readwrite("m_uv",&Face::m_uv)
    .def_readwrite("m_norm",&Face::m_norm)
    .def_readwrite("m_numVerts",&Face::m_numVerts)
    .def_readwrite("m_textureCoord",&Face::m_textureCoord)
    .def_readwrite("m_normals",&Face::m_normals)
    ;
}




}

