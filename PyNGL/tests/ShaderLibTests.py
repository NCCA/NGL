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
    self.assertTrue(shader.getNumShaders()==8)

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
    shader=pyngl.ShaderLib.instance()
    shaderName='TestUniform'
    self.assertTrue(shader.loadShader(shaderName,sourcedir+'testUniformVertex.glsl',sourcedir+'testUniformFragment.glsl',pyngl.ErrorExit.OFF))
    shader.use(shaderName);
    shader.setUniform('testFloat',2.25)
#    result=shader.getUniform('testFloat')
    
#    self.assertAlmostEqual(result,2.25)

    resultVec2=pyngl.Vec2()
    shader.getUniform("testVec2",resultVec2);
    self.assertAlmostEqual(resultVec2.m_x,0.5)
    self.assertAlmostEqual(resultVec2.m_y,2.0)



"""
    shader->setUniform("testVec2",0.5f,2.0f);
    float resultF1,resultF2;
    shader->getUniform("testVec2",resultF1,resultF2);
    EXPECT_FLOAT_EQ(resultF1,0.5f)<<"Test setting two floats x";
    EXPECT_FLOAT_EQ(resultF2,2.0f)<<"Test setting two floats y";
    ngl::Vec2 resultVec2;
    shader->getUniform("testVec2",resultVec2);
    EXPECT_FLOAT_EQ(resultVec2.m_x,0.5f)<<"Test getting from ngl::Vec2 m_x";
    EXPECT_FLOAT_EQ(resultVec2.m_y,2.0f)<<"Test getting from ngl::Vec2 m_y";;
    }
    {
    shader->setUniform("testVec3",0.5f,2.0f,-22.2f);
    ngl::Real resultF1,resultF2,resultF3;
    shader->getUniform("testVec3",resultF1,resultF2,resultF3);
    EXPECT_FLOAT_EQ(resultF1,0.5f)<<"test setting 3 floats x";
    EXPECT_FLOAT_EQ(resultF2,2.0f)<<"test setting 3 floats x";
    EXPECT_FLOAT_EQ(resultF3,-22.2f)<<"test setting 3 floats x";
    ngl::Vec3 resultVec3;
    shader->getUniform("testVec3",resultVec3);
    EXPECT_FLOAT_EQ(resultVec3.m_x,0.5f)<<"test getting ngl::Vec3 m_x";
    EXPECT_FLOAT_EQ(resultVec3.m_y,2.0f)<<"test getting ngl::Vec3 m_y";
    EXPECT_FLOAT_EQ(resultVec3.m_z,-22.2f)<<"test getting ngl::Vec3 m_z";
    }
    {
    shader->setUniform("testVec4",0.5f,2.0f,-22.2f,1230.4f);
    ngl::Real resultF1,resultF2,resultF3,resultF4;
    shader->getUniform("testVec4",resultF1,resultF2,resultF3,resultF4);
    EXPECT_FLOAT_EQ(resultF1,0.5f);
    EXPECT_FLOAT_EQ(resultF2,2.0f);
    EXPECT_FLOAT_EQ(resultF3,-22.2f);
    EXPECT_FLOAT_EQ(resultF4,1230.4f);
    ngl::Vec4 resultVec4;
    shader->getUniform("testVec4",resultVec4);
    EXPECT_FLOAT_EQ(resultVec4.m_x,0.5f);
    EXPECT_FLOAT_EQ(resultVec4.m_y,2.0f);
    EXPECT_FLOAT_EQ(resultVec4.m_z,-22.2f);
    EXPECT_FLOAT_EQ(resultVec4.m_w,1230.4f);
    }
    {
    shader->setUniform("testMat2",ngl::Mat2());
    ngl::Mat2 result;
    shader->getUniform("testMat2",result);
    EXPECT_TRUE(result==ngl::Mat2());
    }
    {
    shader->setUniform("testMat3",ngl::Mat3());
    ngl::Mat3 result;
    shader->getUniform("testMat3",result);
    EXPECT_TRUE(result==ngl::Mat3());
    }
    {
    shader->setUniform("testMat4",ngl::Mat4());
    ngl::Mat4 result;
    shader->getUniform("testMat4",result);
    EXPECT_TRUE(result==ngl::Mat4());
    }
"""




if __name__ == '__main__':
     unittest.main()
