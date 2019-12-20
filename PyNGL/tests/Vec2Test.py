#!/usr/bin/python
import sys
if sys.version_info.major == 3 :
  import pyngl3 as pyngl
else :
  import pyngl

import unittest
import ctypes

# Note all pyngl types use internal fuzzy float equality operators

class TestVec2(unittest.TestCase):
  def testdefaultCtor(self):
    test=pyngl.Vec2()
    result=pyngl.Vec2(0.0,0.0)         
    self.assertEqual( test,result)

  def testDotProduct(self) :
    a=pyngl.Vec2(1.0,2.0);
    b=pyngl.Vec2(4.0,5.0);
    self.assertEqual(a.dot(b),14.0);

  def testNull(self) :
    test=pyngl.Vec2(1,2)
    test.null()
    self.assertTrue(test==pyngl.Vec2.zero())

  def testNormalize(self) :
    test=pyngl.Vec2(22.3,0.5)
    test.normalize() 
    result=pyngl.Vec2(0.9997,0.0224)
    self.assertTrue(test==result)  
    self.assertEqual(test,result)


  def testLength(self) :
    a=pyngl.Vec2(22.0,1.0)
    self.assertAlmostEqual(a.length(),22.022,delta=0.001)

  def testLengthSquared(self) :
    a=pyngl.Vec2(22.0,1.0)
    self.assertAlmostEqual(a.lengthSquared(),485.0,delta=0.001)


  def testSubscipt(self) :
    test=pyngl.Vec2(1,2)
    self.assertAlmostEqual(test[0],1.0)
    self.assertAlmostEqual(test[1],2.0)

  def testFloatCtor(self) :
    test=pyngl.Vec2(1.0,2.0)
    result=pyngl.Vec2(1.0,2.0)
    self.assertEqual(test,result)

  def testAssignOperator(self) :
    test=pyngl.Vec2(1.0,2.0)
    copy=test
    result=pyngl.Vec2(1.0,2.0)
    self.assertEqual(test,result)

  def testAdd(self) :
    a=pyngl.Vec2(1.0,2.0)
    b=pyngl.Vec2(2.0,3.0)
    c=a+b
    self.assertAlmostEquals(c.m_x,3.0,delta=0.001)
    self.assertAlmostEquals(c.m_y,5.0,delta=0.001)

  def testAddEqual(self) :
    a=pyngl.Vec2(1.0,2.0)
    b=pyngl.Vec2(2.0,3.0)
    a+=b
    self.assertAlmostEquals(a.m_x,3.0,delta=0.001)
    self.assertAlmostEquals(a.m_y,5.0,delta=0.001)

  def testMinus(self) :
    a=pyngl.Vec2(1.0,2.0)
    b=pyngl.Vec2(2.0,3.0)
    c=a-b
    self.assertAlmostEquals(c.m_x,-1.0,delta=0.001)
    self.assertAlmostEquals(c.m_y,-1.0,delta=0.001)

  def testMinusEqual(self) :
    a=pyngl.Vec2(1.0,2.0)
    b=pyngl.Vec2(2.0,3.0)
    a-=b
    self.assertAlmostEquals(a.m_x,-1.0,delta=0.001)
    self.assertAlmostEquals(a.m_y,-1.0,delta=0.001)

  def testMultiplyFloat(self) :
    a=pyngl.Vec2(1.0,2.0)
    b=a*2.0
    self.assertAlmostEquals(b.m_x,2.0,delta=0.001)
    self.assertAlmostEquals(b.m_y,4.0,delta=0.001)

  def testMultiplyEqualFloat(self) :
    a=pyngl.Vec2(1.0,2.0)
    a*=2.0
    self.assertAlmostEquals(a.m_x,2.0,delta=0.001)
    self.assertAlmostEquals(a.m_y,4.0,delta=0.001)


  def testDivideFloat(self) :
    a=pyngl.Vec2(1.0,2.0)
    b=a/2.0
    self.assertAlmostEquals(b.m_x,0.5,delta=0.001)
    self.assertAlmostEquals(b.m_y,1.0,delta=0.001)

  def testDivideEqualFloat(self) :
    a=pyngl.Vec2(1.0,2.0)
    a/=2.0
    self.assertAlmostEquals(a.m_x,0.5,delta=0.001)
    self.assertAlmostEquals(a.m_y,1.0,delta=0.001)

  def testDivideVec(self) :
    a=pyngl.Vec2(1.0,2.0)
    b=pyngl.Vec2(2.0,2.0)
    c=a/b
    self.assertAlmostEquals(c.m_x,0.5,delta=0.001)
    self.assertAlmostEquals(c.m_y,1.0,delta=0.001)

  def testDivideEqualVec(self) :
    a=pyngl.Vec2(1.0,2.0)
    b=pyngl.Vec2(2.0,2.0)
    a/=b
    self.assertAlmostEquals(a.m_x,0.5,delta=0.001)
    self.assertAlmostEquals(a.m_y,1.0,delta=0.001)




  def testSizeof(self):
    test=pyngl.Vec2()
    self.assertTrue( test.sizeof()==2*ctypes.sizeof(ctypes.c_float))

if __name__ == '__main__':
     unittest.main()
