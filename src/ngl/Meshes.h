#if defined __cplusplus

/// these will be pre-compiled for speed
	#include "Football.h"
	#include "Cube.h"
	#include "Teapot.h"
	#include "Octahedron.h"
	#include "Dodecahedron.h"
	#include "Icosahedron.h"
	#include "Tetrahedron.h"
	#include "Troll.h"
/// if you want the large data sets just define the following
/// in the .pro file
#ifdef ADDLARGEMODELS
	#include "Bunny.h"
	#include "Dragon.h"
	#include "Buddah.h"
#endif


 #endif
