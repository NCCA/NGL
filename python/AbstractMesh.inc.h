#ifndef __ABSTRACTMESH_INC_H__
#define __ABSTRACTMESH_INC_H__

// import the namespace for convenience
using namespace boost::python;
// now we define a python class for the code
// above

class_<AbstractMesh , boost::noncopyable >("AbstractMesh", no_init)
    /// we have to define an init method for
    /// each possible version available in the header
    // prototype the methods
    .def("createVAO", &AbstractMesh::createVAO)
    .def("drawBBox", &AbstractMesh::drawBBox)
    .def("draw", &AbstractMesh::draw)
    .def("saveNCCABinaryMesh", &AbstractMesh::saveNCCABinaryMesh)

    .def("loadTexture", &AbstractMesh::loadTexture)
    .def("scale", &AbstractMesh::scale)
    .def("calcDimensions", &AbstractMesh::calcDimensions)
    .def("writeToRibSubdiv", &AbstractMesh::writeToRibSubdiv)
    .def("getTextureID", &AbstractMesh::getTextureID)
    //.def("mapVAOVerts", &AbstractMesh::mapVAOVerts,return_value_policy<reference_existing_object>())
    .def("unMapVAO", &AbstractMesh::unMapVAO)

   // .def("getIndices", &AbstractMesh::getIndices)
    .def("getBBox", &AbstractMesh::getBBox,return_value_policy<reference_existing_object>())
		.def("getVertexList", &AbstractMesh::getVertexListPY)
	  .def("getNormalList", &AbstractMesh::getNormalListPY)
	  .def("getTextureCordList", &AbstractMesh::getTextureCordListPY)
	  //.def("getFaceList", &AbstractMesh::getFaceListPY)

//  .def("getVertexAtIndex", &AbstractMesh::getVertexAtIndex)
    .def("getNumVerts", &AbstractMesh::getNumVerts)
    .def("getNumNormals", &AbstractMesh::getNumNormals)
    .def("getNumTexCords", &AbstractMesh::getNumTexCords)
    .def("getNumFaces", &AbstractMesh::getNumFaces)
		.def("getSphereCenter", &AbstractMesh::getSphereCenter)
		.def("getSphereRadius", &AbstractMesh::getSphereRadius)
		.def("getCenter", &AbstractMesh::getCenter)

    ;

#endif


