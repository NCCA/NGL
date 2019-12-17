#!/usr/bin/python

import unittest
import pyngl
import ctypes

# Note all pyngl types use internal fuzzy float equality operators

class TestVec4(unittest.TestCase):
  def testdefaultCtor(self):
    test=pyngl.Vec4()
    result=pyngl.Vec4(0.0,0.0,0.0,1.0)         
    self.assertEqual( test,result)

  def testSubscript(self) :
    test=pyngl.Vec4(1.0,2.0,3.0,4.0)
    self.assertEqual(test[0],1.0)
    self.assertEqual(test[1],2.0)
    self.assertEqual(test[2],3.0)
    self.assertEqual(test[3],4.0)

  def testFloatCtor(self) :
    test=pyngl.Vec4(1.0,2.0,3.0,4.0)
    result=pyngl.Vec4(1.0,2.0,3.0,4.0)
    self.assertTrue(test==result)

  def testAssignOperator(self) :
    test=pyngl.Vec4(1.0,2.0,3.0,4.0)
    result=test
    self.assertTrue(test==result)

  def testDotProduct(self) :
    a=pyngl.Vec4(1.0,2.0,3.0);
    b=pyngl.Vec4(4.0,5.0,6.0);
    self.assertEqual(a.dot(b),32.0);

  def testNull(self) :
    test=pyngl.Vec4(1,2,4)
    test.null()
    self.assertTrue(test==pyngl.Vec4.zero())

  def testNormalize(self) :
    test=pyngl.Vec4(22.3,0.5,10.0)
    test.normalize() 
    result=pyngl.Vec4(0.912266,0.0204544,0.409088)
    self.assertTrue(test==result)  
    self.assertEqual(test,result)

  def testInner(self) :
    a=pyngl.Vec4(1,2,3)
    b=pyngl.Vec4(3,4,5)
    self.assertEqual(a.inner(b),26.0)

  def testOuter(self) :
    a=pyngl.Vec4(1.0,2.0,3.0,4.0)
    b=pyngl.Vec4(5.0,6.0,7.0,8.0)
    outer=a.outer(b)
    result=pyngl.Mat4(5,6,7,8,10,12,14,16,15,18,21,24,20,24,28,32)
    self.assertTrue(outer==result)

  def testLength(self) :
    a=pyngl.Vec4(22.0,1.0,32.0)
    self.assertAlmostEqual(a.length(),38.845,delta=0.001)

  def testLengthSquared(self) :
    a=pyngl.Vec4(22.0,1.0,32.0)
    self.assertAlmostEqual(a.lengthSquared(),1509.0,delta=0.001)


  def testCross1(self) :
    a=pyngl.Vec4.up()
    b=pyngl.Vec4.left()
    c=a.cross(b)
    # alas in is a reserved work in python so we use inV
    self.assertTrue(c==pyngl.Vec4.inV())

  def testCross2(self) :
    a=pyngl.Vec4.up()
    b=pyngl.Vec4.left()
    c=pyngl.Vec4()
    c.cross(a,b)
    # alas in is a reserved work in python so we use inV
    self.assertTrue(c==pyngl.Vec4.inV())

  def testSizeof(self):
    test=pyngl.Vec4()
    self.assertTrue( test.sizeof()==4*ctypes.sizeof(ctypes.c_float))


if __name__ == '__main__':
     unittest.main()
