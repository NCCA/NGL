#include "VAOPrimitives.h"
#include "Meshes.h"


//----------------------------------------------------------------------------------------------------------------------
/// @file createDefaultVAOs.cpp
/// @brief implementation files for VAOPrimitives this has been split as it takes a long
/// time to compile this file due to the size of the stanford models, as this file is not updated
/// that often it was decided to split out this method to increase compilation speed when
/// modifying the rest of the VAO primitives class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{

void VAOPrimitives::createDefaultVAOs() noexcept
{
  // load into the vbo list some basic primitives (these are created in .h file arrays from Obj2VBO)
  // Obj2VBO and the original models may be found in the Models directory
  createVAOFromHeader(teapot,Teapot,teapotSIZE);
  createVAOFromHeader(octahedron,Octahedron,OctahedronSIZE);
  createVAOFromHeader(dodecahedron,Dodecahedron,dodecahedronSIZE);
  createVAOFromHeader(icosahedron,Icosahedron,icosahedronSIZE);
  createVAOFromHeader(tetrahedron,Tetrahedron,tetrahedronSIZE);
  createVAOFromHeader(football,Football,footballSIZE);
  createVAOFromHeader(cube,Cube,cubeSIZE);
  createVAOFromHeader(troll,Troll,trollSIZE);
/// @note these data sets are huge and compilation takes a
/// long time hence only enable if needed
#ifdef ADDLARGEMODELS
  createVAOFromHeader(bunny,Bunny,bunnySIZE);
  createVAOFromHeader(dragon,Dragon,dragonSIZE);
  createVAOFromHeader(buddah,Buddah,buddahSIZE);
#endif


}

}
