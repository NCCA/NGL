#include <gtest/gtest.h>
#include <ngl/VAOFactory.h>


class  MultiBufferIndexVAO : public ngl::AbstractVAO
{
  public :

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief creator method for the factory
    /// @param _mode the mode to draw with.
    /// @returns a new AbstractVAO * object
    //----------------------------------------------------------------------------------------------------------------------
    static std::unique_ptr<ngl::AbstractVAO>create(GLenum _mode=GL_TRIANGLES) { return std::unique_ptr<AbstractVAO>(new MultiBufferIndexVAO(_mode)); }
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief draw the VAO using glDrawArrays
    //----------------------------------------------------------------------------------------------------------------------
    virtual void draw() const override{}
    void draw(int , int ) const {}
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor don't do anything as the remove clears things
    //----------------------------------------------------------------------------------------------------------------------
    virtual ~MultiBufferIndexVAO()=default;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief remove the VAO and buffers created
    //----------------------------------------------------------------------------------------------------------------------
    virtual void removeVAO() override {};
    virtual void setData(const VertexData &) override {};
    void setIndices(unsigned int ,const GLvoid *,GLenum ,GLenum ) {}

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief return the id of the buffer, if there is only 1 buffer just return this
    /// if we have the more than one buffer the sub class manages the id's
    /// @param _buffer index (default to 0 for single buffer VAO's)
    //----------------------------------------------------------------------------------------------------------------------
     GLuint getBufferID(unsigned int )const override{return m_buffer;}
     // no need to implement this for the demo but if you need to
     // modify the buffer do so
     ngl::Real * mapBuffer(unsigned int , GLenum ) override{ return nullptr;}


  protected :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor calles parent ctor to allocate vao;
    //----------------------------------------------------------------------------------------------------------------------
    MultiBufferIndexVAO(GLenum _mode)  : ngl::AbstractVAO(_mode)
    {

    }

  private :
    GLuint m_buffer=0;
};


TEST(VAOFactory,register)
{
  ngl::VAOFactory::registerVAOCreator("multiBufferIndexVAO", MultiBufferIndexVAO::create);
  ngl::VAOFactory::listCreators();
  EXPECT_TRUE(ngl::VAOFactory::getNumCreators()==4);
}

TEST(VAOFactory,unregister)
{
  ngl::VAOFactory::unregisterVAOCreator("multiBufferIndexVAO");
  EXPECT_TRUE(ngl::VAOFactory::getNumCreators()==3);

}