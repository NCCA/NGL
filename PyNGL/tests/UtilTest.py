#!/usr/bin/python

import unittest
import pyngl

import imp
try:
    imp.find_module('glm')
    useGLM = True
    import glm
except ImportError:
    useGLM = False

# Note all pyngl types use internal fuzzy float equality operators

class TestUtil(unittest.TestCase):

  def glmToNGL(self,m) :
    return pyngl.Mat4(m[0][0],m[0][1],m[0][2],m[0][3],m[1][0],m[1][1],m[1][2],m[1][3],m[2][0],m[2][1],m[2][2],m[2][3],m[3][0],m[3][1],m[3][2],m[3][3])    

  if useGLM == True :
    def testPerspective(self) :
      fov=45.0
      near=0.02
      far=10.0
      aspect=1024.0/720.0
      perspNGL=pyngl.perspective(fov,aspect,near,far)
      perspGLM=glm.perspective(pyngl.radians(fov),aspect,near,far)
      self.assertTrue(self.glmToNGL(perspGLM)==perspNGL)
      
    def testPerspectiveFOV(self) :
      fov=45.0
      near=0.02
      far=10.0
      aspect=1024.0/720.0
      width=1024
      height=720
      perspNGL=pyngl.perspectiveFov(fov,width,height,near,far)
      perspGLM=glm.perspectiveFov(pyngl.radians(fov),width,height,near,far)
      self.assertTrue(self.glmToNGL(perspGLM)==perspNGL)

    def testInfinitePerspective(self) :
      fov=45.0
      near=0.02
      aspect=1024.0/720.0
      perspNGL=pyngl.infinitePerspective(fov,aspect,near)
      perspGLM=glm.infinitePerspective(pyngl.radians(fov),aspect,near)
      self.assertTrue(self.glmToNGL(perspGLM)==perspNGL)

    def testOrtho(self) :
      orthNGL= pyngl.ortho(-1.0, 1.0, -1.0,1.0,1.0,-1.0) 
      orthGLM= glm.ortho(-1.0, 1.0, -1.0,1.0,1.0,-1.0) 
      self.assertTrue(self.glmToNGL(orthGLM)==orthNGL);    

    def testOrtho2D(self) :
      orthNGL= pyngl.ortho(-1.0, 1.0, -1.0,1.0) 
      orthGLM= glm.ortho(  -1.0, 1.0, -1.0,1.0) 
      self.assertTrue(self.glmToNGL(orthGLM)==orthNGL)

    def testLookAt(self) :
      lookNGL=pyngl.lookAt(pyngl.Vec3(2.0,2.0,2.0),pyngl.Vec3(0,0,0),pyngl.Vec3(0,1.0,0))
      lookGLM=glm.lookAt(glm.vec3(2.0,2.0,2.0),glm.vec3(0.0,0.0,0.0),glm.vec3(0.0,1.0,0.0))
      self.assertTrue(self.glmToNGL(lookGLM)==lookNGL)

    def testFrustum(self) :
      frustumNGL=pyngl.frustum(-1.0,1.0,-1.0,1.0,1.0,-1.0) ;
      frustumGLM=glm.frustum(-1.0,1.0,-1.0,1.0,1.0,-1.0) ;
      self.assertTrue(self.glmToNGL(frustumGLM)==frustumNGL)
  
  def testRadians(self) :
    result=pyngl.radians(45.0)
    self.assertAlmostEqual(result,0.7853981633974483)

  def testDegrees(self) :
    result=pyngl.degrees(0.7853981633974483)
    self.assertAlmostEqual(result,45.0)

  def testCalcNormal1(self) :
    result= pyngl.calcNormal(pyngl.Vec3(-1.0,-1.0,0.0),pyngl.Vec3(0.0,0.0,0.0) ,pyngl.Vec3(1.0,-1.0,0.0))
    self.assertEqual(result,pyngl.Vec3(0.0,0.0,1.0)) 
  def testCalcNormal2(self) :
    result= pyngl.calcNormal(pyngl.Vec4(-1.0,-1.0,0.0,0.0),pyngl.Vec4(0.0,0.0,0.0,0.0) ,pyngl.Vec4(1.0,-1.0,0.0,0.0))
    self.assertEqual(result,pyngl.Vec3(0.0,0.0,1.0)) 

if __name__ == '__main__':
     unittest.main()
