#include <ngl/Transformation.h>
#include <ngl/Vec4.h>
#include <ngl/NGLStream.h>
#include <hayai/hayai.hpp>
#include <hayai/hayai_main.hpp>



struct TestTx
{
    void loadToShader()
    {
      auto t=m_tx.getMatrix();
    }
    void test()
    {
      m_tx.setPosition(0,2,0);
      loadToShader();
    }

    ngl::Transformation m_tx;
};


TestTx tx;

BENCHMARK(Transform, ClassMember, 10, 100)
{
  tx.test();
}



struct TestRef
{
    void loadToShader( ngl::Transformation &_tx)
    {
      auto t=_tx.getMatrix();
    }
    void test()
    {
      ngl::Transformation tx;
      tx.setPosition(0,2,0);
      loadToShader(tx);
    }

};

TestRef ref;

BENCHMARK(Transform, TestClass, 10, 100)
{
  ref.test();
}
