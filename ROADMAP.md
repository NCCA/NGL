# NGL 8 Roadmap

This document will outline the major design / structural changes being made to NGL for release 8 with the aim of it being ready for academic year 2020/21

## Remove Qt as a Core requirement of NGL

Whilst Qt will still be used for OpenGL context generation and as an option fror image loading and fonts in NGL, it will no longer need to be used to build by default. This will be a command line option (as the current image loading library code already is).

## Use cmake as the build tool

Cmake will be the only build tool used for NGL, this will allow for the use of many ide's that now support cmake, this will also make the Windows build easier as MSBuild can be used after cmake.

Qt Creator supports cmake projects as does visual studio.

## vcpkg support

All dependencies will be installed via vcpkg on all platforms to make it easier to setup and run NGL / Demos (excluding Qt which will use the normal processes). This will integrate with cmake and also make University setup easier under windows.

# Library Design Changes

The following changes will be made to the core design of NGL

## Remove Singleton classes

All Singleton classes  (ShaderLib, VAOPrimitives, Random,Init) to remove the singleton and use static data / methods. ( ```ngl::VAOPrimitives::draw( ngl::teapot);``` for example).

## Begin to de-couple render code

We need to begin the designing the code to allow multiple graphics API's such as vulkan and metal, this will help to future proof everything. Not sure how t do this but will be a major part of any re-designs we do.

## Python Bindings

Will begin to make python 3 the default python API and make the interface more pythonic (and more python 3 so return iterators / objects etc). Will still retain python 2 bindings for now.

## Remove RapidXML for point bake

Use JSON instead, will need to re-write the demo code
