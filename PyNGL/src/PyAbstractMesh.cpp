#include "PyBindIncludes.h"
#include "AbstractMesh.h"
#include <vector>
namespace py = pybind11;


namespace ngl
{


void pyInitAbstractMesh(py::module & m)
{

  py::class_<AbstractMesh>(m, "AbstractMesh")
      .def("drawBBox", &AbstractMesh::drawBBox)
      .def("draw", &AbstractMesh::draw)
      .def("loadTexture", &AbstractMesh::loadTexture)
      .def("scale", &AbstractMesh::scale)
      .def("calcDimensions", &AbstractMesh::calcDimensions)
      .def("calcBoundingSphere",&AbstractMesh::calcBoundingSphere)
      .def("createVAO", &AbstractMesh::createVAO)
      .def("getTextureID",&AbstractMesh::getTextureID)
      .def("mapVAOVerts", &AbstractMesh::mapVAOVerts)
      .def("unMapVAO", &AbstractMesh::unMapVAO)
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
      .value("TRUE",AbstractMesh::CalcBB::True )
      .value("FALSE",AbstractMesh::CalcBB::False)
    ;
  py::enum_<AbstractMesh::ResetVAO>(m, "ResetVAO")
      .value("TRUE",AbstractMesh::ResetVAO::True )
      .value("FALSE",AbstractMesh::ResetVAO::False)
    ;
  py::class_<Face>(m, "Face")
    .def(py::init<>())
    .def(py::init<const Face &>())
    .def_readwrite("m_vert",&Face::m_vert)
    .def_readwrite("m_uv",&Face::m_uv)
    .def_readwrite("m_norm",&Face::m_norm)
    .def_readwrite("m_textureCoord",&Face::m_textureCoord)
    .def_readwrite("m_normals",&Face::m_normals)
    ;
}




}

