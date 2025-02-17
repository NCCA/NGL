# -------------------------------------------------------------------------------------------
# as much as possible I will use best practice as outlined in the book "Profession cmake"
# -------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.20.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()
# -------------------------------------------------------------------------------------------
# Setup the project and languages required. Note version number is NGL version
# -------------------------------------------------------------------------------------------
project(AllNGL VERSION 8.0 LANGUAGES CXX C)
# These all assume we are using vcpkg for the install.
find_package(glm CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(gl3w CONFIG REQUIRED)
find_package(OpenMP)
find_package(OpenImageIO CONFIG)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(OpenImageIO_FOUND AND(NOT NO_OIIO AND NOT USE_QT))
    message("Found OpenImageIO so using that")
    add_compile_definitions(USEOIIO)
    #find_package(IlmBase CONFIG)
    find_package(OpenEXR CONFIG)
    set(Boost_NO_WARN_NEW_VERSIONS 1)
    find_package(Boost COMPONENTS filesystem thread)
elseif(USE_QT)
    message("Using Qt for Image and Font to avoid lib png bug")
    add_compile_definitions(USEQIMAGE)
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
else()
    message("Using Simpler Built-in Image Loaders only PNG,TIFF and EXR supported")
    add_compile_definitions(USEBUILTINIMAGE)
endif() # end of using OpenImageIO

find_package(freetype CONFIG REQUIRED)
find_path(RAPIDXML_INCLUDE_DIRS "rapidxml/rapidxml.hpp")
find_package(RapidJSON CONFIG REQUIRED)

# Set to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
option(ENABLE_FAST_MATH ON)
add_compile_definitions(NGL_DEBUG)

if(MSVC)
    add_compile_options(/W3 -wd4068) # /W4 is too noisy
else()
    add_compile_options(-Wall -Wextra -pedantic) # -Werror)
endif()

if (ADD_COVERAGE)
    message("adding coverage flags")
    add_compile_options(-ftest-coverage -fprofile-arcs)
endif()

if(WIN32)
    # Not defined in msvc compiler for cmaths so must set definition manually here
    add_compile_definitions(_USE_MATH_DEFINES)
    add_compile_definitions(NOMINMAX)

    # Need to define this when building shared library or suffer dllimport errors
    add_compile_definitions(BUILDING_DLL)

else()
    # Not a defined option for msvc - fine for gcc and clang
    set(CMAKE_CXX_FLAGS "-Wno-register")
endif()

# Bring the headers into the project (local ones)
include_directories(${CMAKE_SOURCE_DIR}/include/ngl)
include_directories(${CMAKE_SOURCE_DIR}/src/ngl)
include_directories(${CMAKE_SOURCE_DIR}/src/shaders)
include_directories(/usr/local/include/)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_compile_definitions(ADDLARGEMODELS)
add_compile_definitions(USEGLM)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

set(CPP_FILES
    ${CMAKE_SOURCE_DIR}/src/Vec4.cpp
    ${CMAKE_SOURCE_DIR}/src/VAOPrimitives.cpp
    ${CMAKE_SOURCE_DIR}/src/VAOFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/SimpleIndexVAO.cpp
    ${CMAKE_SOURCE_DIR}/src/SimpleVAO.cpp
    ${CMAKE_SOURCE_DIR}/src/AbstractVAO.cpp
    ${CMAKE_SOURCE_DIR}/src/MultiBufferVAO.cpp
    ${CMAKE_SOURCE_DIR}/src/Util.cpp
    ${CMAKE_SOURCE_DIR}/src/Texture.cpp
    ${CMAKE_SOURCE_DIR}/src/ShaderLib.cpp
    ${CMAKE_SOURCE_DIR}/src/Transformation.cpp
    ${CMAKE_SOURCE_DIR}/src/Quaternion.cpp
    ${CMAKE_SOURCE_DIR}/src/Obj.cpp
    ${CMAKE_SOURCE_DIR}/src/Mat4.cpp
    ${CMAKE_SOURCE_DIR}/src/NGLInit.cpp
    ${CMAKE_SOURCE_DIR}/src/BezierCurve.cpp
    ${CMAKE_SOURCE_DIR}/src/BBox.cpp
    ${CMAKE_SOURCE_DIR}/src/AbstractMesh.cpp
    ${CMAKE_SOURCE_DIR}/src/Random.cpp
    ${CMAKE_SOURCE_DIR}/src/NCCAPointBake.cpp
    ${CMAKE_SOURCE_DIR}/src/Shader.cpp
    ${CMAKE_SOURCE_DIR}/src/ShaderProgram.cpp
    ${CMAKE_SOURCE_DIR}/src/Plane.cpp
    ${CMAKE_SOURCE_DIR}/src/AABB.cpp
    ${CMAKE_SOURCE_DIR}/src/createDefaultVAOs.cpp
    ${CMAKE_SOURCE_DIR}/src/Vec3.cpp
    ${CMAKE_SOURCE_DIR}/src/Vec2.cpp
    ${CMAKE_SOURCE_DIR}/src/Text.cpp
    ${CMAKE_SOURCE_DIR}/src/Mat3.cpp
    ${CMAKE_SOURCE_DIR}/src/Mat2.cpp
    ${CMAKE_SOURCE_DIR}/src/NGLStream.cpp
    ${CMAKE_SOURCE_DIR}/src/Image.cpp
    ${CMAKE_SOURCE_DIR}/src/Types.cpp
    ${CMAKE_SOURCE_DIR}/src/pystring.cpp
    ${CMAKE_SOURCE_DIR}/src/NGLMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/BufferTextures.cpp

)

set(HEADERS
    ${CMAKE_SOURCE_DIR}/include/ngl/Vec4.h
    ${CMAKE_SOURCE_DIR}/include/ngl/VAOPrimitives.h
    ${CMAKE_SOURCE_DIR}/include/ngl/VAOFactory.h
    ${CMAKE_SOURCE_DIR}/include/ngl/SimpleIndexVAO.h
    ${CMAKE_SOURCE_DIR}/include/ngl/SimpleVAO.h
    ${CMAKE_SOURCE_DIR}/include/ngl/AbstractVAO.h
    ${CMAKE_SOURCE_DIR}/include/ngl/MultiBufferVAO.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Util.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Types.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Texture.h
    ${CMAKE_SOURCE_DIR}/include/ngl/ShaderLib.h
    ${CMAKE_SOURCE_DIR}/include/ngl/ShaderLib.inl
    ${CMAKE_SOURCE_DIR}/include/ngl/Transformation.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Quaternion.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Obj.h
    ${CMAKE_SOURCE_DIR}/include/ngl/NGLassert.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Mat4.h
    ${CMAKE_SOURCE_DIR}/include/ngl/NGLInit.h
    ${CMAKE_SOURCE_DIR}/include/ngl/BezierCurve.h
    ${CMAKE_SOURCE_DIR}/include/ngl/BBox.h
    ${CMAKE_SOURCE_DIR}/include/ngl/AbstractMesh.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Random.h
    ${CMAKE_SOURCE_DIR}/include/ngl/NCCAPointBake.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Shader.h
    ${CMAKE_SOURCE_DIR}/include/ngl/ShaderProgram.h
    ${CMAKE_SOURCE_DIR}/include/ngl/ShaderProgram.inl
    ${CMAKE_SOURCE_DIR}/include/ngl/BufferTextures.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Plane.h
    ${CMAKE_SOURCE_DIR}/include/ngl/AABB.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Vec3.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Vec2.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Text.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Mat3.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Mat2.h
    ${CMAKE_SOURCE_DIR}/include/ngl/pystring.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Image.h
    ${CMAKE_SOURCE_DIR}/include/ngl/NGLStream.h
    ${CMAKE_SOURCE_DIR}/include/ngl/NGLStream.h
    ${CMAKE_SOURCE_DIR}/include/ngl/NGLMessage.h
    ${CMAKE_SOURCE_DIR}/include/ngl/NGLHash.h
    ${CMAKE_SOURCE_DIR}/src/shaders/TextShaders.h
    ${CMAKE_SOURCE_DIR}/src/shaders/ColourShaders.h
    ${CMAKE_SOURCE_DIR}/src/shaders/DiffuseShaders.h
)

if(NOT DEFINED PYNGL_ONLY)
    if(NO_OIIO)
        install(FILES ${CMAKE_SOURCE_DIR}/NGLConfigNOOIIO.cmake RENAME NGLConfig.cmake DESTINATION ./)
    else()
        install(FILES ${CMAKE_SOURCE_DIR}/NGLConfig.cmake DESTINATION ./)
    endif()

    if(WIN32)
        add_library(NGL STATIC)
    else()
        add_library(NGL SHARED)
    endif()

    target_sources(NGL PRIVATE ${CPP_FILES} ${HEADERS})
    install(TARGETS NGL DESTINATION lib CONFIGURATIONS Release)
    install(TARGETS NGL DESTINATION lib)

    install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ngl/ DESTINATION include/ngl)

    # see what platform we are on and set platform defines
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        find_library(MACGL OpenGL)
        add_definitions(-DGL_SILENCE_DEPRECATION)
        set(EXTRALIBS ${MACGL})
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set(EXTRALIBS OpenMP::OpenMP_CXX)
    endif()

    if(WIN32)
        add_definitions(-D_USE_MATH_DEFINES)
        set(EXTRALIBS OpenMP::OpenMP_CXX)
    endif()

    # add exe and link libs this must be after the other defines
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BUILD_DIR})

    target_link_libraries(NGL PRIVATE glm::glm)
    target_link_libraries(NGL PRIVATE fmt::fmt)
    target_link_libraries(NGL PRIVATE unofficial::gl3w::gl3w)
    target_link_libraries(NGL PRIVATE ${EXTRALIBS})

    if(OpenImageIO_FOUND AND(NOT NO_OIIO AND NOT USE_QT))
        find_package(OpenMP)
        target_link_libraries(NGL PRIVATE OpenImageIO::OpenImageIO Boost::filesystem Boost::thread)
    endif()

    if(USE_QT)
        target_link_libraries(NGL PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
    endif()

    target_link_libraries(NGL PRIVATE freetype )
    target_include_directories(NGL PRIVATE ${RAPIDXML_INCLUDE_DIRS})
    target_include_directories(NGL PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
    if (ADD_COVERAGE)
        target_link_libraries(NGL PRIVATE --coverage)
    endif()



    # ################################################################
    # Tests
    # ################################################################
    find_package(GTest CONFIG REQUIRED)
    include(GoogleTest)
    enable_testing()

    find_package(glfw3 CONFIG REQUIRED)

    add_executable(NGLTests)
    target_sources(NGLTests PRIVATE
        ${CMAKE_SOURCE_DIR}/tests/main.cpp
        ${CMAKE_SOURCE_DIR}/tests/AABBTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/UtilTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/BBoxTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/BezierCurveTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/Vec4Tests.cpp
        ${CMAKE_SOURCE_DIR}/tests/Mat2Tests.cpp
        ${CMAKE_SOURCE_DIR}/tests/NGLInitTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/VAOPrimitivesTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/Mat3Tests.cpp
        ${CMAKE_SOURCE_DIR}/tests/ObjTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/PlaneTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/TransformationTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/Vec2Tests.cpp
        ${CMAKE_SOURCE_DIR}/tests/Mat4Tests.cpp
        ${CMAKE_SOURCE_DIR}/tests/ShaderLibTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/Vec3Tests.cpp
        ${CMAKE_SOURCE_DIR}/tests/RandomTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/QuaternionTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/ImageTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/HashTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/PointBakeTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/MessageTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/NGLStreamTest.cpp
        ${CMAKE_SOURCE_DIR}/tests/TextureTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/BufferTextureTests.cpp
        ${CMAKE_SOURCE_DIR}/tests/VAOFactoryTests.cpp
        
    )
    add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)
    target_link_libraries(NGLTests PRIVATE glfw PRIVATE GTest::gtest )
    target_link_libraries(NGLTests PRIVATE fmt::fmt )

    # if ( OpenImageIO_FOUND AND NOT NO_OIIO OR NOT USE_QT)
    if(OpenImageIO_FOUND AND(NOT NO_OIIO AND NOT USE_QT))
        target_link_libraries(NGLTests PRIVATE OpenImageIO::OpenImageIO Boost::filesystem Boost::thread )
    endif()

    if(USE_QT)
        target_link_libraries(NGLTests PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
    endif()

    target_include_directories(NGLTests PRIVATE ${RAPIDXML_INCLUDE_DIRS})
    target_include_directories(NGLTests PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
    target_link_libraries(NGLTests PRIVATE freetype)
    target_link_libraries(NGLTests PRIVATE unofficial::gl3w::gl3w)

    # see what platform we are on and set platform defines
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        message("Doing mac OpenGL")
        find_library(MACGL OpenGL)
        add_definitions(-DGL_SILENCE_DEPRECATION)
        set(EXTRALIBS ${MACGL})
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set(EXTRALIBS OpenMP::OpenMP_CXX)
    endif()

    if(WIN32)
        add_definitions(-D_USE_MATH_DEFINES)
        set(EXTRALIBS OpenMP::OpenMP_CXX)
    endif()

    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        message("On Windows " ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
        target_link_libraries(NGLTests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/NGL.lib)
    else()
        target_link_libraries(NGLTests PRIVATE NGL PRIVATE ${EXTRALIBS})
    endif()
 if (ADD_COVERAGE)
        target_link_libraries(NGLTests PRIVATE --coverage)
    endif()
    # gtest_discover_tests(NGLTests)
    # Now create a post build command to copy the test directories
    add_custom_command(
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/tests/files
                    ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/files
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            OUTPUT  ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/files/
            COMMENT "copying test files"
    )
    # Now a custom target to copy the files which check to see if the files exist
    add_custom_target(
            CopyTestfiles ALL
            DEPENDS ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/files/
    )
    # now add this a dependency for NGLTests so it gets run.
    add_dependencies(NGLTests CopyTestfiles )



    #    add_custom_target(CopyTestfiles ALL
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/tests/filesinary
#        ${CMAKE_BINARY_DIR}/files
#            COMMENT "Copy Test files to build directory"
#    )

endif() # PYNGL_ONLY

# PyNGL
# ############################################################
if(DEFINED BUILD_PYNGL OR DEFINED PYNGL_ONLY)
    find_package(pybind11 CONFIG REQUIRED)
    add_compile_definitions(PYTHONBUILD)

    set(PYSOURCEDIR ${CMAKE_SOURCE_DIR}/PyNGL/src)
    include_directories(${CMAKE_SOURCE_DIR}/PyNGL/)
    include_directories(${PYTHON_INCLUDE_DIRS})
    pybind11_add_module(pyngl NO_EXTRAS)

    target_sources(pyngl PRIVATE ${CPP_FILES} ${HEADERS}
        ${PYSOURCEDIR}/PyAABB.cpp
        ${PYSOURCEDIR}/PyNGLInit.cpp
        ${PYSOURCEDIR}/PyText.cpp
        ${PYSOURCEDIR}/PyAbstractMesh.cpp
        ${PYSOURCEDIR}/PyObj.cpp
        ${PYSOURCEDIR}/PyTexture.cpp
        ${PYSOURCEDIR}/PyAbstractVAO.cpp
        ${PYSOURCEDIR}/PyPlane.cpp
        ${PYSOURCEDIR}/PythonBindings.cpp
        ${PYSOURCEDIR}/PyBBox.cpp
        ${PYSOURCEDIR}/PyQuaternion.cpp
        ${PYSOURCEDIR}/PyTransformation.cpp
        ${PYSOURCEDIR}/PyBezierCurve.cpp
        ${PYSOURCEDIR}/PyRandom.cpp
        ${PYSOURCEDIR}/PyUtil.cpp
        ${PYSOURCEDIR}/PyImage.cpp
        ${PYSOURCEDIR}/PyVAOFactory.cpp
        ${PYSOURCEDIR}/PyMat3.cpp
        ${PYSOURCEDIR}/PyMat2.cpp
        ${PYSOURCEDIR}/PyShader.cpp
        ${PYSOURCEDIR}/PyVAOPrimitives.cpp
        ${PYSOURCEDIR}/PyMat4.cpp
        ${PYSOURCEDIR}/PyShaderLib.cpp
        ${PYSOURCEDIR}/PyVec2.cpp
        ${PYSOURCEDIR}/PyMultiBufferVAO.cpp
        ${PYSOURCEDIR}/PyShaderProgram.cpp
        ${PYSOURCEDIR}/PyVec3.cpp
        ${PYSOURCEDIR}/PySimpleIndexVAO.cpp
        ${PYSOURCEDIR}/PyVec4.cpp
        ${PYSOURCEDIR}/PyNCCAPointBake.cpp
        ${PYSOURCEDIR}/PySimpleVAO.cpp
    )

    # see what platform we are on and set platform defines
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        find_library(MACGL OpenGL)
        add_definitions(-DGL_SILENCE_DEPRECATION)
        set(EXTRALIBS ${MACGL})
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set(EXTRALIBS OpenMP::OpenMP_CXX)
    endif()

    if(WIN32)
        add_definitions(-D_USE_MATH_DEFINES)
        set(EXTRALIBS OpenMP::OpenMP_CXX)
    endif()

    # add exe and link libs this must be after the other defines
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY${CMAKE_SOURCE_DIR}/lib)
    SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_SOURCE_DIR}/lib/pyngl.so")
    target_link_libraries(pyngl PRIVATE pybind11::module)
    target_link_libraries(pyngl PRIVATE glm::glm)
    target_link_libraries(pyngl PRIVATE fmt::fmt)
    target_link_libraries(pyngl PRIVATE unofficial::gl3w::gl3w)
    target_link_libraries(pyngl PRIVATE ${PROJECT_LINK_LIBS} ${EXTRALIBS})

    if(OpenImageIO_FOUND AND NOT NO_OIIO)
        target_link_libraries(pyngl PRIVATE OpenImageIO::OpenImageIO Boost::filesystem Boost::thread )
    endif()

    target_link_libraries(pyngl PRIVATE freetype)
    target_include_directories(pyngl PRIVATE ${RAPIDXML_INCLUDE_DIRS})
    target_include_directories(pyngl PRIVATE ${RAPIDJSON_INCLUDE_DIRS})

    install(TARGETS pyngl DESTINATION lib CONFIGURATIONS Release)
    install(TARGETS pyngl DESTINATION lib)
endif()
