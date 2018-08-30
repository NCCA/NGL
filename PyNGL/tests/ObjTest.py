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
  
  def testCheckVerts(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle1.obj',pyngl.CalcBB.False))
    verts=a.getVertexList()
    self.assertTrue(verts[0]==pyngl.Vec3(2.0,0.0,0.0))
    self.assertTrue(verts[1]==pyngl.Vec3(0.0,4.0,0.0))
    self.assertTrue(verts[2]==pyngl.Vec3(-2.0,0.0,0.0))

  def testCheckNormals(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle1.obj',pyngl.CalcBB.False))
    normal=a.getNormalList()
    self.assertTrue(normal[0]==pyngl.Vec3(0.0,0.0,1.0))
    self.assertTrue(normal[1]==pyngl.Vec3(0.0,0.0,1.0))
    self.assertTrue(normal[2]==pyngl.Vec3(0.0,0.0,1.0))

  def testCheckUV(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle1.obj',pyngl.CalcBB.False))
    uv=a.getUVList()
    self.assertTrue(uv[0]==pyngl.Vec3(1.00000,0.00000,0.000000))
    self.assertTrue(uv[1]==pyngl.Vec3(0.5000,1.0000,0.000000))
    self.assertTrue(uv[2]==pyngl.Vec3(0.004399,0.008916,0.00000))

  def testCheckFaceVertOnly(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'TriangleVertsOnly.obj',pyngl.CalcBB.False))
    face=a.getFaceList()
    self.assertEqual(face[0].m_vert[0],0)
    self.assertEqual(face[0].m_vert[1],1)
    self.assertEqual(face[0].m_vert[2],2)

  def testCheckFaceVertNormal(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'TriangleVertNormal.obj',pyngl.CalcBB.False))
    face=a.getFaceList()
    self.assertEqual(face[0].m_vert[0],0)
    self.assertEqual(face[0].m_vert[1],1)
    self.assertEqual(face[0].m_vert[2],2)
    self.assertEqual(face[0].m_norm[0],0);
    self.assertEqual(face[0].m_norm[1],1);
    self.assertEqual(face[0].m_norm[2],2);

  def testCheckFaceVertUV(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'TriangleVertsUV.obj',pyngl.CalcBB.False))
    face=a.getFaceList()
    self.assertEqual(face[0].m_vert[0],0)
    self.assertEqual(face[0].m_vert[1],1)
    self.assertEqual(face[0].m_vert[2],2)
    self.assertEqual(face[0].m_uv[0],0);
    self.assertEqual(face[0].m_uv[1],1);
    self.assertEqual(face[0].m_uv[2],2);

  def testCheckFaceVertOnlyNegativeIndex(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'CubeNegativeIndex.obj',pyngl.CalcBB.False))
    face=a.getFaceList()
    idx=0
    for i in range(0,len(face)) :
      self.assertEqual(face[i].m_vert[0],idx)
      self.assertEqual(face[i].m_vert[1],idx+1)
      self.assertEqual(face[i].m_vert[2],idx+2)
      self.assertEqual(face[i].m_vert[3],idx+3)
      idx+=4
      


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
