#!/usr/bin/python

import unittest
import pyngl
import os
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
      self.assertFalse(a.load(file))
      self.assertFalse(a.isLoaded())

  def testLoadFail(self) :
    a=pyngl.Obj()
    self.assertFalse(a.load("nothere.obj"))
    self.assertFalse(a.isLoaded())
  
  def testParseVertex(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle1.obj'))
    self.assertEqual(a.getNumVerts(),3)

  def testParseNormal(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle1.obj'))
    self.assertEqual(a.getNumNormals(),3)

  def testParseUV(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle1.obj'))
    self.assertEqual(a.getNumTexCords(),3)

  def testParseUV3(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle3UV.obj'))
    self.assertEqual(a.getNumTexCords(),3)
  
  def testCheckVerts(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle1.obj'))
    verts=a.getVertexList()
    self.assertTrue(verts[0]==pyngl.Vec3(2.0,0.0,0.0))
    self.assertTrue(verts[1]==pyngl.Vec3(0.0,4.0,0.0))
    self.assertTrue(verts[2]==pyngl.Vec3(-2.0,0.0,0.0))

  def testCheckNormals(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle1.obj'))
    normal=a.getNormalList()
    self.assertTrue(normal[0]==pyngl.Vec3(0.0,0.0,1.0))
    self.assertTrue(normal[1]==pyngl.Vec3(0.0,0.0,1.0))
    self.assertTrue(normal[2]==pyngl.Vec3(0.0,0.0,1.0))

  def testCheckUV(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'Triangle1.obj'))
    uv=a.getUVList()
    self.assertTrue(uv[0]==pyngl.Vec3(1.00000,0.00000,0.000000))
    self.assertTrue(uv[1]==pyngl.Vec3(0.5000,1.0000,0.000000))
    self.assertTrue(uv[2]==pyngl.Vec3(0.004399,0.008916,0.00000))

  def testCheckFaceVertOnly(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'TriangleVertsOnly.obj'))
    face=a.getFaceList()
    self.assertEqual(face[0].m_vert[0],0)
    self.assertEqual(face[0].m_vert[1],1)
    self.assertEqual(face[0].m_vert[2],2)

  def testCheckFaceVertNormal(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'TriangleVertNormal.obj'))
    face=a.getFaceList()
    self.assertEqual(face[0].m_vert[0],0)
    self.assertEqual(face[0].m_vert[1],1)
    self.assertEqual(face[0].m_vert[2],2)
    self.assertEqual(face[0].m_norm[0],0);
    self.assertEqual(face[0].m_norm[1],1);
    self.assertEqual(face[0].m_norm[2],2);

  def testCheckFaceVertUV(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'TriangleVertsUV.obj'))
    face=a.getFaceList()
    self.assertEqual(face[0].m_vert[0],0)
    self.assertEqual(face[0].m_vert[1],1)
    self.assertEqual(face[0].m_vert[2],2)
    self.assertEqual(face[0].m_uv[0],0);
    self.assertEqual(face[0].m_uv[1],1);
    self.assertEqual(face[0].m_uv[2],2);

  def testCheckFaceVertOnlyNegativeIndex(self) :
    a=pyngl.Obj()
    self.assertTrue(a.load(sourcedir+'CubeNegativeIndex.obj'))
    face=a.getFaceList()
    idx=0
    for i in range(0,len(face)) :
      self.assertEqual(face[i].m_vert[0],idx)
      self.assertEqual(face[i].m_vert[1],idx+1)
      self.assertEqual(face[i].m_vert[2],idx+2)
      self.assertEqual(face[i].m_vert[3],idx+3)
      idx+=4
      
  def testCheckFace(self) :
    a=pyngl.Obj(sourcedir+"Triangle1.obj")
    face=a.getFaceList()
    self.assertEqual(face[0].m_vert[0],0);
    self.assertEqual(face[0].m_vert[1],1);
    self.assertEqual(face[0].m_vert[2],2);

    self.assertEqual(face[0].m_norm[0],0);
    self.assertEqual(face[0].m_norm[1],1);
    self.assertEqual(face[0].m_norm[2],2);

    self.assertEqual(face[0].m_uv[0],0);
    self.assertEqual(face[0].m_uv[1],1);
    self.assertEqual(face[0].m_uv[2],2);  


  def testAddVertex(self) :
    a=pyngl.Obj()
    v=0.0
    for i in range(0,20) :
      a.addVertex(pyngl.Vec3(v,v,v))
      v=v+1.0
    verts=a.getVertexList()
    v=0.0
    for i in range(0,20) :
      self.assertTrue(verts[i]==pyngl.Vec3(v,v,v))
      v+=1.0

  def testAddNormal(self) :
    a=pyngl.Obj()
    v=0.0
    for i in range(0,20) :
      a.addNormal(pyngl.Vec3(v,v,v))
      v=v+1.0
    norm=a.getNormalList()
    v=0.0
    for i in range(0,20) :
      self.assertTrue(norm[i]==pyngl.Vec3(v,v,v))
      v+=1.0

  def testAddUV3(self) :
    a=pyngl.Obj()
    v=0.0
    for i in range(0,20) :
      a.addUV(pyngl.Vec3(v,v,v))
      v=v+1.0
    uv=a.getUVList()
    v=0.0
    for i in range(0,20) :
      self.assertTrue(uv[i]==pyngl.Vec3(v,v,v))
      v+=1.0

  def testAddUV2(self) :
    a=pyngl.Obj()
    v=0.0
    for i in range(0,20) :
      a.addUV(pyngl.Vec2(v,v))
      v=v+1.0
    uv=a.getUVList()
    v=0.0
    for i in range(0,20) :
      self.assertTrue(uv[i]==pyngl.Vec3(v,v,0))
      v+=1.0

  def testAddFace(self) :
    a=pyngl.Obj()
    f=pyngl.Face()
    f.m_vert.append(0)
    f.m_vert.append(1)
    f.m_vert.append(2)
    f.m_norm.append(0)
    f.m_norm.append(1)
    f.m_norm.append(2)
    f.m_uv.append(0)
    f.m_uv.append(1)
    f.m_uv.append(2)
    a.addFace(f)
    face=a.getFaceList()
    self.assertEqual(face[0].m_vert[0],0);
    self.assertEqual(face[0].m_vert[1],1);
    self.assertEqual(face[0].m_vert[2],2);

    self.assertEqual(face[0].m_norm[0],0);
    self.assertEqual(face[0].m_norm[1],1);
    self.assertEqual(face[0].m_norm[2],2);

    self.assertEqual(face[0].m_uv[0],0);
    self.assertEqual(face[0].m_uv[1],1);
    self.assertEqual(face[0].m_uv[2],2);

  def buildObj(self) :
    a=pyngl.Obj()
    a.addVertex(pyngl.Vec3(2.00000,0.00000,0.000000))
    a.addVertex(pyngl.Vec3(0.0000,4.0000,0.000000))
    a.addVertex(pyngl.Vec3(-2.00000,0.000000,0.000000))
    a.addUV(pyngl.Vec2(1.000000,0.000000))
    a.addUV(pyngl.Vec2(0.500000,1.000000))
    a.addUV(pyngl.Vec2(0.004399,0.008916))
    a.addNormal(pyngl.Vec3(0.000000,0.000000,1.000000))
    a.addNormal(pyngl.Vec3(0.000000,0.000000,1.000000))
    a.addNormal(pyngl.Vec3(0.000000,0.000000,1.000000))
    f=pyngl.Face()
    # f 1/1/1 2/2/2 3/3/3
    f.m_vert.append(0)
    f.m_vert.append(1)
    f.m_vert.append(2)
    f.m_uv.append(0)
    f.m_uv.append(1)
    f.m_uv.append(2)
    f.m_norm.append(0)
    f.m_norm.append(1)
    f.m_norm.append(2)
    a.addFace(f)
    return a

  def testBuildObj(self) :
    a=self.buildObj()
    face=a.getFaceList()
    self.assertEqual(face[0].m_vert[0],0)
    self.assertEqual(face[0].m_vert[1],1)
    self.assertEqual(face[0].m_vert[2],2)
    self.assertEqual(face[0].m_norm[0],0)
    self.assertEqual(face[0].m_norm[1],1)
    self.assertEqual(face[0].m_norm[2],2)
    self.assertEqual(face[0].m_uv[0],0)
    self.assertEqual(face[0].m_uv[1],1)
    self.assertEqual(face[0].m_uv[2],2)
    verts=a.getVertexList()
    self.assertTrue(verts[0]==pyngl.Vec3(2.00000,0.00000,0.000000))
    self.assertTrue(verts[1]==pyngl.Vec3(0.0000,4.0000,0.000000))
    self.assertTrue(verts[2]==pyngl.Vec3(-2.00000,0.000000,0.000000))
    norm=a.getNormalList()
    self.assertTrue(norm[0]==pyngl.Vec3(0.0,0.0,1.0))
    self.assertTrue(norm[1]==pyngl.Vec3(0.0,0.0,1.0 ))
    self.assertTrue(norm[2]==pyngl.Vec3(0.0,0.0,1.0 ))
    uv=a.getUVList();
    self.assertTrue(uv[0]==pyngl.Vec3(1.0,0.0,0.0))
    self.assertTrue(uv[1]==pyngl.Vec3(0.5,1.0,0.0))
    self.assertTrue(uv[2]==pyngl.Vec3(0.004399,0.008916,0.0)) 

  def testSaveVertsOnly(self) :
    a=pyngl.Obj() 
    a.addVertex(pyngl.Vec3(2.00000,0.00000,0.000000))
    a.addVertex(pyngl.Vec3(0.0000,4.0000,0.000000))
    a.addVertex(pyngl.Vec3(-2.00000,0.000000,0.00000))
    f=pyngl.Face()
    f.m_vert.append(0)
    f.m_vert.append(1)
    f.m_vert.append(2)
    a.addFace(f)
    a.save('faceOnly.obj')
    b=pyngl.Obj('faceOnly.obj')
    face=b.getFaceList()
    self.assertEqual(face[0].m_vert[0],0)
    self.assertEqual(face[0].m_vert[1],1)
    self.assertEqual(face[0].m_vert[2],2)
    verts=b.getVertexList()
    self.assertTrue(verts[0]==pyngl.Vec3(2.0,0.0,0.0))
    self.assertTrue(verts[1]==pyngl.Vec3(0.0,4.0,0.0))
    self.assertTrue(verts[2]==pyngl.Vec3(-2.0,0.0,0.0))
    os.remove('faceOnly.obj')

  def testSaveVertsUV(self) :
    a=pyngl.Obj() 
    a.addVertex(pyngl.Vec3(2.00000,0.00000,0.000000))
    a.addVertex(pyngl.Vec3(0.0000,4.0000,0.000000))
    a.addVertex(pyngl.Vec3(-2.00000,0.000000,0.00000))
    a.addUV(pyngl.Vec2(1.0,0.0))
    a.addUV(pyngl.Vec2(0.5,1.0))
    a.addUV(pyngl.Vec2(0.004399,0.008916))
    f=pyngl.Face()
    f.m_vert.append(0)
    f.m_vert.append(1)
    f.m_vert.append(2)
    f.m_uv.append(0)
    f.m_uv.append(1)
    f.m_uv.append(2)    
    a.addFace(f)
    a.save('faceUV.obj')
    
    b=pyngl.Obj('faceUV.obj')
    face=b.getFaceList()
    self.assertEqual(face[0].m_vert[0],0)
    self.assertEqual(face[0].m_vert[1],1)
    self.assertEqual(face[0].m_vert[2],2)
    verts=b.getVertexList()
    self.assertTrue(verts[0]==pyngl.Vec3(2.0,0.0,0.0))
    self.assertTrue(verts[1]==pyngl.Vec3(0.0,4.0,0.0))
    self.assertTrue(verts[2]==pyngl.Vec3(-2.0,0.0,0.0))
    uv=b.getUVList()
    self.assertTrue(uv[0]==pyngl.Vec3(1.0,0.0,0.0))
    self.assertTrue(uv[1]==pyngl.Vec3(0.5,1.0,0.0))
    self.assertTrue(uv[2]==pyngl.Vec3(0.004399,0.008916,0.0))
    os.remove('faceUV.obj')

  def saveVertsNormal(self) :
    a=pyngl.Obj() 
    a.addVertex(pyngl.Vec3(2.00000,0.00000,0.000000))
    a.addVertex(pyngl.Vec3(0.0000,4.0000,0.000000))
    a.addVertex(pyngl.Vec3(-2.00000,0.000000,0.00000))
    a.addNormal(pyngl.Vec3(0.0,0.0,1.0))
    a.addNormal(pyngl.Vec3(0.0,0.0,1.0))
    a.addNormal(pyngl.Vec3(0.0,0.0,1.0))
    f=pyngl.Face()
    f.m_vert.append(0)
    f.m_vert.append(1)
    f.m_vert.append(2)
    f.m_norm.append(0)
    f.m_norm.append(1)
    f.m_norm.append(2)    
    a.addFace(f)
    a.save('faceVertNormal.obj')
    
    b=pyngl.Obj('faceVertNormal.obj')
    face=b.getFaceList()
    self.assertEqual(face[0].m_vert[0],0)
    self.assertEqual(face[0].m_vert[1],1)
    self.assertEqual(face[0].m_vert[2],2)
    verts=b.getVertexList()
    self.assertTrue(verts[0]==pyngl.Vec3(2.0,0.0,0.0))
    self.assertTrue(verts[1]==pyngl.Vec3(0.0,4.0,0.0))
    self.assertTrue(verts[2]==pyngl.Vec3(-2.0,0.0,0.0))
    norm=b.getUVList()
    self.assertTrue(norm[0]==pyngl.Vec3(0.0,0.0,1.0))
    self.assertTrue(norm[1]==pyngl.Vec3(0.0,0.0,1.0))
    self.assertTrue(norm[2]==pyngl.Vec3(0.0,0.0,1.0))
    os.remove('faceVertNormal.obj')

  def testSaveObj(self) :
    a=pyngl.Obj() 
    a.addVertex(pyngl.Vec3(2.00000,0.00000,0.000000))
    a.addVertex(pyngl.Vec3(0.0000,4.0000,0.000000))
    a.addVertex(pyngl.Vec3(-2.00000,0.000000,0.00000))
    a.addNormal(pyngl.Vec3(0.0,0.0,1.0))
    a.addNormal(pyngl.Vec3(0.0,0.0,1.0))
    a.addNormal(pyngl.Vec3(0.0,0.0,1.0))
    a.addUV(pyngl.Vec2(1.0,0.0))
    a.addUV(pyngl.Vec2(0.5,1.0))
    a.addUV(pyngl.Vec2(0.004399,0.008916))

    f=pyngl.Face()
    f.m_vert.append(0)
    f.m_vert.append(1)
    f.m_vert.append(2)
    f.m_norm.append(0)
    f.m_norm.append(1)
    f.m_norm.append(2)
    f.m_uv.append(0)
    f.m_uv.append(1)
    f.m_uv.append(2)    
    
    a.addFace(f)
    a.save('test.obj')
    
    b=pyngl.Obj('test.obj')
    face=b.getFaceList()
    self.assertEqual(face[0].m_vert[0],0)
    self.assertEqual(face[0].m_vert[1],1)
    self.assertEqual(face[0].m_vert[2],2)
    verts=b.getVertexList()
    self.assertTrue(verts[0]==pyngl.Vec3(2.0,0.0,0.0))
    self.assertTrue(verts[1]==pyngl.Vec3(0.0,4.0,0.0))
    self.assertTrue(verts[2]==pyngl.Vec3(-2.0,0.0,0.0))
    norm=b.getNormalList()
    self.assertTrue(norm[0]==pyngl.Vec3(0.0,0.0,1.0))
    self.assertTrue(norm[1]==pyngl.Vec3(0.0,0.0,1.0))
    self.assertTrue(norm[2]==pyngl.Vec3(0.0,0.0,1.0))
    uv=b.getUVList()
    self.assertTrue(uv[0]==pyngl.Vec3(1.0,0.0,0.0))
    self.assertTrue(uv[1]==pyngl.Vec3(0.5,1.0,0.0))
    self.assertTrue(uv[2]==pyngl.Vec3(0.004399,0.008916,0.0))
    os.remove('test.obj')


  def testCopyCtor(self) :
    a=pyngl.Obj() 
    a.addVertex(pyngl.Vec3(2.00000,0.00000,0.000000))
    a.addVertex(pyngl.Vec3(0.0000,4.0000,0.000000))
    a.addVertex(pyngl.Vec3(-2.00000,0.000000,0.00000))
    a.addNormal(pyngl.Vec3(0.0,0.0,1.0))
    a.addNormal(pyngl.Vec3(0.0,0.0,1.0))
    a.addNormal(pyngl.Vec3(0.0,0.0,1.0))
    a.addUV(pyngl.Vec2(1.0,0.0))
    a.addUV(pyngl.Vec2(0.5,1.0))
    a.addUV(pyngl.Vec2(0.004399,0.008916))

    f=pyngl.Face()
    f.m_vert.append(0)
    f.m_vert.append(1)
    f.m_vert.append(2)
    f.m_norm.append(0)
    f.m_norm.append(1)
    f.m_norm.append(2)
    f.m_uv.append(0)
    f.m_uv.append(1)
    f.m_uv.append(2) 
    a.addFace(f)   
    b=a
    face=b.getFaceList()
    self.assertEqual(face[0].m_vert[0],0)
    self.assertEqual(face[0].m_vert[1],1)
    self.assertEqual(face[0].m_vert[2],2)
    verts=b.getVertexList()
    self.assertTrue(verts[0]==pyngl.Vec3(2.0,0.0,0.0))
    self.assertTrue(verts[1]==pyngl.Vec3(0.0,4.0,0.0))
    self.assertTrue(verts[2]==pyngl.Vec3(-2.0,0.0,0.0))
    norm=b.getNormalList()
    self.assertTrue(norm[0]==pyngl.Vec3(0.0,0.0,1.0))
    self.assertTrue(norm[1]==pyngl.Vec3(0.0,0.0,1.0))
    self.assertTrue(norm[2]==pyngl.Vec3(0.0,0.0,1.0))
    uv=b.getUVList()
    self.assertTrue(uv[0]==pyngl.Vec3(1.0,0.0,0.0))
    self.assertTrue(uv[1]==pyngl.Vec3(0.5,1.0,0.0))
    self.assertTrue(uv[2]==pyngl.Vec3(0.004399,0.008916,0.0))



if __name__ == '__main__':
     unittest.main()
