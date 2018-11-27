#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

PYBIND11_MAKE_OPAQUE(std::vector<uint32_t, std::allocator<uint32_t>>);


namespace ngl
{
namespace py = pybind11;

using uintList = std::vector<uint32_t, std::allocator<uint32_t>>;



// each cpp file will have an init function to do the binding
// see http://pybind11.readthedocs.io/en/master/faq.html#how-can-i-reduce-the-build-time
extern void pyInitVec4(py::module & m);
extern void pyInitVec3(py::module & m);
extern void pyInitAABB(py::module & m);
extern void pyInitAbstractMesh(py::module & m);
extern void pyInitAbstractVAO(py::module & m);
extern void pyInitBBox(py::module & m);
extern void pyInitBezierCurve(py::module & m);
extern void pyInitCamera(py::module & m);
extern void pyInitColour(py::module & m);
extern void pyInitImage(py::module & m);
extern void pyInitLogger(py::module & m);
extern void pyInitVAOPrimitives(py::module & m);
extern void pyInitMat2(py::module & m);
extern void pyInitMat3(py::module & m);
extern void pyInitMat4(py::module & m);
extern void pyInitMaterial(py::module & m);
extern void pyInitMultiBufferVAO(py::module & m);
extern void pyInitNCCABinMesh(py::module & m);
extern void pyInitPointBake(py::module & m);
extern void pyInitNGLInit(py::module & m);
extern void pyInitObj(py::module & m);
extern void pyInitPlane(py::module & m);
extern void pyInitQuaternion(py::module & m);
extern void pyInitRandom(py::module & m);
extern void pyInitRibExport(py::module & m);
extern void pyInitShaderLib(py::module & m);
extern void pyInitSimpleIndexVAO(py::module & m);
extern void pyInitSimpleVAO(py::module & m);
extern void pyInitSpotlight(py::module & m);
extern void pyInitText(py::module & m);
extern void pyInitTexture(py::module & m);
extern void pyInitTransformation(py::module & m);
extern void pyInitUtils(py::module & m);
extern void pyInitVAOFactory(py::module & m);
extern void pyInitVec2(py::module & m);
extern void pyInitShader(py::module & m);
extern void pyInitShaderProgram(py::module & m);


PYBIND11_MODULE(pyngl,m)
{
//    py::module m("pyngl", "pyngl module ");
    m.doc()="pyngl module to use NGL in python";
    pyInitVec4(m);
    pyInitVec3(m);
    pyInitAABB(m);
    pyInitAbstractMesh(m);
    pyInitAbstractVAO(m);
    pyInitBBox(m);
    pyInitBezierCurve(m);
    pyInitImage(m);
    pyInitVAOPrimitives(m);
    pyInitMat2(m);
    pyInitMat3(m);
    pyInitMat4(m);
    pyInitMultiBufferVAO(m);
    pyInitNCCABinMesh(m);
    pyInitPointBake(m);
    pyInitNGLInit(m);
    pyInitObj(m);
    pyInitPlane(m);
    pyInitQuaternion(m);
    pyInitRandom(m);
    pyInitRibExport(m);
    pyInitShaderLib(m);
    pyInitShader(m);
    pyInitShaderProgram(m);
    pyInitSimpleIndexVAO(m);
    pyInitSimpleVAO(m);
    pyInitText(m);
    pyInitTexture(m);
    pyInitTransformation(m);
    pyInitUtils(m);
    pyInitVAOFactory(m);
    pyInitVec2(m);


    m.attr("nglColourShader")="nglColourShader";
    m.attr("nglDiffuseShader")="nglDiffuseShader";
    m.attr("nglCheckerShader")="nglCheckerShader";
    m.attr("simpleVAO")="simpleVAO";
    m.attr("multiBufferVAO")="multiBufferVAO";
    m.attr("simpleIndexVAO")="simpleIndexVAO";
    m.attr("teapot")="teapot";
    m.attr("octahedron")="octahedron";
    m.attr("dodecahedron")="dodecahedron";
    m.attr("icosahedron")="icosahedron";
    m.attr("tetrahedron")="tetrahedron";
    m.attr("football")="football";
    m.attr("cube")="cube";
    m.attr("troll")="troll";
    m.attr("bunny")="bunny";
    m.attr("dragon")="dragon";
    m.attr("buddah")="buddah";



    //return m.ptr();
}



}
