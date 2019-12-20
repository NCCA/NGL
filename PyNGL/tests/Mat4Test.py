#!/usr/bin/python
import sys 
if sys.version_info.major == 3 :
  import pyngl3 as pyngl
else :
  import pyngl

import unittest
import ctypes
# Note all pyngl types use internal fuzzy float equality operators

class TestMat4(unittest.TestCase):
  def testdefaultCtor(self):
    test=pyngl.Mat4()
    result=pyngl.Mat4(1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0)         
    self.assertTrue( test==result)

  def testNull(self) :
    test=pyngl.Mat4()
    test.null()
    result=pyngl.Mat4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)         
    self.assertTrue( test==result)

  def testIdentity(self) :
    test=pyngl.Mat4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16)
    test.identity()
    result=pyngl.Mat4(1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0)         
    self.assertTrue( test==result)

  def testFloatCtor(self) :
    test=pyngl.Mat4(2.0) 
    result=pyngl.Mat4(2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,1)         
    self.assertTrue( test==result)
    
  def testAssignOperator(self) :
    test=pyngl.Mat4(2.0) 
    copy=test
    result=pyngl.Mat4(2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,1)         
    self.assertTrue( copy==result)
  
  def testCopyCtor(self) :
    test=pyngl.Mat4(2.0) 
    copy=pyngl.Mat4(test)
    result=pyngl.Mat4(2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,1)         
    self.assertTrue( copy==result)

  def testSizeof(self):
    test=pyngl.Mat4()
    self.assertTrue( test.sizeof()==16*ctypes.sizeof(ctypes.c_float))

  def testSetAt(self) :
    test=pyngl.Mat4()
    value=0.0
    for y in range(0,4) :
      for x in range(0,4) :
        test.setAtXY(x,y,value)
        value+=1.0
    result=pyngl.Mat4(0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15)
    self.assertTrue(test==result)

  def testTranslate(self) :
    test=pyngl.Mat4()
    test.translate(1,2,3)
    result=pyngl.Mat4(1,0,0,0,0,1,0,0,0,0,1,0,1,2,3,1)
    self.assertTrue(test == result)

  def testTranspose(self) :
    test=pyngl.Mat4()
    test.translate(1,2,3)
    test.transpose()
    result=pyngl.Mat4(1,0,0,1,0,1,0,2,0,0,1,3,0,0,0,1)
    self.assertTrue(test == result)
  
  def testScale(self) :
    test=pyngl.Mat4()
    test.scale(1.0,2.0,3.0)
    result=pyngl.Mat4(1,0,0,0,0,2,0,0,0,0,3,0,0,0,0,1)
    self.assertTrue(test == result)
    
  def testrotateX(self) :
    test=pyngl.Mat4()
    test.rotateX(45.0)
    result=pyngl.Mat4(1,0,0,0,0,0.707107,0.707107,0,0,-0.707107,0.707107,0,0,0,0,1)
    self.assertTrue(test == result)

  def testrotateY(self) :
    test=pyngl.Mat4() 
    test.rotateY(25.0)
    result=pyngl.Mat4(0.906308,0,-0.422618,0,0,1,0,0,0.422618,0,0.906308,0,0,0,0,1)
    self.assertTrue(test == result)

  def testrotateZ(self) :
    test=pyngl.Mat4() 
    test.rotateZ(-36.0)
    result=pyngl.Mat4(0.809017,-0.587785,0,0,0.587785,0.809017,0,0,0,0,1,0,0,0,0,1)
    self.assertTrue(test == result)


  def testMat4xMat4(self) :
    t1=pyngl.Mat4()
    t2=pyngl.Mat4()
    t1.rotateX(45.0)
    t2.rotateY(35.0)
    test=t2*t1
    result=pyngl.Mat4(0.819152,0,-0.573577,0,0.40558,0.707107,0.579228,0,0.40558,-0.707107,0.579228,0,0,0,0,1)
    self.assertTrue(test == result) 
   
  def testMat4xEquals(self) :
    test=pyngl.Mat4()
    t2=pyngl.Mat4()
    test.rotateX(45.0)
    t2.rotateY(35.0)
    test*=t2
    result=pyngl.Mat4(0.819152,0.40558,-0.40558,0,0,0.707107,0.707107,0,0.573577,-0.579228,0.579228,0,0,0,0,1)
    self.assertTrue(test == result) 

  def testMat4xEquals2(self) :
    test=pyngl.Mat4()
    t2=pyngl.Mat4()
    test.rotateX(45.0)
    t2.rotateY(35.0)
    test*=t2
    r=pyngl.Mat4()
    r.rotateX(45.0)
    self.assertTrue(test == (r*t2)) 


  def testPlusEqual(self) :
    t1=pyngl.Mat4()
    t2=pyngl.Mat4()
    t1.rotateX(45.0)
    t2.rotateY(35.0)
    t1+=t2
    result=pyngl.Mat4(1.81915,0,-0.573577,0,0,1.70711,0.707107,0,0.573577,-0.707107,1.52626,0,0,0,0,2)
    self.assertTrue(t1 == result) 

  def testPlus(self) :
    t1=pyngl.Mat4()
    t2=pyngl.Mat4()
    t1.rotateX(45.0)
    t2.rotateY(35.0)
    res=t1+t2
    result=pyngl.Mat4(1.81915,0,-0.573577,0,0,1.70711,0.707107,0,0.573577,-0.707107,1.52626,0,0,0,0,2)
    self.assertTrue(res == result) 

  def testMat4xReal(self) :
    test=pyngl.Mat4()
    value=0.0
    for y in range(0,3) :
      for x in range(0,3) :
        test.setAtXY(x,y,value)
        value+=1.0
    test=test*4.2
    result=pyngl.Mat4(0,16.8,33.6,50.4,4.2,21,37.8,54.6,8.4,25.2,42,58.8,12.6,29.4,46.2,63)
    self.assertTrue(test==result)

  def testMat4xReal(self) :
    test=pyngl.Mat4()
    value=0.0
    for y in range(0,4) :
      for x in range(0,4) :
        test.setAtXY(x,y,value)
        value+=1.0
    test*=4.2
    result=pyngl.Mat4(0,16.8,33.6,50.4,4.2,21,37.8,54.6,8.4,25.2,42,58.8,12.6,29.4,46.2,63)
    self.assertTrue(test==result)


  def testDeterminant(self) :
    test=pyngl.Mat4(1,0,0,0,0,2,2,0,0,-0.5,2,0,0,0,0,1)
    det=test.determinant()
    self.assertEqual(det,5.0)


  def testInverse(self) :
    # test verified with matlab
    # 1,0,0,0,0,0.4, -0.4, 0 ,0 , 0.1 , 0.4 0 ,0,0,0,1
    test=pyngl.Mat4(1,0,0,0,0,2,2,0,0,-0.5,2,0,0,0,0,1)
    test=test.inverse()
    result=pyngl.Mat4(1,0,0,0,0,0.4,-0.4,0,0,0.1,0.4,0,0,0,0,1)
    self.assertTrue(test==result)


  def testAdjacent(self) :
    test=pyngl.Mat4(1,0,0,0,0,2,2,0,0,-0.5,2,0,0,0,0,1)
    test=test.adjacent()
    result=pyngl.Mat4(5,0,0,0,0,2,0.5,0,0,-2,2,0,0,0,0,5)
    self.assertTrue(test==result)

  def testAdjacentWithMat4(self) :
    t1=pyngl.Mat4()
    t2=pyngl.Mat4()
    t1.rotateX(45.0)
    t2.rotateY(35.0)
    test=t1.adjacent(t2)
    result=pyngl.Mat4(0.819152,0,-0.573577,0,0,1,0,0,0.573577,0,0.819152,0,0,0,0,1)
    self.assertTrue(test==result)

  def Vec4xMat4(self) :
    t1=pyngl.Mat4()
    test=pyngl.Vec4(2,1,2,1)
    t1.rotateX(45.0)
    test=test*t1
    result=pyngl.Vec4(2,2.12132,0.707107,1)
    self.assertTrue(test==result)

  def Mat4xVec4(self) :
    t1=pyngl.Mat4()
    test=pyngl.Vec4(2,1,2,1)
    t1.rotateX(45.0)
    test=t1*test
    result=pyngl.Vec4(2,-0.707107,2.12132,1)
    self.assertTrue(test==result)




if __name__ == '__main__':
     unittest.main()
