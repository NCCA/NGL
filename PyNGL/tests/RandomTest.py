#!/usr/bin/python
import sys
if sys.version_info.major == 3 :
  import pyngl3 as pyngl
else :
  import pyngl

import unittest
import ctypes
# Note all pyngl types use internal fuzzy float equality operators

class TestRandom(unittest.TestCase):
  def testInstance(self):
    rng=pyngl.Random.instance()
    self.assertTrue( rng != None)

  def testVec2(self):
    rng=pyngl.Random.instance()
    rng.setSeed()
    v=rng.getRandomVec2()
    self.assertTrue(v.m_x>=-1.0 and v.m_x<=1.0)
    self.assertTrue(v.m_y>=-1.0 and v.m_y<=1.0)

  def testVec3(self):
    rng=pyngl.Random.instance()
    rng.setSeed()
    v=rng.getRandomVec3()
    self.assertTrue(v.m_x>=-1.0 and v.m_x<=1.0)
    self.assertTrue(v.m_y>=-1.0 and v.m_y<=1.0)
    self.assertTrue(v.m_z>=-1.0 and v.m_z<=1.0)

  def testVec4(self):
    rng=pyngl.Random.instance()
    rng.setSeed()
    v=rng.getRandomVec4()
    self.assertTrue(v.m_x>=-1.0 and v.m_x<=1.0)
    self.assertTrue(v.m_y>=-1.0 and v.m_y<=1.0)
    self.assertTrue(v.m_z>=-1.0 and v.m_z<=1.0)
    self.assertTrue(v.m_w>=-1.0 and v.m_w<=1.0)

  def testPoint(self):
    rng=pyngl.Random.instance()
    rng.setSeed()
    v=rng.getRandomPoint(20,20,20)
    self.assertTrue(v.m_x>=-20.0 and v.m_x<=20.0)
    self.assertTrue(v.m_y>=-20.0 and v.m_y<=20.0)
    self.assertTrue(v.m_z>=-20.0 and v.m_z<=20.0)

  def testRandomNumber(self):
    rng=pyngl.Random.instance()
    rng.setSeed()
    v=rng.randomNumber()
    self.assertTrue(v>=-1.0 and v<=1.0)

  def testRandomNumberArg(self):
    rng=pyngl.Random.instance()
    rng.setSeed()
    v=rng.randomNumber(100)
    self.assertTrue(v>=-100.0 and v<=100.0)

  def testRandomPositiveNumber(self):
    rng=pyngl.Random.instance()
    rng.setSeed()
    v=rng.randomPositiveNumber()
    self.assertTrue(v>=0.0 and v<=1.0)

  def testRandomNumberPositiveArg(self):
    rng=pyngl.Random.instance()
    rng.setSeed()
    v=rng.randomPositiveNumber(100)
    self.assertTrue(v>=0.0 and v<=100.0)


if __name__ == '__main__':
     unittest.main()
