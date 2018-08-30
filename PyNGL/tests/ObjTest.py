#!/usr/bin/python

import unittest
import pyngl

# Note all pyngl types use internal fuzzy float equality operators

sourcedir='../../tests/files/'
validfiles=[sourcedir+'Triangle1.obj',
   sourcedir+'TriangleVertNormal.obj',
   sourcedir+'TriangleVertsOnly.obj',
   sourcedir+'TriangleVertsUV.obj',
   sourcedir+'Triangle3UV.obj',
   sourcedir+'TriMessedFormat.obj',
   sourcedir+'CubeNegativeIndex.obj']

invalidfiles=[sourcedir+'BrokenFloats.obj']

class TestObj(unittest.TestCase):

  def testOpenForReading(self) :
    for file in validfiles+invalidfiles :
      try :
        with open(file,'r') as f :
          self.assertTrue(True)
      except IOError :
          print file+' not found'
          self.assertTrue(False)

  def testDefaultCtor(self) :
    a=pyngl.Obj()
    self.assertEqual(a.getNumFaces(),0)
    self.assertEqual(a.getNumNormals(),0)
    self.assertEqual(a.getNumVerts(),0)
    self.assertEqual(a.getNumTexCords(),0)

  def testLoadValid(self) :
    a=pyngl.Obj()
    for file in validfiles :
      self.assertTrue(a.load(file,pyngl.CalcBB.True))
      self.assertTrue(a.isLoaded())

  def testLoadInvalidValid(self) :
    a=pyngl.Obj()
    for file in invalidfiles :
      self.assertFalse(a.load(file,pyngl.CalcBB.False))
      self.assertFalse(a.isLoaded())

  def testLoadFail(self) :
    a=pyngl.Obj()
    self.assertFalse(a.load("nothere.obj",pyngl.CalcBB.False))
    self.assertFalse(a.isLoaded())
  
  def testParseVertex(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle1.obj',pyngl.CalcBB.False))
    self.assertEqual(a.getNumVerts(),3)

  def testParseNormal(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle1.obj',pyngl.CalcBB.False))
    self.assertEqual(a.getNumNormals(),3)

  def testParseUV(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle1.obj',pyngl.CalcBB.False))
    self.assertEqual(a.getNumTexCords(),3)

  def testParseUV3(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle3UV.obj',pyngl.CalcBB.False))
    self.assertEqual(a.getNumTexCords(),3)


  def testSave(self) :
    a=pyngl.Obj() 
    a.addVertex(pyngl.Vec3(2.00000,0.00000,0.000000))
    a.addVertex(pyngl.Vec3(0.0000,4.0000,0.000000))
    a.addVertex(pyngl.Vec3(-2.00000,0.000000,0.00000))
    f=pyngl.Face();
    f.m_vert.push_back(0);
    f.m_vert.push_back(1);
    f.m_vert.push_back(2);
    a.addFace(f);
    a.save("faceOnly.obj");



if __name__ == '__main__':
     unittest.main()
