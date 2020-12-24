# Mac install

To install the compilers for MacOSX we can use the xcode app from the app store. One installed in the terminal depending upon the OS version you may need to grant permissions for the first run. To do this open a teminal window and type 

```clang++ --version``` 

and follow the prompts.

## NGL dependancies

NGL has a number of dependancies which can be installed using vcpkg. However before that we need to install some other packages.

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
.\vcpkg install openimageio
.\vcpkg install rapidjson
.\vcpkg install rapidxml
.\vcpkg install fmt
.\vcpkg install freetype
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






