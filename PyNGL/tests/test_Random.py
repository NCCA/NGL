#!/usr/bin/env python
import ctypes
import sys
import unittest

import pyngl as pyngl

# Note all pyngl types use internal fuzzy float equality operators

class TestRandom(unittest.TestCase):

  def testVec2(self):

    pyngl.Random.setSeed()
    v=pyngl.Random.getRandomVec2()
    self.assertTrue(v.m_x>=-1.0 and v.m_x<=1.0)
    self.assertTrue(v.m_y>=-1.0 and v.m_y<=1.0)

  def testVec3(self):

    pyngl.Random.setSeed()
    v=pyngl.Random.getRandomVec3()
    self.assertTrue(v.m_x>=-1.0 and v.m_x<=1.0)
    self.assertTrue(v.m_y>=-1.0 and v.m_y<=1.0)
    self.assertTrue(v.m_z>=-1.0 and v.m_z<=1.0)

  def testVec4(self):

    pyngl.Random.setSeed()
    v=pyngl.Random.getRandomVec4()
    self.assertTrue(v.m_x>=-1.0 and v.m_x<=1.0)
    self.assertTrue(v.m_y>=-1.0 and v.m_y<=1.0)
    self.assertTrue(v.m_z>=-1.0 and v.m_z<=1.0)
    self.assertTrue(v.m_w>=-1.0 and v.m_w<=1.0)

  def testPoint(self):

    pyngl.Random.setSeed()
    v=pyngl.Random.getRandomPoint(20,20,20)
    self.assertTrue(v.m_x>=-20.0 and v.m_x<=20.0)
    self.assertTrue(v.m_y>=-20.0 and v.m_y<=20.0)
    self.assertTrue(v.m_z>=-20.0 and v.m_z<=20.0)

  def testRandomNumber(self):

    pyngl.Random.setSeed()
    v=pyngl.Random.randomNumber()
    self.assertTrue(v>=-1.0 and v<=1.0)

  def testRandomNumberArg(self):

    pyngl.Random.setSeed()
    v=pyngl.Random.randomNumber(100)
    self.assertTrue(v>=-100.0 and v<=100.0)

  def testRandomPositiveNumber(self):

    pyngl.Random.setSeed()
    v=pyngl.Random.randomPositiveNumber()
    self.assertTrue(v>=0.0 and v<=1.0)

  def testRandomNumberPositiveArg(self):

    pyngl.Random.setSeed()
    v=pyngl.Random.randomPositiveNumber(100)
    self.assertTrue(v>=0.0 and v<=100.0)


if __name__ == '__main__':
     unittest.main()
