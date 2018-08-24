#!/usr/bin/python

import unittest
import pyngl

# Note all pyngl types use internal fuzzy float equality operators

class TestVec3(unittest.TestCase):
  def testdefaultCtor(self):
    test=pyngl.Vec3()
    result=pyngl.Vec3(0.0,0.0,0.0)         
    self.assertEqual( test,result)

  def testDotProduct(self) :
    a=pyngl.Vec3(1.0,2.0,3.0);
    b=pyngl.Vec3(4.0,5.0,6.0);
    self.assertEqual(a.dot(b),32.0);

  def testNull(self) :
    test=pyngl.Vec3(1,2,4)
    test.null()
    self.assertTrue(test==pyngl.Vec3.zero())

  def testNormalize(self) :
    test=pyngl.Vec3(22.3,0.5,10.0)
    test.normalize() 
    result=pyngl.Vec3(0.912266,0.0204544,0.409088)
    self.assertTrue(test==result)  
    self.assertEqual(test,result)

  def testInner(self) :
    a=pyngl.Vec3(1,2,3)
    b=pyngl.Vec3(3,4,5)
    self.assertEqual(a.inner(b),26.0)

  def testOuter(self) :
    a=pyngl.Vec3(1.0,2.0,3.0)
    b=pyngl.Vec3(3.0,4.0,5.0)
    outer=a.outer(b)
    result=pyngl.Mat3(3,4,5,6,8,10,9,12,15)
    self.assertTrue(outer==result)

  def testLength(self) :
    a=pyngl.Vec3(22.0,1.0,32.0)
    self.assertAlmostEqual(a.length(),38.845,delta=0.001)

  def testLengthSquared(self) :
    a=pyngl.Vec3(22.0,1.0,32.0)
    self.assertAlmostEqual(a.lengthSquared(),1509.0,delta=0.001)


  def testCross1(self) :
    a=pyngl.Vec3.up()
    b=pyngl.Vec3.left()
    c=a.cross(b)
    # alas in is a reserved work in python so we use inV
    self.assertTrue(c==pyngl.Vec3.inV())

  def testCross2(self) :
    a=pyngl.Vec3.up()
    b=pyngl.Vec3.left()
    c=pyngl.Vec3()
    c.cross(a,b)
    # alas in is a reserved work in python so we use inV
    self.assertTrue(c==pyngl.Vec3.inV())

  def testSubscipt(self) :
    test=pyngl.Vec3(1,2,3)
    self.assertAlmostEqual(test[0],1.0)
    self.assertAlmostEqual(test[1],2.0)
    self.assertAlmostEqual(test[2],3.0)

  def testFloatCtor(self) :
    test=pyngl.Vec3(1.0,2.0,3.0)
    result=pyngl.Vec3(1.0,2.0,3.0)
    self.assertEqual(test,result)

  def testAssignOperator(self) :
    test=pyngl.Vec3(1.0,2.0,3.0)
    copy=test
    result=pyngl.Vec3(1.0,2.0,3.0)
    self.assertEqual(test,result)

if __name__ == '__main__':
     unittest.main()
