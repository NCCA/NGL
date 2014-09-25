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

