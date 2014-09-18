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

void VAOPrimitives::createDefaultVAOs()
{
  // load into the vbo list some basic primitives (these are created in .h file arrays from Obj2VBO)
  // Obj2VBO and the original models may be found in the Models directory
   createVAOFromHeader("teapot",teapot,teapotSIZE);
  createVAOFromHeader("octahedron",Octahedron,OctahedronSIZE);
  createVAOFromHeader("dodecahedron",dodecahedron,dodecahedronSIZE);
  createVAOFromHeader("icosahedron",icosahedron,icosahedronSIZE);
  createVAOFromHeader("tetrahedron",tetrahedron,tetrahedronSIZE);
  createVAOFromHeader("football",football,footballSIZE);
  createVAOFromHeader("cube",cube,cubeSIZE);
  createVAOFromHeader("troll",troll,trollSIZE);
/// @note these data sets are huge and compilation takes a
/// long time hence only enable if needed
#ifdef ADDLARGEMODELS
  createVAOFromHeader("bunny",bunny,bunnySIZE);
  createVAOFromHeader("dragon",dragon,dragonSIZE);
  createVAOFromHeader("buddah",buddah,buddahSIZE);
#endif


}

}
