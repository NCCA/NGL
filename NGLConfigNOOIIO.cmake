set(NGL_Found,1)
find_package(glm CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(gl3w CONFIG REQUIRED)


find_package(freetype CONFIG REQUIRED)
find_path(RAPIDXML_INCLUDE_DIRS "rapidxml/rapidxml.hpp")
find_package(RapidJSON CONFIG REQUIRED)
add_compile_definitions(ADDLARGEMODELS)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

if(DEFINED NGL_HOME)
	message("NGL_HOME DEFINED as ${NGL_HOME}")
else()
	message("Using default home dir")
	if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set(NGL_HOME $ENV{HOME}/NGL)	
	elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")		
		set(NGL_HOME $ENV{HOME}/NGL)	
	elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")		
			set(NGL_HOME $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/NGL)	
	endif()
	message("${NGL_HOME}")
endif()

# see what platform we are on and set platform defines
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	find_library(MACGL OpenGL)
	include_directories(include ${NGL_HOME}/include)
	set(EXTRALIBS  ${MACGL})
  add_definitions(-DGL_SILENCE_DEPRICATION)
	add_definitions(-DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED)
	set ( PROJECT_LINK_LIBS ${MACGL} NGL)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	include_directories(include ${NGL_HOME}/include)
	set ( PROJECT_LINK_LIBS -lGL NGL)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
 	include_directories(include ${NGL_HOME}/include)
	link_directories(${NGL_HOME}/lib)	
	link_libraries(${NGL_HOME}/lib/NGL.lib)
	add_compile_options(/W3 -wd4068 ) # /W4 is too noisy
	add_compile_definitions(_USE_MATH_DEFINES)
	add_compile_definitions(NOMINMAX)
	# Need to define this when building shared library or suffer dllimport errors
	add_compile_definitions(BUILDING_DLL)
endif()

# now add NGL specific values
link_directories(${NGL_HOME}/lib)

link_libraries( ${PROJECT_LINK_LIBS}  fmt::fmt-header-only freetype glm::glm unofficial::gl3w::gl3w)

