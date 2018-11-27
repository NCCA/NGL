#!/usr/bin/python

import unittest
import pyngl
import os
# directory  with test files in (use same as C++ tests for ease)
sourcedir='../../tests/files/'

class TestShaderLib(unittest.TestCase):


  def testInstance(self) :    
    shader=pyngl.ShaderLib.instance()
    self.assertTrue(shader !=None)

  def testLoadShader(self) :
    shader=pyngl.ShaderLib.instance()
    self.assertTrue(shader.loadShader('Test',sourcedir+'vert.glsl',sourcedir+'frag.glsl',pyngl.ErrorExit.OFF))


  def testUse(self) :
    shader=pyngl.ShaderLib.instance()
    shader.use('Test')
    self.assertTrue(shader.getCurrentShaderName()=='Test')

  def testUseNull(self) :
    shader=pyngl.ShaderLib.instance()
    shader.use('Foo')
    self.assertTrue(shader.getCurrentShaderName()=='NULL')

  def testLoadErrorShader(self) :
    shader=pyngl.ShaderLib.instance()
    self.assertFalse(shader.loadShader('Test',sourcedir+'vertErr.glsl',sourcedir+'fragErr.glsl',pyngl.ErrorExit.OFF))

  def testloadParts(self) :
    shader=pyngl.ShaderLib.instance()
    shaderName='Test2'
    shader.createShaderProgram(shaderName,pyngl.ErrorExit.OFF)
    Vertex='Test2Vert'
    shader.attachShader( Vertex, pyngl.ShaderType.VERTEX, pyngl.ErrorExit.OFF)
    shader.loadShaderSource(Vertex,sourcedir+'vert.glsl')
    self.assertTrue(shader.compileShader(Vertex))

    Fragment='Test2Frag'
    shader.attachShader( Fragment, pyngl.ShaderType.FRAGMENT, pyngl.ErrorExit.OFF)
    shader.loadShaderSource(Fragment,sourcedir+'frag.glsl')
    self.assertTrue(shader.compileShader(Fragment))
    shader.attachShaderToProgram(shaderName,Vertex)
    shader.attachShaderToProgram(shaderName,Fragment)


    self.assertTrue(shader.linkProgramObject(shaderName))
    shader.use(shaderName)
    self.assertTrue(shader.getCurrentShaderName()==shaderName)


  def testLoadPartsFailVertex(self) :
    shader=pyngl.ShaderLib.instance()
    shaderName='Test3'
    shader.createShaderProgram(shaderName,pyngl.ErrorExit.OFF)
    Vertex='Test3Vert'
    shader.attachShader( Vertex, pyngl.ShaderType.VERTEX, pyngl.ErrorExit.OFF)
    shader.loadShaderSource(Vertex,sourcedir+'vertErr.glsl')
    self.assertFalse(shader.compileShader(Vertex))

  def testLoadPartsFailFragment(self) :
    shader=pyngl.ShaderLib.instance()
    shaderName='Test4'
    shader.createShaderProgram(shaderName,pyngl.ErrorExit.OFF)
    Fragment='Test4Frag'
    shader.attachShader( Fragment, pyngl.ShaderType.FRAGMENT, pyngl.ErrorExit.OFF)
    shader.loadShaderSource(Fragment,sourcedir+'fragErr.glsl')
    self.assertFalse(shader.compileShader(Fragment))

  def testFailLink(self) :
    shaderName='Test5'
    shader=pyngl.ShaderLib.instance()
    shader.createShaderProgram(shaderName,pyngl.ErrorExit.OFF)
    Vertex='Test5Vert'
    shader.attachShader( Vertex, pyngl.ShaderType.VERTEX,pyngl.ErrorExit.OFF )
    shader.loadShaderSource(Vertex,sourcedir+'vertLinkErr.glsl')
    self.assertTrue(shader.compileShader(Vertex))
    Fragment='Test5Frag'
    shader.attachShader( Fragment, pyngl.ShaderType.FRAGMENT ,pyngl.ErrorExit.OFF)
    shader.loadShaderSource(Fragment,sourcedir+'fragLinkErr.glsl')
    self.assertTrue(shader.compileShader(Fragment))
    shader.attachShaderToProgram(shaderName,Vertex)
    shader.attachShaderToProgram(shaderName,Fragment)
    self.assertFalse(shader.linkProgramObject(shaderName))

  def testSetUniform(self) :
    # note how the API changes here to be more pythonic as 
    # we have no pass by reference here
    shader=pyngl.ShaderLib.instance()
    shaderName='TestUniform'
    self.assertTrue(shader.loadShader(shaderName,sourcedir+'testUniformVertex.glsl',sourcedir+'testUniformFragment.glsl',pyngl.ErrorExit.OFF))
    shader.use(shaderName);
    shader.setUniform('testFloat',2.25)
    result=shader.getUniform1f('testFloat')
    
    self.assertAlmostEqual(result,2.25,delta=3)

    shader.setUniform("testVec2",0.5,2.0)
    resultVec2=shader.getUniformVec2("testVec2")
    self.assertAlmostEqual(resultVec2.m_x,0.5,delta=3)
    self.assertAlmostEqual(resultVec2.m_y,2.0,delta=3)

    x,y=shader.getUniform2f("testVec2")
    self.assertAlmostEqual(resultVec2.m_x,0.5,delta=3)
    self.assertAlmostEqual(resultVec2.m_y,2.0,delta=3)

    shader.setUniform('testVec3',0.5,2.0,-22.2)
    resultF1,resultF2,resultF3=shader.getUniform3f('testVec3')
    self.assertAlmostEqual(resultF1,0.5,delta=3)
    self.assertAlmostEqual(resultF2,2.0,delta=3)
    self.assertAlmostEqual(resultF3,-22.2,delta=3)
    resultVec3=shader.getUniformVec3('testVec3');
    self.assertAlmostEqual(resultVec3.m_x,0.5,delta=3)
    self.assertAlmostEqual(resultVec3.m_y,2.0,delta=3)
    self.assertAlmostEqual(resultVec3.m_z,-22.2,delta=3)

    shader.setUniform('testVec4',0.5,2.0,-22.2,1230.4)
    resultF1,resultF2,resultF3,resultF4=shader.getUniform4f('testVec4')
    self.assertAlmostEqual(resultF1,0.5,delta=3)
    self.assertAlmostEqual(resultF2,2.0,delta=3)
    self.assertAlmostEqual(resultF3,-22.2,delta=3)
    self.assertAlmostEqual(resultF4,1230.4,delta=3)

    resultVec4=shader.getUniformVec4('testVec4');
    self.assertAlmostEqual(resultVec4.m_x,0.5,delta=3)
    self.assertAlmostEqual(resultVec4.m_y,2.0,delta=3)
    self.assertAlmostEqual(resultVec4.m_z,-22.2,delta=3)
    self.assertAlmostEqual(resultVec4.m_w,1230.4,delta=3)
    shader.setUniform('testMat2',pyngl.Mat2())    
    result=shader.getUniformMat2('testMat2')
    self.assertTrue(result==pyngl.Mat2())

    shader.setUniform('testMat3',pyngl.Mat3())    
    result=shader.getUniformMat3('testMat3')
    self.assertTrue(result==pyngl.Mat3())

    shader.setUniform('testMat4',pyngl.Mat4())    
    result=shader.getUniformMat4('testMat4')
    self.assertTrue(result==pyngl.Mat4())

  def testEditShader(self) :
    shader = pyngl.ShaderLib.instance()
    shaderName='Edit'

    shader.createShaderProgram(shaderName,pyngl.ErrorExit.OFF)
    Vertex='EditVert'
    shader.attachShader( Vertex, pyngl.ShaderType.VERTEX ,pyngl.ErrorExit.OFF)
    shader.loadShaderSource(Vertex,sourcedir+'EditVert.glsl')
    self.assertTrue(shader.editShader(Vertex,'@breakMe','1.0'))
    self.assertTrue(shader.editShader(Vertex,'@numLights','2'))
    self.assertTrue(shader.compileShader(Vertex))
    Fragment='EditFrag'
    shader.attachShader( Fragment, pyngl.ShaderType.FRAGMENT,pyngl.ErrorExit.OFF )
    shader.loadShaderSource(Fragment,sourcedir+'EditFrag.glsl')
    self.assertTrue(shader.editShader(Fragment,'@numLights','2'))
    self.assertTrue(shader.compileShader(Fragment))
    shader.attachShaderToProgram(shaderName,Vertex);
    shader.attachShaderToProgram(shaderName,Fragment);
    self.assertTrue(shader.linkProgramObject(shaderName))
    shader.use(shaderName)
    self.assertTrue(shader.getCurrentShaderName()==shaderName);
    # Now re-edit
    shader.resetEdits(Vertex);
    shader.resetEdits(Fragment);
    self.assertTrue(shader.editShader(Vertex,'@numLights','5'))
    self.assertTrue(shader.editShader(Vertex,'@breakMe','1.0'))
    self.assertTrue(shader.editShader(Fragment,'@numLights','5'))
    self.assertTrue(shader.compileShader(Vertex))
    self.assertTrue(shader.compileShader(Fragment))
    self.assertTrue(shader.linkProgramObject(shaderName));
   



if __name__ == '__main__':
     unittest.main()
