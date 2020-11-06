# NGL the NCCA Graphics Library

## NGL 8 master branch 

For the current build status see our CI logs here 


[![Build Status](https://travis-ci.org/NCCA/NGL.svg?branch=master)](https://travis-ci.org/NCCA/NGL)
[Travis CI (Linux and Mac)](https://travis-ci.org/NCCA/NGL)

[![CircleCI](https://circleci.com/gh/NCCA/NGL.svg?style=svg)](https://circleci.com/gh/NCCA/NGL)
[Circle CI (g++ latest (8))](https://circleci.com/gh/NCCA)

## Pre-requisites

NGL depends upon the following libraries

- [OpenImageIO](https://github.com/OpenImageIO/oiio) For image reading and writing. 
- [GLM](https://glm.g-truc.net/0.9.9/index.html) this is a header only library and can be copied to /usr/local/include This is a compatibility layer and can be removed by commenting out the  USEGLM define in the Qt projects.
- [glfw3](https://www.glfw.org/) is used to create an OpenGL context for the unit tests, if you don't want to install this just don't build the unit tests.  
- [gtest](https://github.com/google/googletest) for Unit testing if you are building the tests.
- [cmake](https://cmake.org/) for building of NGL and all demos.

To install all the dependencies I use [vcpkg](https://github.com/microsoft/vcpkg) depending upon your platform you can read what to install in the detailed instructions below.


## Building

It needs to be built using QtCreator or CMake for Windows build instructions read [Windows.md](Windows.md). A brief guide for setting up with Ubuntu can be found here [UBUNTU.md](UBUNTU.md) and [Mac OSX](Mac.md)

Note this is now being built using C++ 17 and will use many C++ 17 features so make sure you have a modern compiler such as clang++ or g++ >4.8

For more info check out the website here

https://nccastaff.bmth.ac.uk/jmacey/GraphicsLib/
and for the demos 

https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/index.html

Theres are also other demos on github which are generally work in progress.

# Demos
## [BlankNGL](https://github.com/NCCA/BlankNGL)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/BlankNGL.png)

This is an empty boilerplate framework for NGL projects, it creates an empty window and draws nothing

## [SimpleNGL](https://github.com/NCCA/SimpleNGL)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/SimpleNGL.png)

This is the most basic version of an NGL demo, it creates a simple window in Qt and allows the manipulation of the teapot using the mouse.

## [SDLNGL](https://github.com/NCCA/SDLNGL)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/SDLNGL.png)

This is the simplest SDL / NGL demo using a basic SDL2.0 window and core profile OpenGL context

Note that this .pro file contains the calls to add the output of sdl2-config to the build using


There is a webgl demo of the sphere program [here](https://nccastaff.bournemouth.ac.uk/jmacey/WebGL/VAO1/)

## [VAOPrimitives](https://github.com/NCCA/VAOPrimitives)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/VAOPrims.png)

A simple scene using all of the built in VAO primitives, this has approx 350,000 Verts so is a good performance test of NGL

## [Camera](https://github.com/NCCA/Camera)

![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Camera.png)

This demonstrates how to create a simple Camera class as well as showing how the camera is actually made up of a simple series of matrices. This demo also demonstrates the ngl::TextClass

## [Matrix Stack](https://github.com/NCCA/MatrixStack)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/MatrixStack.png)

This demo implements a matrix stack similar to the immediate mode OpenGL push / pop matrix functionality. It can be extended to replicate basic immediate mode OpenGL pipeline functions with modern OpenGL rendering.


## [using ngl::lookAt and ngl::perspective](https://github.com/NCCA/LookAtDemos)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/lookat.png)

These two demos demonstrate using the lookAt and perspective utility classes from Util.h see individual README.md for more details

Interactive demos are [here](https://nccastaff.bournemouth.ac.uk/jmacey/WebGL/LookAt1/) and
[here] (https://nccastaff.bournemouth.ac.uk/jmacey/WebGL/LookAt2/)

## [Lights](https://github.com/NCCA/Lights)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Lights.png)

Simple demo showing how to use the ngl::Light class for point lighting
[WebGL version](https://nccastaff.bournemouth.ac.uk/jmacey/WebGL/Lights/)


## [VertexArrayObject](https://github.com/NCCA/VertexArrayObject)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/VAO.png)

A series of demos to show how to create a VertexArrayObject from different types of data. There are examples of how to create a simple boid shape as I was getting fed up of flocking teapots!

## [ShadingModels](https://github.com/NCCA/ShadingModels)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Shading.png)

A series of examples to demonstrate different shaders and techniques in glsl. Eventually I'm going to replace all of this with a simpler demo as most of the code in these examples is very similar.



## [Demo showing how to use ngl::VertexArrayObject](https://github.com/NCCA/KleinBottle)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Klein.png)

This program demonstrates the production of a Klein bottle based on the code from this excellent [website](http://paulbourke.net/geometry/klein/) It uses the ngl::VertexArrayObject class

## [TextureDemos](https://github.com/NCCA/Textures)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/texture.png)

A collection of demos showing how to use textures in ngl including examples of loading from a QImage.
## [Texture Compression](https://github.com/NCCA/TextureCompressor)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/TextureComp.png)

A series of demos to show how to create and then use [DXT](http://en.wikipedia.org/wiki/S3_Texture_Compression) compressed textures.

[Compressor](https://github.com/NCCA/TextureCompressor/tree/master/Compressor) Is a simple command line tool to create basic DxT1,3,5 textures to be used with [glCompressedTexImage2D](https://www.khronos.org/opengles/sdk/docs/man/xhtml/glCompressedTexImage2D.xml) formats.
[DXTViewer](https://github.com/NCCA/TextureCompressor/tree/master/DXTViewer) is a simple tool to load in the compressed files and view them. You can specify the name of the file on the command line or use the file open dialog presented at startup. Use o to reload a file.

## [ImageHeightMap](https://github.com/NCCA/ImageHeightMap)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/ImageHeighmap.png)

This demo shows how to read in an image and create terrain from it by using one of the channels as the height of the vertex in the y.

## [ObjDemo](https://github.com/NCCA/ObjDemo)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/obj.png)

Loads a mesh from an obj file using ngl::Obj and displays it.

[Interactive WebGL demo](https://nccastaff.bournemouth.ac.uk/jmacey/WebGL/ObjDemo/)

## [GameKeyControl](https://github.com/NCCA/GameKeyControl)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/GameKeyControl.png)

A demonstration on how to do game style multi key controls within Qt

## [AdvancedGameKeyControl](https://github.com/NCCA/AdvancedGameKeyControl)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/GameKeyControl.png)

A demonstration on how to do game style multi key controls within Qt and record them

## [SDLJoyPad](https://github.com/NCCA/SDLJoyPad)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/JoyPad.png)

This demo requires SDL 2.0 and a wireless xbox controller. Under the mac you can install this driver. Under linux you may have to install the xpad kernel driver

So far it has not been tested under windows and the button mappings may be different.

## [Interpolation](https://github.com/NCCA/Interpolation)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Interp.png)

This demo demonstrates the different interpolation templates in ngl, see this [blog post](http://jonmacey.blogspot.co.uk/2010/11/interpolation.html)


## [QuatSlerp](https://github.com/NCCA/QuatSlerp)

![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/SLERP.png)

This demo shows how the Quaternion spherical interpolation works. Interactive WebGL [demo](https://nccastaff.bournemouth.ac.uk/jmacey/WebGL/QuatSlerp/)

## [CurveDemos](https://github.com/NCCA/CurveDemos)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Curve.png)

Two demos showing how to use the ngl::BezierCurve class, including an example of exporting from maya using a simple script

## [Collision Demos](https://github.com/NCCA/Collisions)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Collisions.png)

A series of programs showing Ray-Sphere, Ray-Triangle, Sphere-Sphere, Sphere-Plane collision detection algorithms

An interactive WebGL [demo](https://nccastaff.bournemouth.ac.uk/jmacey/WebGL/RaySphere/)

## [OctreeAbstract](https://github.com/NCCA/OctreeAbstract)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Octree.png)

An Abstract Octree template to use in your own projects, this code is originally writen by my collegue Dr Xiaosong Yangfor his advanced collision detection lectures and templated and ported to ngl by me.
Interactive WebGL demo [here](https://nccastaff.bournemouth.ac.uk/jmacey/WebGL/Octree/)

## [Particle Demos](https://github.com/NCCA/ParticleSystem)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Particles.png)

Simple particle system demos, need to update these and add some more at some stage.

# [ParticleFactory](https://github.com/NCCA/ParticleFactory)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/ParticleFactory.png)

This demo demonstrates the use of the [factory pattern](http://en.wikipedia.org/wiki/Factory_method_pattern) and [runtime polymorphism](http://en.wikipedia.org/wiki/Polymorphism_(computer_science))

## [ColourSelection](https://github.com/NCCA/ColourSelection)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/ColourSelect.png)

Picking of objects using Colour values based on this [post](http://content.gpwiki.org/index.php/OpenGL_Selection_Using_Unique_Color_IDs)

## [Point Bake Demos](https://github.com/NCCA/PointBake)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/PointBake.png)

The NCCA PointBake format is a simple xml format for storing per vertex animation data, presented in these demos are maya scripts to export in the format and some demos to show how to load and visualise this data.

## [Morph Objects](https://github.com/NCCA/MorphObj)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Morph.png)

Morphing meshes using shaders. based on the paper [here](http://http.developer.nvidia.com/GPUGems3/gpugems3_ch03.html)

## [Morph Objects (Texture Buffer Objects)](https://github.com/NCCA/MorphObjTBO)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Morph.png)

Morphing meshes using shaders and texture buffer objects. based on the paper [here](http://http.developer.nvidia.com/GPUGems3/gpugems3_ch03.html)

## [Facial Animation](https://github.com/NCCA/FacialAnimation)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Face.png)

Simple Facial animation using blen shape meshes and texture buffer objects

## [Using libassimp to load meshes](https://github.com/NCCA/AssetImportDemos)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Assimp.png)

How to load and animate meshes using assimp

## [Embeded Python](https://github.com/NCCA/EmbedPython)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/EmbedPy.png)

This demo show how to embed the pyhton C interpretor into your own code and run python scripts

## [QtNGL](https://github.com/NCCA/QtNGL)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/QtNGL.png)

How to use the Qt GUI with NGL

## [Mass Spring System using RK 4 integration](https://github.com/NCCA/MassSpring)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/MassSpring.png)

This demonstrates a simple spring using RK4 integration as shown [here](http://gafferongames.com/game-physics/)

## [Affine Transforms](https://github.com/NCCA/AffineTransforms)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Affine.png)

A demonstration of affine transforms using matrices (mainly used for teaching maths)

## [FrustumCull](https://github.com/NCCA/FrustumCull)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Frustrum.png)

Added frustum culling to the ngl::Camera class, this demo shows how to use it, most of the code is based on the article [here](http://www.lighthouse3d.com/tutorials/view-frustum-culling/)

## [Geometry Shaders](https://github.com/NCCA/GeometryShaders)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/GeoShader.png)

Simple Geometry shader demo

## [Tesselation shader](https://github.com/NCCA/TessellationShader)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Tessellation.png)

This demo is the one written for [this](http://jonmacey.blogspot.co.uk/2013/05/glsl-tessellation-shaders-under-mac-osx.html) blog post and implements [this](http://prideout.net/blog/?p=48) code

## [Animated Textures](https://github.com/NCCA/AnimatedTextures)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Fire.png)

This demo uses several sprite sheets of fire to generate an animated fire using billboards. The billboards are generated on the GPU using a geometry shader and the data for the frames / animation is passes using attributes.

## [Instancing](https://github.com/NCCA/Instancing) 
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Instancing.png)

A number of demos showing how instancing in OpenGL works

## [Normal Mapping](https://github.com/NCCA/NormalMapping)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/NormalMapping.png)

This demo uses the ngl::Obj and ngl::VertexArrayObject classes to read in a mesh then construct an extended VAO passing in Tangents and Bi-Tangents (BiNormals) to glsl as attributes. This is then used to do normal mapping along the lines of [this](http://www.ozone3d.net/tutorials/bump_mapping.php)

## [Using Framebuffer Objects](https://github.com/NCCA/FBODemos)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/FBO.png)

A number of demos showing how to use Frame buffer objects, including real time shadows and render to FBO demos

## [Bullet Physics and NGL](https://github.com/NCCA/BulletNGL)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Bullet.png)

Using the Bullet Physics with NGL, the demo has basic wrappers for the Physics world and rigid bodies, it also uses the ngl::Obj to load low-res collision meshes and uses higher detail ones for the drawing.

For more details read the user [guide](http://bulletphysics.org/wordpress/) of Bullet.
## [Bullet Physics and NGL](https://github.com/NCCA/BulletTower)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/BulletTower.png)

Using the Bullet Physics with NGL, the demo has basic wrappers for the Physics world and rigid bodies It then procedurally generates a tower which the user can demolish.

An interactive WebGL demo is [here](https://nccastaff.bournemouth.ac.uk/jmacey/WebGL/BulletTower/)
For more details read the user [guide](http://bulletphysics.org/wordpress/) of Bullet.


## [ODE NGL](https://github.com/NCCA/ODENGL)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/ODENGL.png)

Using the ODE Physics engine 


## [Using the Kinect with NGL](https://github.com/NCCA/KinectMDI)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Kinect.png)

This demo shows how to use the kinect with the OpenKinect drivers and Qt / ngl. The code base is a modified version of my Qt Kinect Reference design which can be seen here. You will need to install the libfreenect drivers


## [Using the Kinect with NGL and OpenCV](https://github.com/NCCA/OpenCVKinect)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/OpenCV.png)

This demo shows how to use the kinect with the OpenKinect drivers and Qt / ngl. The code base is a modified version of my Qt Kinect Reference design which can be seen here. You will need to install the libfreenect drivers

This has issues on the mac due to the C++ compiler and OpenCV

## [Sponza Demo](https://github.com/NCCA/Sponza)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Sponza.png)

A basic framework to load a Wavefront OBJ file with groups and an MTL file with textures and draw the scene as efficiently as possible. The source contains the models and textures from here and is quite large


For a detailed look at how this work see the following blog posts

[The Initial Design](http://jonmacey.blogspot.co.uk/2012/11/sponza-demo-pt-1-initial-design.html)

[The mtl Class](http://jonmacey.blogspot.co.uk/2012/11/sponza-demo-pt-2-mtl-class.html)

[GroupedObj class](http://jonmacey.blogspot.co.uk/2012/11/sponza-demo-pt-3-groupedobj-class.html)

## [Sponza Oculus Rift Demo](https://github.com/NCCA/SponzaRift)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Oculus.png)

This builds on the original sponza demo and adds oculus rift support, this is very much 
work in progress and needs quite a bit of tidying up.

You will need to install the oculus SDK and adjust the path in the .pro file to get it working.

This version also loads the binary Model and Material file, you may have to re-create this using the save and load methods as the binary file may not transfer to different operating systems.

## [Box2D Demo](https://github.com/NCCA/Box2D)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Box2D.png)

A simple demo to show Box2D being used with ngl

## [Export from Maya to Box2D](https://github.com/NCCA/Box2DExport)
![](https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Box2D.png)

A simple example of an exported then using it in box 2D see the python files for more details
