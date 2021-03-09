# NGL Build for NCCA Labs

All of the tools and libraries needed for NGL are already installed in the labs under Linux so install and setup are quite easy. We will first clone to NGLBuild

```
git clone git@github.com:/NCCA/NGL ~/NGLBuild
cd NGLBuild
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=~/NGL -DCMAKE_TOOLCHAIN_FILE=/public/devel/2020/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_MODULE_PATH=/opt/qt/5.12.3/gcc_64/lib/cmake   ..
make -j 12
make install
```

## Building NGL Demos

All of the NGL demos can be build using the same process and setting the CMAKE_PREFIX_PATH to point to the NGL install directory.

```
cmake -DCMAKE_PREFIX_PATH=~/NGL:/opt/qt/5.12.3/gcc_64/lib/cmake/ .. 
```

## Updates for .bash_profile

To make the process easier for future builds it is best to add the following to your .bash_profile

```
export CMAKE_TOOLCHAIN_FILE=/public/devel/2020/vcpkg/scripts/buildsystems/vcpkg.cmake
export CMAKE_MODULE_PATH=/opt/qt/5.12.3/gcc_64/lib/cmake
export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:~/NGLcmake:/opt/qt/5.12.3/gcc_64/lib/cmake/ 
```

Now all NGL demos can be build using

```
cd [demodir]
mkdir build
cd build
cmake ..
make -j 4
d

```
