#include <ngl/Mat4.h>
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


void printCtor(const std::string &_name,const ngl::Mat4 &_m)
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
    ngl::Mat4 m1;
    writeTest("Test Ctor");
    printCtor("result",m1);
    writeTest("Calling NULL");
    m1.null();
    printCtor("result",m1);
    writeTest("Calling identity");
    m1.identity();
    printCtor("result",m1);

  }
  {
    ngl::Mat4 m1(2.0f);
    writeTest("Testing float ident ctor m(2.0f)");
    printCtor("result",m1);
    ngl::Mat4 m2(m1);
    writeTest("Testing copy ctor");
    printCtor("result",m2);
    ngl::Mat4 m3=m1;
    writeTest("Testing assignment operator");
    printCtor("result",m3);


  }




}
