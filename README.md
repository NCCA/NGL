#NGL the NCCA Graphics Library
This is the main source branch for the NCCA Graphics Library ngl.

It needs to be built using QtCreator and you will also need to install
boost

For more info check out the website here

http://nccastaff.bmth.ac.uk/jmacey/GraphicsLib/
and for the demos

http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/index.html
#Demos
##[BlankNGL](https://github.com/NCCA/BlankNGL)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/BlankNGL.png)

This is an empty boilerplate framework for NGL projects, it creates an empty window and draws nothing

##[SimpleNGL](https://github.com/NCCA/SimpleNGL)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/SimpleNGL.png)

This is the most basic version of an NGL demo, it creates a simple window in Qt and allows
the manipulaiton of the teapot using the mouse.

##[SDLNGL](https://github.com/NCCA/SDLNGL)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/SDLNGL.png)

This is the simplest SDL / NGL demo using a basic SDL2.0 window and core profile OpenGL context

Note that this .pro file contains the calls to add the output of sdl2-config to the build using


There is a webgl demo of the sphere program [here](http://nccastaff.bournemouth.ac.uk/jmacey/WebGL/VAO1/)

##[VAOPrimitives](https://github.com/NCCA/VAOPrimitives)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/VAOPrims.png)

A simple scene using all of the built in VAO primitives, this has approx 350,000 Verts so is a good performance test of NGL

##[Camera](https://github.com/NCCA/Camera)

![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Camera.png)

This demonstrates the use of the ngl::Camera class as well as showing how the camera is actually made up of a simple series of matrices

##[SDLNGL](https://github.com/NCCA/SDLTTF)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/TTFText.png)

As the ngl::Text class is reliant upon QFont at present this class is a drop in replacment using  [sdl-ttf] (https://www.libsdl.org/projects/SDL_ttf/)
eventually all of this will be merged into the core ngl with compile time flags to choose the text rendering engine.

##[using ngl::lookAt and ngl::perspective](https://github.com/NCCA/LookAtDemos)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/lookat.png)

These two demos demonstrate using the lookAt and perspective utility classes from Util.h see individual README.md for more details

Interactive demos are [here](http://nccastaff.bournemouth.ac.uk/jmacey/WebGL/LookAt1/) and
[here] (http://nccastaff.bournemouth.ac.uk/jmacey/WebGL/LookAt2/)

##[Lights](https://github.com/NCCA/Lights)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Lights.png)

Simple demo showing how to use the ngl::Light class for point lighting
[WebGL version](http://nccastaff.bournemouth.ac.uk/jmacey/WebGL/Lights/)

##[SpotLight](https://github.com/NCCA/SpotLight)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Spotlight.png)

This demo show the ngl::SpotLight class in action
[interactive webgl demo](http://nccastaff.bournemouth.ac.uk/jmacey/WebGL/Spotlights/)

##[ShadingModels](https://github.com/NCCA/ShadingModels)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Shading.png)

A series of examples to demonstrate different shaders and techniques in glsl. Eventually I'm going to replace all of this with a simpler demo as most of the code in these examples is very similar.

##[VertexArrayObject](https://github.com/NCCA/VertexArrayObject)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/VAO.png)

A series of demos to show how to create a VertexArrayObject from different types of data. There are examples of how to create a simple boid shape as I was getting fed up of flocking teapots!

## [Demo showing how to use ngl::VertexArrayObject](https://github.com/NCCA/KleinBottle)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Klein.png)

This program demonstrates the production of a Klein bottle based on the code from this excellent [website](http://paulbourke.net/geometry/klein/) It uses the ngl::VertexArrayObject class

##[TextureDemos](https://github.com/NCCA/Textures)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/texture.png)

A collection of demos showing how to use textures in ngl including examples of loading from a QImage.

##[ImageHeightMap](https://github.com/NCCA/ImageHeightMap)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/ImageHeighmap.png)

This demo shows how to read in an image and create terrain from it by using one of the channels as the height of the vertex in the y.

##[ObjDemo](https://github.com/NCCA/ObjDemo)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/obj.png)

Loads a mesh from an obj file using ngl::Obj and displays it.

[Interactive WebGL demo](http://nccastaff.bournemouth.ac.uk/jmacey/WebGL/ObjDemo/)

##[GameKeyControl](https://github.com/NCCA/GameKeyControl)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/GameKeyControl.png)

A demonstration on how to do game style multi key controls within Qt

##[AdvancedGameKeyControl](https://github.com/NCCA/AdvancedGameKeyControl)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/GameKeyControl.png)

A demonstration on how to do game style multi key controls within Qt and record them

##[SDLJoyPad](https://github.com/NCCA/SDLJoyPad)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/JoyPad.png)

This demo requires SDL 2.0 and a wireless xbox controller. Under the mac you can install this driver. Under linux you may have to install the xpad kernel driver

So far it has not been tested under windows and the button mappings may be different.

##[Interpolation](https://github.com/NCCA/Interpolation)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Interp.png)

This demo demonstrates the different interpolation templates in ngl, see this [blog post](http://jonmacey.blogspot.co.uk/2010/11/interpolation.html)

##[QuatSlerp](https://github.com/NCCA/QuatSlerp)

![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/SLERP.png)

This demo shows how the Quaternion spherical interpolation works. Interactive WebGL [demo](http://nccastaff.bournemouth.ac.uk/jmacey/WebGL/QuatSlerp/)

##[CurveDemos](https://github.com/NCCA/CurveDemos)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Curve.png)

Two demos showing how to use the ngl::BezierCurve class, including an example of exporting from maya using a simple script

##[Collision Demos](https://github.com/NCCA/Collisions)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Collisions.png)

A series of programs showing Ray-Sphere, Ray-Triangle, Sphere-Sphere, Sphere-Plane collision detection algorithms

An interactive WebGL [demo](http://nccastaff.bournemouth.ac.uk/jmacey/WebGL/RaySphere/)

##[OctreeAbstract](https://github.com/NCCA/OctreeAbstract)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Octree.png)

An Abstract Octree template to use in your own projects, this code is originally writen by my collegue Dr Xiaosong Yangfor his advanced collision detection lectures and templated and ported to ngl by me.
Interactive WebGL demo [here](http://nccastaff.bournemouth.ac.uk/jmacey/WebGL/Octree/)

##[Particle Demos](https://github.com/NCCA/ParticleSystem)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Particles.png)

Simple particle system demos, need to update these and add some more at some stage.

#[ParticleFactory](https://github.com/NCCA/ParticleFactory)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/ParticleFactory.png)

This demo demonstrates the use of the [factory pattern](http://en.wikipedia.org/wiki/Factory_method_pattern) and [runtime polymorphism](http://en.wikipedia.org/wiki/Polymorphism_(computer_science))

##[ColourSelection](https://github.com/NCCA/ColourSelection)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/ColourSelect.png)

Picking of objects using Colour values based on this [post](http://content.gpwiki.org/index.php/OpenGL_Selection_Using_Unique_Color_IDs)

##[Point Bake Demos](https://github.com/NCCA/ColourSelection)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/PointBake.png)

The NCCA PointBake format is a simple xml format for storing per vertex animation data, presented in these demos are maya scripts to export in the format and some demos to show how to load and visualise this data.

##[Morph Objects](https://github.com/NCCA/MorphObj)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Morph.png)

Morphing meshes using shaders. based on the paper [here](http://http.developer.nvidia.com/GPUGems3/gpugems3_ch03.html)

##[Morph Objects (Texture Buffer Objects)](https://github.com/NCCA/MorphObjTBO)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Morph.png)

Morphing meshes using shaders and texture buffer objects. based on the paper [here](http://http.developer.nvidia.com/GPUGems3/gpugems3_ch03.html)

##[Facial Animation](https://github.com/NCCA/FacialAnimation)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Face.png)

Simple Facial animation using blen shape meshes and texture buffer objects

##[Using libassimp to load meshes](https://github.com/NCCA/AssetImportDemos)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Assimp.png)

How to load and animate meshes using assimp

##[Embeded Python](https://github.com/NCCA/EmbedPython)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/EmbedPy.png)

This demo show how to embed the pyhton C interpretor into your own code and run python scripts

##[QtNGL](https://github.com/NCCA/QtNGL)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/QtNGL.png)

How to use the Qt GUI with NGL

##[Mass Spring System using RK 4 integration](https://github.com/NCCA/MassSpring)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/MassSpring.png)

This demonstrates a simple spring using RK4 integration as shown [here](http://gafferongames.com/game-physics/)

##[Affine Transforms](https://github.com/NCCA/AffineTransforms)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Affine.png)

A demonstration of affine transforms using matrices (mainly used for teaching maths)

##[FrustumCull](https://github.com/NCCA/FrustumCull)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Frustrum.png)

Added frustum culling to the ngl::Camera class, this demo shows how to use it, most of the code is based on the article [here](http://www.lighthouse3d.com/tutorials/view-frustum-culling/)

##[Geometry Shaders](https://github.com/NCCA/GeometryShaders)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/GeoShader.png)

Simple Geometry shader demo

##[Tesselation shader](https://github.com/NCCA/TessellationShader)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Tessellation.png)

This demo is the one written for [this](http://jonmacey.blogspot.co.uk/2013/05/glsl-tessellation-shaders-under-mac-osx.html) blog post and implements [this](http://prideout.net/blog/?p=48) code

##[Animated Textures](https://github.com/NCCA/AnimatedTextures)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Fire.png)

This demo uses several sprite sheets of fire to generate an animated fire using billboards. The billboards are generated on the GPU using a geometry shader and the data for the frames / animation is passes using attributes.

##[Instancing](https://github.com/NCCA/Instancing) 
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Instancing.png)

A number of demos showing how instancing in OpenGL works

##[Normal Mapping](https://github.com/NCCA/NormalMapping)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/NormalMapping.png)

This demo uses the ngl::Obj and ngl::VertexArrayObject classes to read in a mesh then construct an extended VAO passing in Tangents and Bi-Tangents (BiNormals) to glsl as attributes. This is then used to do normal mapping along the lines of [this](http://www.ozone3d.net/tutorials/bump_mapping.php)

##[Using Framebuffer Objects](https://github.com/NCCA/FBODemos)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/FBO.png)

A number of demos showing how to use Frame buffer objects, including real time shadows and render to FBO demos

##[Bullet Physics and NGL](https://github.com/NCCA/BulletNGL)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Bullet.png)

Using the Bullet Physics with NGL, the demo has basic wrappers for the Physics world and rigid bodies, it also uses the ngl::Obj to load low-res collision meshes and uses higher detail ones for the drawing.

For more details read the user [guide](http://bulletphysics.org/wordpress/) of Bullet.

##[ODE NGL](git@github.com:NCCA/ODENGL.git)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/ODENGL.png)

Using the ODE Physics engine 


##[Using the Kinect with NGL](https://github.com/NCCA/KinectMDI)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Kinect.png)

This demo shows how to use the kinect with the OpenKinect drivers and Qt / ngl. The code base is a modified version of my Qt Kinect Reference design which can be seen here. You will need to install the libfreenect drivers


##[Using the Kinect with NGL and OpenCV](https://github.com/NCCA/OpenCVKinect)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/OpenCV.png)

This demo shows how to use the kinect with the OpenKinect drivers and Qt / ngl. The code base is a modified version of my Qt Kinect Reference design which can be seen here. You will need to install the libfreenect drivers

This has issues on the mac due to the C++ compiler and OpenCV

##[Sponza Demo](https://github.com/NCCA/Sponza)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Sponza.png)

A basic framework to load a Wavefront OBJ file with groups and an MTL file with textures and draw the scene as efficiently as possible. The source contains the models and textures from here and is quite large


For a detailed look at how this work see the following blog posts

[The Initial Design](http://jonmacey.blogspot.co.uk/2012/11/sponza-demo-pt-1-initial-design.html)

[The mtl Class](http://jonmacey.blogspot.co.uk/2012/11/sponza-demo-pt-2-mtl-class.html)

[GroupedObj class](http://jonmacey.blogspot.co.uk/2012/11/sponza-demo-pt-3-groupedobj-class.html)

##[Box2D Demo](https://github.com/NCCA/Box2D)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Box2D.png)

A simple demo to show Box2D being used with ngl

##[Export from Maya to Box2D](https://github.com/NCCA/Box2DExport)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Box2D.png)

A simple example of an exported then using it in box 2D see the python files for more details
