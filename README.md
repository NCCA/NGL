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

