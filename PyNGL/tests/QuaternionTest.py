#!/usr/bin/python
import sys
if sys.version_info.major == 3 :
  import pyngl as pyngl
else :
  import pyngl

import unittest
import ctypes
import math

# Note all pyngl types use internal fuzzy float equality operators

class TestQuaternion(unittest.TestCase):
  def testdefaultCtor(self):
    test=pyngl.Quaternion()
    self.assertAlmostEqual( test.getS(),1.0)
    self.assertAlmostEqual( test.getX(),0.0)
    self.assertAlmostEqual( test.getY(),0.0)
    self.assertAlmostEqual( test.getZ(),0.0)

  def testUserCtor(self):
    test=pyngl.Quaternion(0.2,0.0,1.0,0.0)
    self.assertAlmostEqual( test.getS(),0.2)
    self.assertAlmostEqual( test.getX(),0.0)
    self.assertAlmostEqual( test.getY(),1.0)
    self.assertAlmostEqual( test.getZ(),0.0)

  def testAddition(self):
    q1=pyngl.Quaternion(0.5,1.0,0.0,0.0)
    q2=pyngl.Quaternion(0.2,0.0,1.0,0.0)
    res=q1+q2
    self.assertAlmostEqual( res.getS(),0.7)
    self.assertAlmostEqual( res.getX(),1.0)
    self.assertAlmostEqual( res.getY(),1.0)
    self.assertAlmostEqual( res.getZ(),0.0)

  def testAdditionEqual(self):
    q1=pyngl.Quaternion(0.5,1.0,0.0,0.0)
    q2=pyngl.Quaternion(0.2,0.0,1.0,0.0)
    q1+=q2
    self.assertAlmostEqual( q1.getS(),0.7)
    self.assertAlmostEqual( q1.getX(),1.0)
    self.assertAlmostEqual( q1.getY(),1.0)
    self.assertAlmostEqual( q1.getZ(),0.0)

  def testSubtract(self):
    q1=pyngl.Quaternion(0.5,1.0,1.0,0.0)
    q2=pyngl.Quaternion(0.2,1.0,1.0,0.0)
    res=q1-q2
    self.assertAlmostEqual( res.getS(),0.3)
    self.assertAlmostEqual( res.getX(),0.0)
    self.assertAlmostEqual( res.getY(),0.0)
    self.assertAlmostEqual( res.getZ(),0.0)

  def testSubtractionEqual(self):
    q1=pyngl.Quaternion(0.5,1.0,1.0,0.0)
    q2=pyngl.Quaternion(0.2,1.0,1.0,0.0)
    q1-=q2
    self.assertAlmostEqual( q1.getS(),0.3)
    self.assertAlmostEqual( q1.getX(),0.0)
    self.assertAlmostEqual( q1.getY(),0.0)
    self.assertAlmostEqual( q1.getZ(),0.0)



  def testMultiplyQuat(self):
    q1=pyngl.Quaternion(-math.sin(math.pi),3.0,4.0,3.0)
    q2=pyngl.Quaternion(4.0,3.9,-1.0,-3.0)
    res=q1*q2
    self.assertAlmostEqual( res.getS(),1.3,delta=0.001)
    self.assertAlmostEqual( res.getX(),3.0,delta=0.001)
    self.assertAlmostEqual( res.getY(),36.7,delta=0.001)
    self.assertAlmostEqual( res.getZ(),-6.60,delta=0.001)

  def testMultiplyEqualQuat(self):
    q1=pyngl.Quaternion(-math.sin(math.pi),3.0,4.0,3.0)
    q2=pyngl.Quaternion(4.0,3.9,-1.0,-3.0)
    q1*=q2
    self.assertAlmostEqual( q1.getS(),1.3,delta=0.001)
    self.assertAlmostEqual( q1.getX(),3.0,delta=0.001)
    self.assertAlmostEqual( q1.getY(),36.7,delta=0.001)
    self.assertAlmostEqual( q1.getZ(),-6.60,delta=0.001)


  def testMagnitude(self):
    q1=pyngl.Quaternion(1.3,3.0,36.7,-6.6)
    self.assertAlmostEqual(q1.magnitude(),37.4381,delta=0.01)

  def testNormalise(self):
    q1=pyngl.Quaternion(1.3,3.0,36.7,-6.6)
    q1.normalise()
    self.assertAlmostEqual( q1.getS(),0.0347298,delta=0.001)
    self.assertAlmostEqual( q1.getX(),0.0801457,delta=0.001)
    self.assertAlmostEqual( q1.getY(),0.98045,delta=0.001)
    self.assertAlmostEqual( q1.getZ(),-0.176321,delta=0.001)

  def testConjugate(self):
    q1=pyngl.Quaternion(1.3,3.0,36.7,-6.6)
    q1=q1.conjugate()
    self.assertAlmostEqual( q1.getS(),1.3,delta=0.001)
    self.assertAlmostEqual( q1.getX(),-3.0,delta=0.001)
    self.assertAlmostEqual( q1.getY(),-36.7,delta=0.001)
    self.assertAlmostEqual( q1.getZ(),6.6,delta=0.001)

  def testInverse(self):
    q1=pyngl.Quaternion(1.3,-3.0,-36.7,6.6)
    q1=q1.inverse()
    self.assertAlmostEqual( q1.getS(),0.000927816,delta=0.01)
    self.assertAlmostEqual( q1.getX(),0.00214111,delta=0.01)
    self.assertAlmostEqual( q1.getY(),0.026193,delta=0.01)
    self.assertAlmostEqual( q1.getZ(),0.00471045,delta=0.01)


if __name__ == '__main__':
     unittest.main()
