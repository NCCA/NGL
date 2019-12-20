#!/usr/bin/python
import sys
if sys.version_info.major == 3 :
  import pyngl3 as pyngl
else :
  import pyngl

import unittest
import ctypes
# Note all pyngl types use internal fuzzy float equality operators

class TestMat2(unittest.TestCase):
  def testdefaultCtor(self):
    test=pyngl.Mat2()
    result=pyngl.Mat2(1,0,0,1)         
    self.assertTrue( test==result)

  def testNull(self) :
    test=pyngl.Mat2()
    test.null()
    result=pyngl.Mat2(0.0)         
    self.assertTrue( test==result)

  def testIdentity(self) :
    test=pyngl.Mat2(1,2,3,4)
    test.identity()
    result=pyngl.Mat2()         
    self.assertTrue( test==result)

  def testFloatCtor(self) :
    test=pyngl.Mat2(2.0) 
    result=pyngl.Mat2(2.0,0.0,0.0,2.0)         
    self.assertTrue( test==result)

  def testAssignOperator(self) :
    test=pyngl.Mat2(2.0) 
    copy=test
    result=pyngl.Mat2(2.0,0.0,0.0,2.0)         
    self.assertTrue( copy==result)

  def testCopyCtor(self) :
    test=pyngl.Mat2(2.0) 
    copy=pyngl.Mat2(test)
    result=pyngl.Mat2(2.0,0.0,0.0,2.0)         
    self.assertTrue( copy==result)

  def testSizeof(self):
    test=pyngl.Mat2()
    self.assertTrue( test.sizeof()==4*ctypes.sizeof(ctypes.c_float))

  def testTranspose(self) :
    test=pyngl.Mat2(1,2,3,4)
    test.transpose()
    result=pyngl.Mat2(1,3,2,4)
    self.assertTrue(test == result)

  
  def testScale(self) :
    test=pyngl.Mat2()
    test.scale(1.0,2.0)
    result=pyngl.Mat2(1,0,0,2)
    self.assertTrue(test == result)


  def testMat2xMat2(self) :
    t1=pyngl.Mat2(1,2,3,4)
    t2=pyngl.Mat2(5,6,7,8)
    test=t1*t2
    result=pyngl.Mat2(19,22,43,50)
    self.assertTrue(test == result) 

  def testMat3xEquals(self) :
    test=pyngl.Mat2(1,2,3,4)
    t2=pyngl.Mat2(5,6,7,8)
    test*=t2
    result=pyngl.Mat2(19,22,43,50)
    self.assertTrue(test == result) 


  def testPlusEqual(self) :
    t1=pyngl.Mat2(1,2,3,4)
    t2=pyngl.Mat2(5,6,7,8)
    t1+=t2
    result=pyngl.Mat2(6,8,10,12)
    self.assertTrue(t1 == result) 

  def testPlus(self) :
    t1=pyngl.Mat2(1,2,3,4)
    t2=pyngl.Mat2(5,6,7,8)
    res=t1+t2
    result=pyngl.Mat2(6,8,10,12)
    self.assertTrue(res == result) 

  def testMat2xReal(self) :
    test=pyngl.Mat2(1,2,3,4)
    test=test*4.0
    result=pyngl.Mat2(4,8,12,16)
    self.assertTrue(test==result)

  def testMat3xReal(self) :
    test=pyngl.Mat2(1,2,3,4)
    test*=4.0
    result=pyngl.Mat2(4,8,12,16)
    self.assertTrue(test==result)


  def testVec2xMat2(self) :
    t1=pyngl.Mat2()
    test=pyngl.Vec2(2,1)
    test=test*t1;
    result=pyngl.Vec2(2,1)
    self.assertTrue(test==result)
 


if __name__ == '__main__':
     unittest.main()
