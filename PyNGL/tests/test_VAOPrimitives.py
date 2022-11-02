#!/usr/bin/env python
import io
import os
import sys
import unittest

import glfw
import pyngl


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


def tearDownModule() -> None:
    glfw.terminate()


class TestVAOPrimitives(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.meshes = [
            pyngl.teapot,
            pyngl.octahedron,
            pyngl.dodecahedron,
            pyngl.icosahedron,
            pyngl.tetrahedron,
            pyngl.football,
            pyngl.cube,
            pyngl.troll,
            pyngl.bunny,
            pyngl.dragon,
            pyngl.buddah,
        ]

    def testGetCreatedIDs(self):
        for m in self.meshes:
            self.assertTrue(pyngl.VAOPrimitives.getVAOFromName(m) != 0)

    def testCheckCreated(self):
        for m in self.meshes:
            vao = pyngl.VAOPrimitives.getVAOFromName(m)
            vao.bind()
            self.assertTrue(vao.getBufferID(0) > 0)
            vao.unbind()

    def testCheckCreateSphere(self):
        pyngl.VAOPrimitives.createSphere("sphere", 1.0, 200)
        self.assertTrue(pyngl.VAOPrimitives.getVAOFromName("sphere") != None)

    def testCheckCreateLineGrid(self):
        pyngl.VAOPrimitives.createLineGrid("grid", 100.0, 100.0, 1000)
        self.assertTrue(pyngl.VAOPrimitives.getVAOFromName("grid") != None)

    def testCreateTrianglePlane(self):
        pyngl.VAOPrimitives.createTrianglePlane(
            "plane", 100.0, 100.0, 1000, 1000, pyngl.Vec3.up()
        )
        self.assertTrue(pyngl.VAOPrimitives.getVAOFromName("plane") != None)

    def testCreateCylinder(self):
        pyngl.VAOPrimitives.createCylinder("cylinder", 1.0, 2.0, 100, 100)
        self.assertTrue(pyngl.VAOPrimitives.getVAOFromName("cylinder") != None)

    def testCreateTorus(self):
        pyngl.VAOPrimitives.createTorus("torus", 1.0, 2.0, 100, 100, True)
        self.assertTrue(pyngl.VAOPrimitives.getVAOFromName("torus") != None)

    def testCreateCone(self):
        pyngl.VAOPrimitives.createCone("cone", 1.0, 2.0, 100, 100)
        self.assertTrue(pyngl.VAOPrimitives.getVAOFromName("cone") != None)

    def testCreateCapsule(self):
        pyngl.VAOPrimitives.createCapsule("capsule", 1.0, 2.0, 100)
        self.assertTrue(pyngl.VAOPrimitives.getVAOFromName("capsule") != None)

    # def testClear(self) :
    #  prim = pyngl.VAOPrimitives.instance()
    #  prim.clear()
    #  for m in self.meshes :
    #    self.assertFalse(prim.getVAOFromName(m) != None)


if __name__ == "__main__":
    unittest.main()
