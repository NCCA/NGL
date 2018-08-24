#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace ngl
{
namespace py = pybind11;
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
extern void pyInitLight(py::module & m);
extern void pyInitLogger(py::module & m);
extern void pyInitVAOPrimitives(py::module & m);
extern void pyInitMat3(py::module & m);
extern void pyInitMat4(py::module & m);
extern void pyInitMaterial(py::module & m);
extern void pyInitMultiBufferVAO(py::module & m);
extern void pyInitNCCABinMesh(py::module & m);
extern void pyInitPointBake(py::module & m);
extern void pyInitNGLInit(py::module & m);
extern void pyInitObj(py::module & m);
extern void pyInitPathCamera(py::module & m);
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


PYBIND11_PLUGIN(pyngl)
{
    py::module m("pyngl", "pyngl module ");


    pyInitVec4(m);
    pyInitVec3(m);
    pyInitAABB(m);
    pyInitAbstractMesh(m);
    pyInitAbstractVAO(m);
    pyInitBBox(m);
    pyInitBezierCurve(m);
    pyInitImage(m);
    pyInitVAOPrimitives(m);
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
    m.attr("nglToonShader")="nglToonShader";

    return m.ptr();
}



}
