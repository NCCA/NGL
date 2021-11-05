#!/usr/bin/python
from __future__ import print_function
import sys
if sys.version_info.major == 3 :
  import pyngl as pyngl
else :
  import pyngl

import unittest
import os


class TestVAOPrimitives(unittest.TestCase):

  @classmethod
  def setUpClass(self) :
    self.meshes=[
    pyngl.teapot,pyngl.octahedron,pyngl.dodecahedron,
     pyngl.icosahedron,pyngl.tetrahedron,pyngl.football,pyngl.cube,
     pyngl.troll,pyngl.bunny,pyngl.dragon,pyngl.buddah
   ]


  def testInstance(self) :
    prim = pyngl.VAOPrimitives.instance()
    self.assertTrue(prim !=None)

  def testGetCreatedIDs(self) :
   prim = pyngl.VAOPrimitives.instance()
   for m in self.meshes :
     print(m)
     self.assertTrue(prim.getVAOFromName(m) != 0)  

  def testCheckCreated(self) :
    prim = pyngl.VAOPrimitives.instance()
    for m in self.meshes :
      print(m)
      vao=prim.getVAOFromName(m)
      vao.bind()
      self.assertTrue(vao.getBufferID(0) > 0)
      vao.unbind()

  def testCheckCreateSphere(self) :
    prim = pyngl.VAOPrimitives.instance()
    prim.createSphere('sphere',1.0,200)
    self.assertTrue(prim.getVAOFromName('sphere') !=None)


  def testCheckCreateLineGrid(self) :
    prim = pyngl.VAOPrimitives.instance()
    prim.createLineGrid('grid',100.0,100.0,1000)
    self.assertTrue(prim.getVAOFromName('grid') !=None)


  def testCreateTrianglePlane(self) :
    prim = pyngl.VAOPrimitives.instance()
    prim.createTrianglePlane('plane',100.0,100.0,1000,1000,pyngl.Vec3.up())
    self.assertTrue(prim.getVAOFromName('plane') !=None)

  def testCreateCylinder(self) :
    prim = pyngl.VAOPrimitives.instance()
    prim.createCylinder('cylinder',1.0,2.0,100,100)
    self.assertTrue(prim.getVAOFromName('cylinder') !=None)

  def testCreateTorus(self) :
    prim = pyngl.VAOPrimitives.instance()
    prim.createTorus('torus',1.0,2.0,100,100,True)
    self.assertTrue(prim.getVAOFromName('torus') !=None)

  def testCreateCone(self) :
    prim = pyngl.VAOPrimitives.instance()
    prim.createCone('cone',1.0,2.0,100,100)
    self.assertTrue(prim.getVAOFromName('cone') !=None)

  def testCreateCapsule(self) :
    prim = pyngl.VAOPrimitives.instance()
    prim.createCapsule('capsule',1.0,2.0,100)
    self.assertTrue(prim.getVAOFromName('capsule') !=None)

  # def testClear(self) :
  #  prim = pyngl.VAOPrimitives.instance()
  #  prim.clear()
  #  for m in self.meshes :
  #    self.assertFalse(prim.getVAOFromName(m) != None)



if __name__ == '__main__':
   unittest.main()
