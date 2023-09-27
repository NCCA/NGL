#include <gtest/gtest.h>
#include <ngl/Transformation.h>
#include <ngl/Mat4.h>
#include <ngl/Vec3.h>
#include <ngl/NGLStream.h>
TEST(Transformation, DefaultCtor)
{
  ngl::Transformation tx;
  EXPECT_TRUE(tx.getMatrix() == ngl::Mat4());
  EXPECT_TRUE(tx.getTransposeMatrix() == ngl::Mat4());
  EXPECT_TRUE(tx.getInverseMatrix() == ngl::Mat4());
}

TEST(Transformation, Position)
{
  {
    ngl::Transformation tx;
    tx.setPosition(1,2,3);
    EXPECT_TRUE(tx.getMatrix() == ngl::Mat4::translate(1,2,3));
    EXPECT_TRUE(tx.getTransposeMatrix() == ngl::Mat4::translate(1,2,3).transpose());
    EXPECT_TRUE(tx.getInverseMatrix() == ngl::Mat4::translate(1,2,3).inverse());

  }
   {
    ngl::Transformation tx;
    tx.setPosition(ngl::Vec3(1,2,3));
    EXPECT_TRUE(tx.getMatrix() == ngl::Mat4::translate(1,2,3));
    EXPECT_TRUE(tx.getTransposeMatrix() == ngl::Mat4::translate(1,2,3).transpose());
    EXPECT_TRUE(tx.getInverseMatrix() == ngl::Mat4::translate(1,2,3).inverse());

  }
  {
    ngl::Transformation tx;
    tx.setPosition(ngl::Vec4(1,2,3));
    EXPECT_TRUE(tx.getMatrix() == ngl::Mat4::translate(1,2,3));
    EXPECT_TRUE(tx.getTransposeMatrix() == ngl::Mat4::translate(1,2,3).transpose());
    EXPECT_TRUE(tx.getInverseMatrix() == ngl::Mat4::translate(1,2,3).inverse());

  }
  {
    ngl::Transformation tx;
    tx.addPosition(1,2,3);
    EXPECT_TRUE(tx.getMatrix() == ngl::Mat4::translate(1,2,3));
    EXPECT_TRUE(tx.getTransposeMatrix() == ngl::Mat4::translate(1,2,3).transpose());
    EXPECT_TRUE(tx.getInverseMatrix() == ngl::Mat4::translate(1,2,3).inverse());

  }
  {
    ngl::Transformation tx;
    tx.addPosition(ngl::Vec3(1,2,3));
    EXPECT_TRUE(tx.getMatrix() == ngl::Mat4::translate(1,2,3));
    EXPECT_TRUE(tx.getTransposeMatrix() == ngl::Mat4::translate(1,2,3).transpose());
    EXPECT_TRUE(tx.getInverseMatrix() == ngl::Mat4::translate(1,2,3).inverse());

  }
  {
    ngl::Transformation tx;
    tx.addPosition(ngl::Vec4(1,2,3));
    EXPECT_TRUE(tx.getMatrix() == ngl::Mat4::translate(1,2,3));
    EXPECT_TRUE(tx.getTransposeMatrix() == ngl::Mat4::translate(1,2,3).transpose());
    EXPECT_TRUE(tx.getInverseMatrix() == ngl::Mat4::translate(1,2,3).inverse());

  }
}




TEST(Transformation,Scale)
{
  {
    ngl::Transformation tx;
    tx.setScale(1,2,3);
    EXPECT_TRUE(tx.getMatrix() == ngl::Mat4::scale(1,2,3));
    EXPECT_TRUE(tx.getTransposeMatrix() == ngl::Mat4::scale(1,2,3).transpose());
    EXPECT_TRUE(tx.getInverseMatrix() == ngl::Mat4::scale(1,2,3).inverse());

  }
   {
    ngl::Transformation tx;
    tx.setScale(ngl::Vec3(1,2,3));
    EXPECT_TRUE(tx.getMatrix() == ngl::Mat4::scale(1,2,3));
    EXPECT_TRUE(tx.getTransposeMatrix() == ngl::Mat4::scale(1,2,3).transpose());
    EXPECT_TRUE(tx.getInverseMatrix() == ngl::Mat4::scale(1,2,3).inverse());

  }
  {
    ngl::Transformation tx;
    tx.setScale(ngl::Vec4(1,2,3));
    EXPECT_TRUE(tx.getMatrix() == ngl::Mat4::scale(1,2,3));
    EXPECT_TRUE(tx.getTransposeMatrix() == ngl::Mat4::scale(1,2,3).transpose());
    EXPECT_TRUE(tx.getInverseMatrix() == ngl::Mat4::scale(1,2,3).inverse());
  }
  // default scale is 1,1,1 to the add will be 2,3,4 if we add 1,2,3
  {
    ngl::Transformation tx;
    tx.addScale(1,2,3);
    EXPECT_TRUE(tx.getMatrix() == ngl::Mat4::scale(2,3,4));
    EXPECT_TRUE(tx.getTransposeMatrix() == ngl::Mat4::scale(2,3,4).transpose());
    EXPECT_TRUE(tx.getInverseMatrix() == ngl::Mat4::scale(2,3,4).inverse());

  }
   {
    ngl::Transformation tx;
    tx.addScale(ngl::Vec3(1,2,3));
    EXPECT_TRUE(tx.getMatrix() == ngl::Mat4::scale(2,3,4));
    EXPECT_TRUE(tx.getTransposeMatrix() == ngl::Mat4::scale(2,3,4).transpose());
    EXPECT_TRUE(tx.getInverseMatrix() == ngl::Mat4::scale(2,3,4).inverse());

  }
  {
    ngl::Transformation tx;
    tx.addScale(ngl::Vec4(1,2,3));
    EXPECT_TRUE(tx.getMatrix() == ngl::Mat4::scale(2,3,4));
    EXPECT_TRUE(tx.getTransposeMatrix() == ngl::Mat4::scale(2,3,4).transpose());
    EXPECT_TRUE(tx.getInverseMatrix() == ngl::Mat4::scale(2,3,4).inverse());
  }

}

TEST(Transformation, Rotation)
{
    auto xrot=ngl::Mat4::rotateX(45.0f);
    auto yrot=ngl::Mat4::rotateY(35.0f);
    auto zrot=ngl::Mat4::rotateZ(90.0f);
    auto totalRotation=zrot*yrot*xrot;
    auto totalTranspose=(zrot*yrot*xrot).transpose();
    auto totalInverse=(xrot*yrot*zrot);
    totalInverse=totalInverse.inverse();
  {
    ngl::Transformation tx;
    tx.setRotation(45.0f,35.0f,90.0f);

    EXPECT_TRUE(tx.getMatrix() == totalRotation);
    EXPECT_TRUE(tx.getTransposeMatrix() == totalTranspose);
  }

  {
    ngl::Transformation tx;
    tx.setRotation(ngl::Vec3(45.0f,35.0f,90.0f));

    EXPECT_TRUE(tx.getMatrix() == totalRotation);
    EXPECT_TRUE(tx.getTransposeMatrix() == totalTranspose);
  }
{
    ngl::Transformation tx;
    tx.setRotation(ngl::Vec4(45.0f,35.0f,90.0f));

    EXPECT_TRUE(tx.getMatrix() == totalRotation);
    EXPECT_TRUE(tx.getTransposeMatrix() == totalTranspose);
  }


  {
    ngl::Transformation tx;
    tx.setRotation(ngl::Vec3(45.0f,35.0f,90.0f));

    EXPECT_TRUE(tx.getMatrix() == totalRotation);
    EXPECT_TRUE(tx.getTransposeMatrix() == totalTranspose);
  }
  {
    ngl::Transformation tx;
    tx.addRotation(ngl::Vec4(45.0f,35.0f,90.0f));

    EXPECT_TRUE(tx.getMatrix() == totalRotation);
    EXPECT_TRUE(tx.getTransposeMatrix() == totalTranspose);
  }
  {
    ngl::Transformation tx;
    tx.addRotation(ngl::Vec3(45.0f,35.0f,90.0f));

    EXPECT_TRUE(tx.getMatrix() == totalRotation);
    EXPECT_TRUE(tx.getTransposeMatrix() == totalTranspose);
  }

  {
    ngl::Transformation tx;
    tx.addRotation(45.0,35.0,90.0f);

    EXPECT_TRUE(tx.getMatrix() == totalRotation);
    EXPECT_TRUE(tx.getTransposeMatrix() == totalTranspose);
    EXPECT_TRUE(tx.getInverseMatrix()== totalInverse);
  }
  {
    ngl::Transformation tx;
    tx.setRotation(ngl::Vec3(45.0,35.0,90.0f));

    EXPECT_TRUE(tx.getMatrix() == totalRotation);
    EXPECT_TRUE(tx.getTransposeMatrix() == totalTranspose);
    EXPECT_TRUE(tx.getInverseMatrix()== totalInverse);
  }
  {
    ngl::Transformation tx;
    tx.addRotation(ngl::Vec4(45.0,35.0,90.0f));

    EXPECT_TRUE(tx.getMatrix() == totalRotation);
    EXPECT_TRUE(tx.getTransposeMatrix() == totalTranspose);
    EXPECT_TRUE(tx.getInverseMatrix()== totalInverse);
 
  }
}

TEST(Transformation,setMatrix)
{
  ngl::Transformation tx;
  tx.setMatrix(ngl::Mat4::rotateX(35.0f));
  EXPECT_TRUE(tx.getMatrix()==ngl::Mat4::rotateX(35.0f));
}

TEST(Transformation,copyAndAssign)
{
  ngl::Transformation tx;
  tx.setRotation(45.0f,0.0f,0.0f);
  EXPECT_TRUE(tx.getMatrix()==ngl::Mat4::rotateX(45.0f));
  auto tx2(tx);
  EXPECT_TRUE(tx2.getMatrix()==ngl::Mat4::rotateX(45.0f));
  auto tx3=tx2;
  EXPECT_TRUE(tx3.getMatrix()==ngl::Mat4::rotateX(45.0f));
  
}

TEST(Transformation,reset)
{
  ngl::Transformation tx;
  tx.setRotation(45.0f,23.0f,0.0f);
  tx.setPosition(45.0f,3.0f,4.0f);
  tx.setScale(45.0f,3.0f,4.0f);
  tx.reset();
  EXPECT_TRUE(tx.getMatrix()==ngl::Mat4());
  auto tx2(tx);
  EXPECT_TRUE(tx2.getMatrix()==ngl::Mat4());
  auto tx3=tx2;
  EXPECT_TRUE(tx3.getMatrix()==ngl::Mat4());
  
}

TEST(Transformation,multiply)
{
  ngl::Transformation tx;
  tx.setRotation(45.0f,23.0f,0.0f);
  tx.setPosition(45.0f,3.0f,4.0f);
  tx.setScale(45.0f,3.0f,4.0f);
  auto tx2=tx*tx;
  EXPECT_TRUE(tx2.getMatrix()==tx.getMatrix()*tx.getMatrix());
  auto tx3=tx;
  tx3*=tx;
  EXPECT_TRUE(tx3.getMatrix()==tx.getMatrix()*tx.getMatrix());

}