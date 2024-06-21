# Mac install

To install the compilers for MacOSX we can use the xcode app from the app store. One installed in the terminal depending upon the OS version you may need to grant permissions for the first run. To do this open a teminal window and type 

```clang++ --version``` 

and follow the prompts.

## NGL dependencies

NGL has a number of dependencies which can be installed using vcpkg. However before that we need to install some other packages.

## brew 

To start with we need to have a working version of ```pkg-config``` the easiest way to install this is using [HomeBrew](https://brew.sh/). Simple install can be done using the following command in the terminal.

```/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"```

Once brew has been installed we can use

```brew install pkg-config``` 

To install pkg-config. By defaut this will be placed into ```/usr/local/bin``` which may not be in your path. To add this to your path in zsh add the following to the ```~/.zshrc``` 

```
export PATH=/usr/local/bin:$PATH
```

## cmake install 

Next we need to install cmake the easiest way is to use a pre built binary from [here](https://cmake.org/download/) follow the instructions for adding cmake to your path in the cmake-gui app.


## Install vcpkg

vcpkg is a tool which allows you to install libraries. I use this to help install the required libraries for NGL. Follow the install instructions here  [https://github.com/microsoft/vcpkg](https://github.com/microsoft/vcpkg). It is important to install this in the root of your home directory. 

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
Optionally if you wish the more powerful OpenImageIO image loading / control you can add 

```
.\vcpkg install openimageio
```

The cmake file will auto detect this install and use it.

If you wish to install the python binding you can  add 

```
.\vcpkg install pybind11
```


## Building NGL

To build NGL we need to do the following

```
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_INSTALL_PREFIX:PATH=~/NGL/  ..
make
make install
```

## Adding NGL to your path

To add NGL to your path you can add the following to your ```~/.zprofile``` file this assumes you have installed the vcpgk and NGL in your home directory.

```
export CMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake
export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:~/NGL/:~/Qt/6.3.0/macos/lib/cmake
export VCPKG_ROOT=~/vcpkg
```

To activate this you can either restart your terminal or type 

```
source ~/.zprofile
```

## Python Build with PyBind

typically this is not needed as we don't use the python binding in any courses. However if you wish to build the python binding you can do the following (assuming you have installed pybind11 using vcpkg and are using pyenv to manage your python versions)

```
cmake -DCMAKE_INSTALL_PREFIX=~/NGL -DBUILD_PYNGL=1 -DPYTHON_EXECUTABLE:FILEPATH=~/.pyenv/shims/python -DPYTHON_INCLUDE_DIRS=/Users/jmacey/.pyenv/versions/3.9.7/include/python3.9 -DPYTHON_LIBRARIES=~/.pyenv/versions/3.9.7/lib
 ..

```

or if you have the python libraries in your path you can use the following

```
cmake -DCMAKE_INSTALL_PREFIX=~/NGL -DBUILD_PYNGL=1   -DPYTHON_INCLUDE_DIR=$(python -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())") -DPYTHON_LIBRARY=$(python -c "import distutils.sysconfig as sysconfig; print(sysconfig.get_config_var('LIBDIR'))") ..

```




