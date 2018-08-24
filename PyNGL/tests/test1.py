#!/usr/bin/python

import pyngl

a=pyngl.Vec4(1.0,2.0,3.0)
tx=pyngl.Transformation()
tx.setRotation(45.0,23.0,12.0)
print a*tx.getMatrix()
print tx.getMatrix()*a