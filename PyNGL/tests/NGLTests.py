#!/usr/bin/env python
from __future__ import print_function
import unittest
import sys
if sys.version_info.major == 3 :
  import pyngl3 as pyngl
else :
  import pyngl

import argparse


def setup():
  import glfw
  if not glfw.init():
    print("error with glfw init")
    sys.exit()
  glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 4)
  glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 1)
  glfw.window_hint(glfw.OPENGL_FORWARD_COMPAT, True)
  glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)  
  window = glfw.create_window(640, 480, "", None, None)
  if not window:
    glfw.terminate()
    return

  # Make the window's context current
  glfw.make_context_current(window)
  pyngl.NGLInit.instance().setCommunicationMode(pyngl.CommunicationMode.STDOUT);



def tearDown():
  print("teardown module")
  glfw.Terminate()


if __name__ == '__main__':
  
  parser = argparse.ArgumentParser(description='Modify render parameters')
  parser.add_argument('--noGL', '-g' , action='count',help="don't run GL based tests mainly for CI")
  args = parser.parse_args()
  useGL=True
  if args.noGL :
    useGL = False 

  if useGL == True :
    setup()
    # gl only tests
    from ShaderLibTests import *
    #from VAOPrimitivesTests import *
  # non GL tests
  from Mat2Test import *
  from Mat3Test import *
  from Mat4Test import *
  from Vec2Test import *
  from Vec3Test import *
  from Vec4Test import *
  from ObjTest import *
  from UtilTest import *
  from RandomTest import *
  from QuaternionTest import *
  if len(sys.argv) > 1 :
    unittest.main(argv=sys.argv[1:])
  else :
    unittest.main()
  if useGL== True :
    tearDown()
