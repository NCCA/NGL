#include <ngl/Mat4.h>
#include <ngl/Vec4.h>
#include <ngl/NGLStream.h>
#include <fstream>

/// Yes I know it's a global, but these are quick and dirty tests!
static std::ofstream gstream;


void removeCharFromStream(long _amount=1)
{
  // get rid of last ,
  long pos = gstream.tellp();
  gstream.seekp (pos-_amount);
}


void writeCtor(const std::string &_name,const ngl::Mat4 &_m)
{
  gstream<<"ngl::Mat4 "<<_name<<"(";
  for(int i=0; i<16; ++i)
    gstream<<_m.m_openGL[i]<<',';
  removeCharFromStream();
  gstream<<");\n";
}

void writeTest(const std::string &_name)
{
  static int test=0;
  gstream<<"Test "<<test++<<' '<<_name<<'\n';
}

int main(int argc, char **argv)
{
  std::string fname("testoutput.txt");
  if(argc == 2)
    fname=argv[1];
  gstream.open(fname.c_str(),std::ios::out);
  if (!gstream.is_open())
  {
    std::cerr<<"problems Opening File\n";
  }
  gstream<<"Testing Output for Mat4";

  {
    ngl::Mat4 test;
    writeTest("Test Ctor");
    writeCtor("result",test);
    writeTest("Calling NULL");
    test.null();
    writeCtor("result",test);
    writeTest("Calling identity");
    test.identity();
    writeCtor("result",test);

  }
  {
    ngl::Mat4 test(2.0f);
    writeTest("Testing float ident ctor m(2.0f)");
    writeCtor("result",test);
    ngl::Mat4 m2(test);
    writeTest("Testing copy ctor");
    writeCtor("result",m2);
    ngl::Mat4 m3=test;
    writeTest("Testing assignment operator");
    writeCtor("result",m3);


  }

  {
    ngl::Mat4 test;
    writeTest("test setAt");
    int value=0.0f;
    for(int y=0; y<4; ++y)
      for(int x=0; x<4; ++x)
          test.setAtXY(x,y,value++);
    writeCtor("result",test);


  }
  {
    ngl::Mat4 test;
    test.translate(1.0f,2.0f,3.0f);
    writeTest("test translate");
    writeCtor("result",test);
  }

  {
    ngl::Mat4 test;
    test.translate(1.0f,2.0f,3.0f);
    test.transpose();
    writeTest("test transpose");
    writeCtor("result",test);
  }

  {
    ngl::Mat4 test;
    test.scale(1.0f,2.0f,3.0f);
    test.transpose();
    writeTest("test scale");
    writeCtor("result",test);
  }
  {
    ngl::Mat4 test;
    test.rotateX(45.0f);
    writeTest("test roateX");
    writeCtor("result",test);
  }
  {
    ngl::Mat4 test;
    test.rotateY(25.0f);
    writeTest("test roateY");
    writeCtor("result",test);
  }

  {
    ngl::Mat4 test;
    test.rotateZ(-36.0f);
    writeTest("test roateZ");
    writeCtor("result",test);
  }
  {
    // test verified as 5 from wolfram alpha
    ngl::Mat4 test(1,0,0,0,0,2,2,0,0,-0.5,2,0,0,0,0,1);
    writeTest("test determinant");
    float det=test.determinant();
    gstream<<"float result="<<det<<";\n";
  }

  {
    // test verified as 5 from wolfram alpha
    ngl::Mat4 test(1,0,0,0,0,2,2,0,0,-0.5,2,0,0,0,0,1);
    writeTest("test determinant");
    float det=test.determinant();
    gstream<<"float result="<<det<<";\n";
  }

  {
    // test verified from wolfram alpha
    // 1,0,0,0,0,0.4, -0.4, 0 ,0 , 0.1 , 0.4 0 ,0,0,0,1
    ngl::Mat4 test(1,0,0,0,0,2,2,0,0,-0.5,2,0,0,0,0,1);
    writeTest("test inverse");
    ngl::Mat4 result=test.inverse();
    writeCtor("result",result);
  }

  {
    // test verified from wolfram alpha
    // 1,0,0,0,0,0.4, -0.4, 0 ,0 , 0.1 , 0.4 0 ,0,0,0,1
    ngl::Mat4 test(1,0,0,0,0,2,2,0,0,-0.5,2,0,0,0,0,1);
    writeTest("test adjacent");
    ngl::Mat4 result=test.Adjacent();
    writeCtor("result",result);
  }

  {
    ngl::Mat4 t1;
    ngl::Mat4 t2;
    t1.rotateX(45.0f);
    t2.rotateY(35.0f);
    writeTest("test adjacent()");
    ngl::Mat4 result=t1.Adjacent(t2);
    writeCtor("result",result);
  }


  {
    ngl::Mat4 t1;
    ngl::Vec4 v(2,1,2,1);
    t1.rotateX(45.0f);
    v=v*t1;
    writeTest("test Vec4*Mat4");
    gstream<<v<<'\n';
  }
  {
    ngl::Mat4 t1;
    ngl::Vec4 v(2,1,2,1);
    t1.rotateX(45.0f);
    v=t1*v;
    writeTest("test Mat4*Vec4");
    gstream<<v<<'\n';
  }
  {
    ngl::Mat4 t1;
    t1.euler(45.0f,0,-1,0);
    ngl::Mat4 t2;
    t2.rotateY(45.0f);
    writeTest("test euler");
    writeCtor("t1",t1);
    writeCtor("t2",t2);

  }
  {
    ngl::Mat4 t1;
    ngl::Mat4 t2;
    t1.rotateX(45.0f);
    t2.rotateY(35.0f);
    ngl::Mat4 test=t1*t2;
    writeTest("test Mat4*Mat4");
    writeCtor("result",test);
  }
  {
    ngl::Mat4 t1;
    ngl::Mat4 t2;
    t1.rotateX(45.0f);
    t2.rotateY(35.0f);
    t1*=t2;
    writeTest("test Mat4*equal");
    writeCtor("result",t1);
  }

  {
    ngl::Mat4 t1;
    ngl::Mat4 t2;
    t1.rotateX(45.0f);
    t2.rotateY(35.0f);
    ngl::Mat4 test=t1+t2;
    writeTest("test Mat4+Mat4");
    writeCtor("result",test);
  }
  {
    ngl::Mat4 t1;
    int value=0.0f;
    for(int y=0; y<4; ++y)
      for(int x=0; x<4; ++x)
          t1.setAtXY(x,y,value++);
    t1=t1*4.2f;
    writeTest("test Mat4xReal");
    writeCtor("result",t1);
  }
  {
    ngl::Mat4 t1;
    int value=0.0f;
    for(int y=0; y<4; ++y)
      for(int x=0; x<4; ++x)
          t1.setAtXY(x,y,value++);
    t1*=4.2f;
    writeTest("test Mat4xEqualReal");
    writeCtor("result",t1);
  }


}
