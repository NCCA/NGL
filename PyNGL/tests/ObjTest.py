#!/usr/bin/python

import unittest
import pyngl

# Note all pyngl types use internal fuzzy float equality operators

sourcedir='../../tests/files/'
validfiles=[sourcedir+'Triangle1.obj',
   sourcedir+'TriangleVertNormal.obj',
   sourcedir+'TriangleVertsOnly.obj',
   sourcedir+'TriangleVertsUV.obj',
   sourcedir+'Triangle3UV.obj',
   sourcedir+'TriMessedFormat.obj',
   sourcedir+'CubeNegativeIndex.obj']

invalidfiles=[sourcedir+'BrokenFloats.obj']

class TestObj(unittest.TestCase):

  def testOpenForReading(self) :
    for file in validfiles+invalidfiles :
      try :
        with open(file,'r') as f :
          self.assertTrue(True)
      except IOError :
          print file+' not found'
          self.assertTrue(False)

  def testDefaultCtor(self) :
    a=pyngl.Obj()
    self.assertEqual(a.getNumFaces(),0)
    self.assertEqual(a.getNumNormals(),0)
    self.assertEqual(a.getNumVerts(),0)
    self.assertEqual(a.getNumTexCords(),0)


  def testLoadValid(self) :
    a=pyngl.Obj()
    for file in validfiles :
      self.assertTrue(a.load(file,pyngl.CalcBB.False))
      self.assertTrue(a.isLoaded())


if __name__ == '__main__':
     unittest.main()
