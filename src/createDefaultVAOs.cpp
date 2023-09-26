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
  createVAOFromHeader(teapot,&Teapot[0],teapotSIZE);
  createVAOFromHeader(octahedron,&Octahedron[0],OctahedronSIZE);
  createVAOFromHeader(dodecahedron,&Dodecahedron[0],dodecahedronSIZE);
  createVAOFromHeader(icosahedron,&Icosahedron[0],icosahedronSIZE);
  createVAOFromHeader(tetrahedron,&Tetrahedron[0],tetrahedronSIZE);
  createVAOFromHeader(football,&Football[0],footballSIZE);
  createVAOFromHeader(cube,&Cube[0],cubeSIZE);
  createVAOFromHeader(troll,&Troll[0],trollSIZE);
/// @note these data sets are huge and compilation takes a
/// long time hence only enable if needed
#ifdef ADDLARGEMODELS
  createVAOFromHeader(bunny,&Bunny[0],bunnySIZE);
  createVAOFromHeader(dragon,&Dragon[0],dragonSIZE);
  createVAOFromHeader(buddah,&Buddah[0],buddahSIZE);
#endif


}

}
