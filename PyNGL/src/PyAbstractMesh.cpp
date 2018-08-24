#include <pybind11/pybind11.h>

#include "AbstractMesh.h"
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
      //.def("getTextureCordList",&AbstractMesh::getTextureCordList)
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

}

}
