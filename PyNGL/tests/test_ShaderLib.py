#!/usr/bin/env python
import io
import os
import sys
import unittest

import glfw
import pyngl

# directory  with test files in (use same as C++ tests for ease)
sourcedir = "../../tests/files/"


def setUpModule():
    if not glfw.init():
        print("error with glfw init")
        sys.exit()
    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 4)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 1)
    glfw.window_hint(glfw.OPENGL_FORWARD_COMPAT, True)
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)
    window = glfw.create_window(640, 480, "", None, None)
    if not window:
        glfw.terminate()

    # Make the window's context current
    glfw.make_context_current(window)
    pyngl.NGLInit.initialize()
    suppress_text = io.StringIO()
    sys.stdout = suppress_text


def tearDownModule() -> None:
    glfw.terminate()
    sys.stdout = sys.__stdout__


class TestShaderLib(unittest.TestCase):
    def testLoadShader(self):
        self.assertTrue(
            pyngl.ShaderLib.loadShader(
                "Test",
                sourcedir + "vert.glsl",
                sourcedir + "frag.glsl",
                pyngl.ErrorExit.OFF,
            )
        )

    def testUse(self):
        pyngl.ShaderLib.use("Test")
        self.assertTrue(pyngl.ShaderLib.getCurrentShaderName() == "Test")

    def testUseNull(self):
        pyngl.ShaderLib.use("unknown")
        self.assertTrue(pyngl.ShaderLib.getCurrentShaderName() == "NULL")

    def testLoadErrorShader(self):
        self.assertFalse(
            pyngl.ShaderLib.loadShader(
                "Test",
                sourcedir + "vertErr.glsl",
                sourcedir + "fragErr.glsl",
                pyngl.ErrorExit.OFF,
            )
        )

    def testloadParts(self):
        shaderName = "Test2"
        pyngl.ShaderLib.createShaderProgram(shaderName, pyngl.ErrorExit.OFF)
        Vertex = "Test2Vert"
        pyngl.ShaderLib.attachShader(
            Vertex, pyngl.ShaderType.VERTEX, pyngl.ErrorExit.OFF
        )
        pyngl.ShaderLib.loadShaderSource(Vertex, sourcedir + "vert.glsl")
        self.assertTrue(pyngl.ShaderLib.compileShader(Vertex))

        Fragment = "Test2Frag"
        pyngl.ShaderLib.attachShader(
            Fragment, pyngl.ShaderType.FRAGMENT, pyngl.ErrorExit.OFF
        )
        pyngl.ShaderLib.loadShaderSource(Fragment, sourcedir + "frag.glsl")
        self.assertTrue(pyngl.ShaderLib.compileShader(Fragment))
        pyngl.ShaderLib.attachShaderToProgram(shaderName, Vertex)
        pyngl.ShaderLib.attachShaderToProgram(shaderName, Fragment)

        self.assertTrue(pyngl.ShaderLib.linkProgramObject(shaderName))
        pyngl.ShaderLib.use(shaderName)
        self.assertTrue(pyngl.ShaderLib.getCurrentShaderName() == shaderName)

    def testLoadPartsFailVertex(self):
        shaderName = "Test3"
        pyngl.ShaderLib.createShaderProgram(shaderName, pyngl.ErrorExit.OFF)
        Vertex = "Test3Vert"
        pyngl.ShaderLib.attachShader(
            Vertex, pyngl.ShaderType.VERTEX, pyngl.ErrorExit.OFF
        )
        pyngl.ShaderLib.loadShaderSource(Vertex, sourcedir + "vertErr.glsl")
        self.assertFalse(pyngl.ShaderLib.compileShader(Vertex))

    def testLoadPartsFailFragment(self):
        shaderName = "Test4"
        pyngl.ShaderLib.createShaderProgram(shaderName, pyngl.ErrorExit.OFF)
        Fragment = "Test4Frag"
        pyngl.ShaderLib.attachShader(
            Fragment, pyngl.ShaderType.FRAGMENT, pyngl.ErrorExit.OFF
        )
        pyngl.ShaderLib.loadShaderSource(Fragment, sourcedir + "fragErr.glsl")
        self.assertFalse(pyngl.ShaderLib.compileShader(Fragment))

    def testFailLink(self):
        shaderName = "Test5"
        pyngl.ShaderLib.createShaderProgram(shaderName, pyngl.ErrorExit.OFF)
        Vertex = "Test5Vert"
        pyngl.ShaderLib.attachShader(
            Vertex, pyngl.ShaderType.VERTEX, pyngl.ErrorExit.OFF
        )
        pyngl.ShaderLib.loadShaderSource(Vertex, sourcedir + "vertLinkErr.glsl")
        self.assertTrue(pyngl.ShaderLib.compileShader(Vertex))
        Fragment = "Test5Frag"
        pyngl.ShaderLib.attachShader(
            Fragment, pyngl.ShaderType.FRAGMENT, pyngl.ErrorExit.OFF
        )
        pyngl.ShaderLib.loadShaderSource(Fragment, sourcedir + "fragLinkErr.glsl")
        self.assertTrue(pyngl.ShaderLib.compileShader(Fragment))
        pyngl.ShaderLib.attachShaderToProgram(shaderName, Vertex)
        pyngl.ShaderLib.attachShaderToProgram(shaderName, Fragment)
        self.assertFalse(pyngl.ShaderLib.linkProgramObject(shaderName))

    def testSetUniform(self):
        # note how the API changes here to be more pythonic as
        # we have no pass by reference here
        shaderName = "TestUniform"
        self.assertTrue(
            pyngl.ShaderLib.loadShader(
                shaderName,
                sourcedir + "testUniformVertex.glsl",
                sourcedir + "testUniformFragment.glsl",
                pyngl.ErrorExit.OFF,
            )
        )
        pyngl.ShaderLib.use(shaderName)
        pyngl.ShaderLib.setUniform("testFloat", 2.25)
        result = pyngl.ShaderLib.getUniform1f("testFloat")

        self.assertAlmostEqual(result, 2.25, delta=3)

        pyngl.ShaderLib.setUniform("testVec2", 0.5, 2.0)
        resultVec2 = pyngl.ShaderLib.getUniformVec2("testVec2")
        self.assertAlmostEqual(resultVec2.m_x, 0.5, delta=3)
        self.assertAlmostEqual(resultVec2.m_y, 2.0, delta=3)

        x, y = pyngl.ShaderLib.getUniform2f("testVec2")
        self.assertAlmostEqual(resultVec2.m_x, 0.5, delta=3)
        self.assertAlmostEqual(resultVec2.m_y, 2.0, delta=3)

        pyngl.ShaderLib.setUniform("testVec3", 0.5, 2.0, -22.2)
        resultF1, resultF2, resultF3 = pyngl.ShaderLib.getUniform3f("testVec3")
        self.assertAlmostEqual(resultF1, 0.5, delta=3)
        self.assertAlmostEqual(resultF2, 2.0, delta=3)
        self.assertAlmostEqual(resultF3, -22.2, delta=3)
        resultVec3 = pyngl.ShaderLib.getUniformVec3("testVec3")
        self.assertAlmostEqual(resultVec3.m_x, 0.5, delta=3)
        self.assertAlmostEqual(resultVec3.m_y, 2.0, delta=3)
        self.assertAlmostEqual(resultVec3.m_z, -22.2, delta=3)

        pyngl.ShaderLib.setUniform("testVec4", 0.5, 2.0, -22.2, 1230.4)
        resultF1, resultF2, resultF3, resultF4 = pyngl.ShaderLib.getUniform4f(
            "testVec4"
        )
        self.assertAlmostEqual(resultF1, 0.5, delta=3)
        self.assertAlmostEqual(resultF2, 2.0, delta=3)
        self.assertAlmostEqual(resultF3, -22.2, delta=3)
        self.assertAlmostEqual(resultF4, 1230.4, delta=3)

        resultVec4 = pyngl.ShaderLib.getUniformVec4("testVec4")
        self.assertAlmostEqual(resultVec4.m_x, 0.5, delta=3)
        self.assertAlmostEqual(resultVec4.m_y, 2.0, delta=3)
        self.assertAlmostEqual(resultVec4.m_z, -22.2, delta=3)
        self.assertAlmostEqual(resultVec4.m_w, 1230.4, delta=3)
        pyngl.ShaderLib.setUniform("testMat2", pyngl.Mat2())
        result = pyngl.ShaderLib.getUniformMat2("testMat2")
        self.assertTrue(result == pyngl.Mat2())

        pyngl.ShaderLib.setUniform("testMat3", pyngl.Mat3())
        result = pyngl.ShaderLib.getUniformMat3("testMat3")
        self.assertTrue(result == pyngl.Mat3())

        pyngl.ShaderLib.setUniform("testMat4", pyngl.Mat4())
        result = pyngl.ShaderLib.getUniformMat4("testMat4")
        self.assertTrue(result == pyngl.Mat4())

    def testEditShader(self):
        shaderName = "Edit"

        pyngl.ShaderLib.createShaderProgram(shaderName, pyngl.ErrorExit.OFF)
        Vertex = "EditVert"
        pyngl.ShaderLib.attachShader(
            Vertex, pyngl.ShaderType.VERTEX, pyngl.ErrorExit.OFF
        )
        pyngl.ShaderLib.loadShaderSource(Vertex, sourcedir + "EditVert.glsl")
        self.assertTrue(pyngl.ShaderLib.editShader(Vertex, "@breakMe", "1.0"))
        self.assertTrue(pyngl.ShaderLib.editShader(Vertex, "@numLights", "2"))
        self.assertTrue(pyngl.ShaderLib.compileShader(Vertex))
        Fragment = "EditFrag"
        pyngl.ShaderLib.attachShader(
            Fragment, pyngl.ShaderType.FRAGMENT, pyngl.ErrorExit.OFF
        )
        pyngl.ShaderLib.loadShaderSource(Fragment, sourcedir + "EditFrag.glsl")
        self.assertTrue(pyngl.ShaderLib.editShader(Fragment, "@numLights", "2"))
        self.assertTrue(pyngl.ShaderLib.compileShader(Fragment))
        pyngl.ShaderLib.attachShaderToProgram(shaderName, Vertex)
        pyngl.ShaderLib.attachShaderToProgram(shaderName, Fragment)
        self.assertTrue(pyngl.ShaderLib.linkProgramObject(shaderName))
        pyngl.ShaderLib.use(shaderName)
        self.assertTrue(pyngl.ShaderLib.getCurrentShaderName() == shaderName)
        # Now re-edit
        pyngl.ShaderLib.resetEdits(Vertex)
        pyngl.ShaderLib.resetEdits(Fragment)
        self.assertTrue(pyngl.ShaderLib.editShader(Vertex, "@numLights", "5"))
        self.assertTrue(pyngl.ShaderLib.editShader(Vertex, "@breakMe", "1.0"))
        self.assertTrue(pyngl.ShaderLib.editShader(Fragment, "@numLights", "5"))
        self.assertTrue(pyngl.ShaderLib.compileShader(Vertex))
        self.assertTrue(pyngl.ShaderLib.compileShader(Fragment))
        self.assertTrue(pyngl.ShaderLib.linkProgramObject(shaderName))


if __name__ == "__main__":
    unittest.main()
