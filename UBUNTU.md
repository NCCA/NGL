# Ubuntu Install

The follow is a minimal set of install instructions for installing NGL with Ubuntu (tested on 20 LTS) and using vcpkg for extra libs. You will also need to install Qt 5.x and add it to your path.

## Getting Started

The following libs needs to be installed using apt

```
sudo apt-get install -y curl build-essential mesa-common-dev  libxinerama-dev  libglu1-mesa-dev  libxcursor-dev libxrandr-dev libxrandr-dev libxi-dev libxxf86vm-dev
```

## Install vcpkg

vcpkg is a tool which allows you to install libraries under windows. I use this to help install the required libraries for NGL. Follow the install instructions here  [https://github.com/microsoft/vcpkg](https://github.com/microsoft/vcpkg). It is important to install this in the root of your home directory to ensure this is correct open terminal and type ```cd  ~``` before running the commands to install vcpkg. NGL will use ``` $HOME/vcpkg ``` in all the build scripts to ensure things are in the correct locations.

Once vcpkg is installed the following libraries need to be added.

```
cd vcpkg
.\vcpkg install gtest
.\vcpkg install glm
.\vcpkg install glfw3
.\vcpkg install gl3w
.\vcpkg install rapidjson
.\vcpkg install rapidxml
.\vcpkg install fmt
.\vcpkg install freetype
```

We can now download and clone the NGL repo.

```
git clone git@github.com:/NCCA/NGL ~/NGLBuild
cd NGLBuild
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_INSTALL_PREFIX:PATH=~/NGL/  ..
make -j 12
make install
```
