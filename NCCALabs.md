# NGL Build for NCCA Labs

All of the tools and libraries needed for NGL are already installed in the labs under Linux so install and setup are quite easy. We will first clone to NGLBuild

```
git clone git@github.com:/NCCA/NGL ~/NGLBuild
cd NGLBuild
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=~/NGL  ..
make -j 12
make install
```

## Building PyNGL

To additionally build the pyngl we need to do the following

```
cmake -DCMAKE_INSTALL_PREFIX:PATH=~/NGL -DBUILD_PYNGL=True ..
```

However this will use the default system python. To use other versions of python such as those installed with pyenv you need to specify the correct python executable.

```
cmake -DCMAKE_INSTALL_PREFIX:PATH=~/NGL -DPYTHON_EXECUTABLE:FILEPATH=~/.pyenv/shims/python -DBUILD_PYNGL=True ..
```

## Building NGL Demos

All of the NGL demos can be build using the same process and setting the CMAKE_PREFIX_PATH to point to the NGL install directory.

```
cmake -DCMAKE_PREFIX_PATH=~/NGL:/opt/qt/5.12.3/gcc_64/lib/cmake/ .. 
```

## Updates for .bash_profile

To make the process easier for future builds it is best to add the following to your .bash_profile

```
export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:~/NGL
```

Now all NGL demos can be built using

```
cd [demodir]
mkdir build
cd build
cmake ..
make -j 4
d

```
