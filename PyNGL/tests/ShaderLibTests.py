#!/usr/bin/python

import unittest
import pyngl
import os
# Note all pyngl types use internal fuzzy float equality operators


class TestShaderLib(unittest.TestCase):


  def testInstance(self) :
    shader=pyngl.ShaderLib.instance()
    self.assertTrue(shader !=None)
    self.assertTrue(shader.getNumShaders()==8)




if __name__ == '__main__':
     unittest.main()
