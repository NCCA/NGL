/*
  Copyright (C) 2009 Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ABSTRACT_MESH_H_
#define ABSTRACT_MESH_H_
/// @file AbstractMesh.h
/// @brief a series of classes used to define an abstract 3D mesh of Faces, Vertex Normals and TexCords
// must include types.h first for Real and GLEW if required
#include "AbstractVAO.h"
#include "BBox.h"
#include "NGLassert.h"
#include "Texture.h"
#include "Types.h"
#include "Vec4.h"
#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>

namespace ngl
{

/// @class Face  "include/Obj.h"
/// @brief simple class used to encapsulate a single face of an abstract mesh file

struct Face
{
  /// @brief The vertices index 
  std::vector< uint32_t > m_vert;
  /// @brief The texture co-ord index
  std::vector< uint32_t > m_uv;
  /// @brief the normal index
  std::vector< uint32_t > m_norm;
  /// @brief debug flag to turn face on and off
  bool m_textureCoord = false;
  bool m_normals = false;
};



/// @class AbstractMesh "include/AbstractMesh.h"
/// @author Jonathan Macey
/// @version 1.0
/// @date 24/09/09
/// Last Revision 16/06/10 added accessors for the mesh elements
/// @brief an abstract base mesh used to build specific meshes such as Obj

class NGL_DLLEXPORT AbstractMesh
{

    public:
  enum class CalcBB : bool
  {
    True = true,
    False = false
  };
  enum class ResetVAO : bool
  {
    True = true,
    False = false
  };

  
  /// @brief Method to load the file in
  /// @param[in]  &_fname the name of the obj file to load
  
  virtual bool load(std::string_view _fname, CalcBB _calcBB = CalcBB::True) noexcept = 0;
  
  /// @brief default ctor must be called from the child class so our dtor is called
  
  AbstractMesh() noexcept
    : m_vbo(false), m_vao(false), m_ext(nullptr)
  {
    ;
  }
  // AbstractMesh(const AbstractMesh &) =default;
  
  /// @brief destructor this will clear out all the vert data and the vbo if created
  
  virtual ~AbstractMesh() noexcept;
  
  /// @brief method to draw the bounding box
  
  void drawBBox() const noexcept;
  
  /// @brief draw method to draw the obj as a VBO. The VBO first needs to be created using the CreateVBO method
  
  void draw() const noexcept;
  
  /// @brief bind the underlying VAO so other draw methods can be used
  
  void bindVAO() const noexcept;
  
  /// @brief unbind the underlying VAO so other draw methods can be used
  
  void unbindVAO() const noexcept;
  
  /// @brief grab the buffer id of the VAO
  
  GLuint getVAOBufferID()
  {
    return m_vaoMesh->getBufferID();
  }

  
  /// @brief load int a texture and set it as the active texture of the Obj
  /// @param[in] &_fname the name of the file to load
  void loadTexture(std::string_view _fname) noexcept;

  
  /// @brief scale the obj by multiplying the actual vertex values by sx,sy and sz
  /// @param[in] _sx the scale value in x
  /// @param[in] _sy the scale value in y
  /// @param[in] _sz the scale value in z
  
  void scale(Real _sx, Real _sy, Real _sz) noexcept;
  
  /// @brief a method to set the BBox and center
  
  void calcDimensions() noexcept;
  
  /// @brief a method to caluculate the bounding Sphere will set
  /// m_sphereCenter and m_sphereRadius
  
  void calcBoundingSphere() noexcept;


  
  //// @brief create a VAO from the current mesh data
  
  virtual void createVAO(ResetVAO _reset = ResetVAO::False) noexcept;
  /// @brief unallocate the VAO so we can move it (for example to the prim class)
  std::unique_ptr< AbstractVAO > moveVAO() noexcept;
  
  /// @brief get the texture id
  /// @returns the texture id
  
  unsigned int getTextureID() const noexcept
  {
    return m_textureID;
  }
  
  /// @brief map the VBO vertex data
  /// @returns a pointer to the VBO vertex data
  
  Real *mapVAOVerts() noexcept;
  /// @brief unmap the VBO based
  void unMapVAO() noexcept;
  /// @brief a method to get the current bounding box of the mesh
  /// @returns the bounding box for the loaded mesh;

  BBox &getBBox() noexcept
  {
    return *m_ext;
  }
  /// @brief accessor for the vertex data
  /// @returns a std::vector containing the vert data
  std::vector< Vec3 > getVertexList() const noexcept
  {
    return m_verts;
  }
  
  /// @brief accessor for the vertex data
  /// @returns a std::vector containing the vert data
  
  Vec3 getVertexAtIndex(uint32_t _i) const noexcept
  {
    return m_verts[_i];
  }

  
  /// @brief accessor for the normals data
  /// @returns a std::vector containing the normal data
  
  std::vector< Vec3 > getNormalList() const noexcept
  {
    return m_norm;
  }
  
  /// @brief accessor for the texture co-ordinates data
  /// @returns a std::vector containing the texture cord data
  
  std::vector< Vec3 > getUVList() const noexcept
  {
    return m_uv;
  }
  
  /// @brief accessor for the Face data
  /// @returns a std::vector containing the face data
  
  std::vector< Face > getFaceList() const noexcept
  {
    return m_face;
  }
  
  /// @brief accessor to get the number of vertices in the object
  
  size_t getNumVerts() const noexcept
  {
    return m_verts.size();
  }
  
  /// @brief accessor to get the number of normals in the object
  
  size_t getNumNormals() const noexcept
  {
    return m_norm.size();
  }
  
  /// @brief accessor to get the number of texture co-ordinates in the object
  
  size_t getNumTexCords() const noexcept
  {
    return m_uv.size();
  }
  
  /// @brief accessor to get the number of faces in the object
  
  size_t getNumFaces() const noexcept
  {
    return m_face.size();
  }
  size_t getMeshSize() const noexcept
  {
    return m_meshSize;
  }
  
  /// @brief accesor to get the bounding sphere center
  
  Vec3 getSphereCenter() const noexcept
  {
    return m_sphereCenter;
  }
  
  /// @brief accesor to get the bounding sphere center
  
  Real getSphereRadius() const noexcept
  {
    return m_sphereRadius;
  }
  
  /// @brief accesor to get the center
  
  Vec3 getCenter() const noexcept
  {
    return m_center;
  }
  
  /// @brief check to see if obj is triangulated as we only support tri or quad objs at the moment
  /// @returns true or false
  
  bool isTriangular() const noexcept;

    protected:
  friend class NCCAPointBake;
  /// @brief Pointer to the Vertex list
  std::vector< Vec3 > m_verts;
  /// @brief Pointer to the Normal List
  std::vector< Vec3 > m_norm;
  /// @brief Pointer to the Texture co-ord list (note that only x and y are used)
  std::vector< Vec3 > m_uv;
  /// @brief Pointer to the Face list
  std::vector< Face > m_face;
  /// @brief Center of the object
  Vec3 m_center = {0.0f, 0.0f, 0.0f};
  /// @brief the size of the index array
  size_t m_indexSize = 0;
  size_t m_meshSize = 0;
  /// @brief buffers for the VBO in order Vert, Tex, Norm
  GLuint m_vboBuffers = 0;
  /// @brief id for our vertexArray object
  std::unique_ptr< AbstractVAO > m_vaoMesh;
  /// @brief flag to indicate if a VBO has been created
  bool m_vbo = false;
  /// @brief flag to indicate if a VBO has been created
  bool m_vao = false;
  /// @brief flag to indicate if the VBO vertex data has been mapped
  bool m_vboMapped = false;
  /// @brief flag to indicate if texture assigned
  bool m_texture = false;
  /// @brief The openGL id  of the texture for the texture generation
  GLuint m_textureID = 0;
  /// @brief The Maximum X value in the obj file used to calculate the extents bbox
  Real m_maxX = 0.0f;
  /// @brief The Min X value in the obj file used to calculate the extents bbox
  Real m_minX = 0.0f;
  /// @brief  The Max Y value in the obj file used to calculate the extents bbox
  Real m_maxY = 0.0f;
  /// @brief  The Min Y value in the obj file used to calculate the extents bbox
  Real m_minY = 0.0f;
  /// @brief  The Max Z value in the obj file used to calculate the extents bbox
  Real m_maxZ = 0.0f;
  /// @brief  The Min Z value in the obj file used to calculate the extents bbox
  Real m_minZ = 0.0f;
  /// @brief   Create a bounding box of the object to store it's extents
  std::unique_ptr< BBox > m_ext;
  /// @brief  determines if the data is Packed as either TRI or QUAD
  GLuint m_dataPackType = 0;
  /// @brief  the size of the buffer pack we use this for the saving of bin vbo
  /// but it actually holds the size of the data (3 for just verts 5 verts norms etc)
  unsigned int m_bufferPackSize = 0;
  /// @brief  which type of VBO are we going to draw
  GLenum m_vboDrawType = 0;  
  /// @brief  flag to indicate if anything loaded for dtor
  bool m_loaded = false;
  /// @brief  the center of the bounding sphere
  Vec3 m_sphereCenter;
  /// @brief  the radius of the bounding sphere
  Real m_sphereRadius = 0.0f;
};

} // end of namespace ngl

#endif // end of the class
