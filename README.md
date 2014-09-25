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

##[VertexArrayObject](https://github.com/NCCA/VAOPrimitives)
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/VAO.png)

A series of demos to show how to create a VertexArrayObject from different types of data. There are examples of how to create a simple boid shape as I was getting fed up of flocking teapots!

There is a webgl demo of the sphere program [here](http://nccastaff.bournemouth.ac.uk/jmacey/WebGL/VAO1/)

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
