/*
  Copyright (C) 2011 Jon Macey

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
#ifndef VAOPRIMITIVES_H_
#define VAOPRIMITIVES_H_

// must include types.h first for Real
#include "AbstractVAO.h"
#include "Types.h"
#include "Vec3.h"
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace ngl
{

/// @class VAOPrimitives "include/VAOPrimitives.h"
/// @brief VAO based object primitives used for fast openGL drawing this is a singelton class
///  so we use the instance method to get access and construct the only instance
/// @author Jonathan Macey
/// @version 1.0
/// @date Last Revision 20/06/11 created and removed VBO class

// a simple structure to hold our vertex data this is a
// legacy format form GLDebugger as we could set to 2 3 3 format
struct vertData
{
  ngl::Real x;
  ngl::Real y;
  ngl::Real z;
  ngl::Real nx;
  ngl::Real ny;
  ngl::Real nz;
  ngl::Real u;
  ngl::Real v;
};

[[maybe_unused]] const static auto *teapot = "teapot";
[[maybe_unused]] const static auto *octahedron = "octahedron";
[[maybe_unused]] const static auto *dodecahedron = "dodecahedron";
[[maybe_unused]] const static auto *icosahedron = "icosahedron";
[[maybe_unused]] const static auto *tetrahedron = "tetrahedron";
[[maybe_unused]] const static auto *football = "football";
[[maybe_unused]] const static auto *cube = "cube";
[[maybe_unused]] const static auto *troll = "troll";
/// @note these data sets are huge and compilation takes a
/// long time hence only enable if needed
#ifdef ADDLARGEMODELS
[[maybe_unused]] const static auto *bunny = "bunny";
[[maybe_unused]] const static auto *dragon = "dragon";
[[maybe_unused]] const static auto *buddah = "buddah";
#endif
class NGL_DLLEXPORT VAOPrimitives
{

  friend class Vec3;

    public:
  

  /// @brief Draw one of the VBO's created via a name lookup
  /// @param[in] _name the name of the VBO to lookup in the VBO map
  
  static void draw(std::string_view _name) noexcept;
  
  /// @brief Draw one of the VBO's created via a name lookup
  /// @param[in] _name the name of the VBO to lookup in the VBO map
  /// @param[in] _mode the draw mode for the VBO override the default
  
  static void draw(std::string_view _name, GLenum _mode) noexcept;
  
  /// @brief create a triangulated Sphere as a vbo with auto generated texture cords
  /// @param[in] _name the name of the object created used when drawing
  /// @param[in] _radius the sphere radius
  /// @param[in] _precision the number of triange subdivisions to use
  
  static void createSphere(std::string_view _name, Real _radius, int _precision) noexcept;
  
  /// @brief create a line based grid (like the maya ground plane)
  /// @param[in] _name the name of the object created used when drawing
  /// @param[in] _width the width of the grid
  /// @param[in] _depth the depth of the grid
  /// @param[in] _steps the number of steps for the grid
  
  static void createLineGrid(std::string_view _name, Real _width, Real _depth, int _steps) noexcept;
  
  /// @brief create a Quad Cylinder as a vbo with auto generated texture cords
  /// @param[in] _name the name of the object created used when drawing
  /// @param[in] _radius the base radius of the Cylinder
  /// @param[in] _height the height of the Cylinder
  /// @param[in] _slices the number of quad elements around the Cylinder
  /// @param[in] _stacks the number of quad elements along the centeral axis
  
  static void createCylinder(std::string_view _name, const Real _radius, Real _height, unsigned int _slices, unsigned int _stacks) noexcept;
  
  /// @brief create a Quad Cone as a vao with auto generated texture cords
  /// @param[in] _name the name of the object created used when drawing
  /// @param[in] _base the base radius of the cone
  /// @param[in] _height the height of the cone
  /// @param[in] _slices the number of quad elements around the cone
  /// @param[in] _stacks the number of quad elements along the centeral axis
  
  static void createCone(std::string_view _name, Real _base, Real _height, unsigned int _slices, unsigned int _stacks) noexcept;
  
  /// @brief create a trinagle fan disk (use as end caps for Cylinder etc)
  /// @param[in] _name the name of the object created used when drawing
  /// @param[in] _radius the disk radius
  /// @param[in] _slices the number of triangles to form the disk
  
  static void createDisk(std::string_view _name, Real _radius, unsigned int _slices) noexcept;
  
  /// @brief create a VBO based torus from rings of quads.
  /// @param[in] _name the name of the VBO created for calling with the draw method
  /// @param[in] _minorRadius the inner radius of the torus
  /// @param[in] _majorRadius the outer radius of the torus.
  /// @param[in] _nSides the precision (number of quads) for the majorRadius
  /// @param[in] _nRings the precision (number of quads) for the minor Radius
  /// @param[in] _flipTX flip the texture co-ord generation default false.
  
  static void createTorus(std::string_view _name, Real _minorRadius, Real _majorRadius, unsigned int _nSides, unsigned int _nRings, bool _flipTX = false) noexcept;
  
  /// @brief create a triangulated plane as a vbo with auto generated texture cords
  /// @param[in] _name the name of the object created used when drawing
  /// @param[in] _width the width of the plane based on the center of the plane being at 0,0,0
  /// @param[in] _depth the height of the plane based on the center of the plane being at 0,0,0
  /// @param[in] _wP the precision of the width, this is basically the steps (per quad) which will be
  ///    triangulated for each (wP == 1 will give 1 quad mad of 2 tris)
  /// @param[in] _dP the precision of the Depth, this is basically the steps (per quad) which will be
  ///    triangulated for each (wP == 1 will give 1 quad mad of 2 tris)
  /// @param[in] _vN The Vertex normal (used for each vertex)
  
  static void createTrianglePlane(std::string_view _name, const Real _width, const Real _depth, const int _wP, const int _dP, const Vec3 &_vN) noexcept;
  
  /// @brief create a triangulated capsule (Cylinder with spherical ends)
  /// @param[in] _name the name of the object created used when drawing
  /// @param[in] _radius the radius of the capsule
  /// @param[in] _height the height of the capsule
  /// @param[in] _precision the precision of the tri mesh created (number of steps)
  
  static void createCapsule(std::string_view _name, const Real _radius = 1.0f, const Real _height = 2.0f, const int _precision = 20) noexcept;
  
  /// @brief load a VBO from a binary file created from Obj2VBO program
  /// @param[in] _name the name of the VBO to be stored as ref to this object
  /// @param[in] _fName the name of the file to load.
  /// @param[in] _type the draw mode type
  
  static void loadBinary(std::string_view _name, std::string_view _fName, const GLenum _type) noexcept;
  
  /// @brief load a VBO from an Obj file
  /// @param[in] _name the name of the VBO to be stored as ref to this object
  /// @param[in] _fName the name of the file to load.
  
  static void loadObj(std::string_view _name, std::string_view _fName) noexcept;
  
  /// @brief create the default VAO's this is done by the ctor anyway but can be called
  /// if the clear method is called. Note you will need to incude VAOHeaders in the client side
  
  static void createDefaultVAOs() noexcept;

  
  /// @brief clear the VAO elements created (is also called by dtor) This is usefull if you
  /// don't want the default primitives
  
  static void clear() noexcept;
  /// @brief get the raw VAO so we can map it etc
  static AbstractVAO *getVAOFromName(std::string_view _name);
  /// @brief add a VAO to the primitives library that we have created elsewhere
  /// @param[in] _name the name of the primitive
  /// @param[in] _id the VAO id
  static void addToPrimitives(std::string_view _name, std::unique_ptr< AbstractVAO > _vao) noexcept;

    private:
  
  ///  a map to store the VAO by name
  
  static std::unordered_map< std::string, std::unique_ptr< AbstractVAO > > m_createdVAOs;

  
  /// @brief default constructor
  
  VAOPrimitives() noexcept;
  
  /// @brief dtor
  
  virtual ~VAOPrimitives();
  
  /// @brief create a VAO from a static header file of data in the TNV format
  /// this will usually be created from the Obj2VBO program in the Models directory
  /// @param[in] _name the name reference for the VBO lookup
  /// @param[in] _data a pointer to the data to load
  /// @param[in] _Size the size of the array of data to load
  
  static void createVAOFromHeader(std::string_view _name, Real const *_data, unsigned int _Size) noexcept;

  
  /// @brief the method to actually create the VAO from the various other methods
  /// Note this is used in conjunction with the vertData struct
  /// @param[in] _name the name to store in the map of the VBO
  /// @param[in] _data the raw data packed into the vertData structure
  /// @param[in] _mode the mode to draw
  
  static void createVAO(std::string_view _name, const std::vector< vertData > &_data, const GLenum _mode) noexcept;
  
  /// @brief create the elements of a circle this is borrowed from freeglut
  /// @param[in,out] io_sint a pointer to the sin elements of the table
  /// @param[in,out] io_cost a pointer to the cos element of the table
  /// @param[in] _n the number of points to calculate.
  
  
  struct cos_sin
  {
    Real sint;
    Real cost;
  };
  static std::vector<cos_sin> fghCircleTable(size_t _n) noexcept;
};

} // namespace ngl
#endif
