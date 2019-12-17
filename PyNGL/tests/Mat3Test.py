#!/usr/bin/python

import unittest
import pyngl
import ctypes
# Note all pyngl types use internal fuzzy float equality operators

class TestMat3(unittest.TestCase):
  def testdefaultCtor(self):
    test=pyngl.Mat3()
    result=pyngl.Mat3(1,0,0,0,1,0,0,0,1)         
    self.assertTrue( test==result)

  def testNull(self) :
    test=pyngl.Mat3()
    test.null()
    result=pyngl.Mat3(0,0,0,0,0,0,0,0,0)         
    self.assertTrue( test==result)

  def testIdentity(self) :
    test=pyngl.Mat3(1,2,3,4,5,6,7,8,9)
    test.identity()
    result=pyngl.Mat3(1,0,0,0,1,0,0,0,1)         
    self.assertTrue( test==result)

  def testFloatCtor(self) :
    test=pyngl.Mat3(2.0) 
    result=pyngl.Mat3(2,0,0,0,2,0,0,0,2)         
    self.assertTrue( test==result)
    
  def testAssignOperator(self) :
    test=pyngl.Mat3(2.0) 
    copy=test
    result=pyngl.Mat3(2,0,0,0,2,0,0,0,2)         
    self.assertTrue( copy==result)
  
  def testCopyCtor(self) :
    test=pyngl.Mat3(2.0) 
    copy=pyngl.Mat3(test)
    result=pyngl.Mat3(2,0,0,0,2,0,0,0,2)         
    self.assertTrue( copy==result)

  def testSizeof(self):
    test=pyngl.Mat3()
    self.assertTrue( test.sizeof()==9*ctypes.sizeof(ctypes.c_float))

  def testSetAt(self) :
    test=pyngl.Mat3()
    value=0.0
    for y in range(0,3) :
      for x in range(0,3) :
        test.setAtXY(x,y,value)
        value+=1.0
    result=pyngl.Mat3(0,3,6,1,4,7,2,5,8)
    self.assertTrue(test==result)

  def testTranspose(self) :
    test=pyngl.Mat3(1,2,3,4,5,6,7,8,9)
    test.transpose()
    result=pyngl.Mat3(1,4,7,2,5,8,3,6,9)
    self.assertTrue(test == result)
  
  def testScale(self) :
    test=pyngl.Mat3()
    test.scale(1.0,2.0,3.0)
    result=pyngl.Mat3(1,0,0,0,2,0,0,0,3)
    self.assertTrue(test == result)
    
  def testrotateX(self) :
    test=pyngl.Mat3()
    test.rotateX(45.0)
    result=pyngl.Mat3(1,0,0,0,0.707107,0.707107,0,-0.707107,0.707107)
    self.assertTrue(test == result)

  def testrotateY(self) :
    test=pyngl.Mat3() 
    test.rotateY(25.0)
    result=pyngl.Mat3(0.906308,0,-0.422618,0,1,0,0.422618,0,0.906308)
    self.assertTrue(test == result)

  def testrotateZ(self) :
    test=pyngl.Mat3() 
    test.rotateZ(-36.0)
    result=pyngl.Mat3(0.809017,-0.587785,0,0.587785,0.809017,0,0,0,1)
    self.assertTrue(test == result)


  def testMat3xMat3(self) :
    t1=pyngl.Mat3()
    t2=pyngl.Mat3()
    t1.rotateX(45.0)
    t2.rotateY(35.0)
    test=t1*t2
    result=pyngl.Mat3(0.819152,0,-0.573577,0.40558,0.707107,0.579228,0.40558,-0.707107,0.579228)
    self.assertTrue(test == result) 
   
  def testMat3xEquals(self) :
    test=pyngl.Mat3()
    t2=pyngl.Mat3()
    test.rotateX(45.0)
    t2.rotateY(35.0)
    test*=t2
    result=pyngl.Mat3(0.819152,0.40558,-0.40558,0,0.707107,0.707107,0.573577,-0.579228,0.579228)
    self.assertTrue(test == result) 

  def testMat3xEquals2(self) :
    test=pyngl.Mat3()
    t2=pyngl.Mat3()
    test.rotateX(45.0)
    t2.rotateY(35.0)
    test*=t2
    r=pyngl.Mat3()
    r.rotateX(45.0)
    self.assertTrue(test == (t2*r)) 


  def testPlusEqual(self) :
    t1=pyngl.Mat3()
    t2=pyngl.Mat3()
    t1.rotateX(45.0)
    t2.rotateY(35.0)
    t1+=t2
    result=pyngl.Mat3(1.81915,0,-0.573577,0,1.70711,0.707107,0.573577,-0.707107,1.52626)
    self.assertTrue(t1 == result) 

  def testPlus(self) :
    t1=pyngl.Mat3()
    t2=pyngl.Mat3()
    t1.rotateX(45.0)
    t2.rotateY(35.0)
    res=t1+t2
    result=pyngl.Mat3(1.81915,0,-0.573577,0,1.70711,0.707107,0.573577,-0.707107,1.52626)
    self.assertTrue(res == result) 

  def testMat3xReal(self) :
    test=pyngl.Mat3()
    value=0.0
    for y in range(0,3) :
      for x in range(0,3) :
        test.setAtXY(x,y,value)
        value+=1.0
    test=test*4.2
    result=pyngl.Mat3(0,12.599999427795,25.199998855591,4.199999809265,16.799999237061,29.399997711182,8.399999618530,21.000000000000,33.599998474121)
    self.assertTrue(test==result)

  def testMat3xReal(self) :
    test=pyngl.Mat3()
    value=0.0
    for y in range(0,3) :
      for x in range(0,3) :
        test.setAtXY(x,y,value)
        value+=1.0
    test*=4.2
    result=pyngl.Mat3(0,12.599999427795,25.199998855591,4.199999809265,16.799999237061,29.399997711182,8.399999618530,21.000000000000,33.599998474121)
    self.assertTrue(test==result)


  def testDeterminant(self) :
    test=pyngl.Mat3(1,0,0,0,2,2,0,-0.5,2)
    det=test.determinant()
    self.assertEqual(det,5.0)


  def testInverse(self) :
    # test verified with matlab
    # 1,0,0,0,0,0.4, -0.4, 0 ,0 , 0.1 , 0.4 0 ,0,0,0,1
    test=pyngl.Mat3(1,0,0,0,2,2,0,-0.5,2)
    test=test.inverse()
    result=pyngl.Mat3(1.0 ,0.0,0.0,0.0,0.4 ,0.1,0.0,-0.4,0.4)
    self.assertTrue(test==result)


  def testVec3xMat3(self) :
    t1=pyngl.Mat3()
    t1.rotateX(45.0)
    test=pyngl.Vec3(2,1,2)
    test=test*t1;
    result=pyngl.Vec3(2,-0.707107,2.12132)
    self.assertTrue(test==result)

 


if __name__ == '__main__':
     unittest.main()
