# Installing NGL under WSL

First follow the steps to install WSLg or go to the app store and install the Ubuntu 22.04.2 LTS app. 

You will also need the correct drivers (I test with nVidia game drivers which support accelerated GPU under wsl)





   
    4  sudo apt-get update && sudo apt install -y build-essential wget vim cmake ninja-build && apt install -y libgl-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev && apt install -y git curl  zip unzip tar pkg-config python3 
    5  sudo apt-get apt install -y git curl  zip unzip tar pkg-config python3 
    6  sudo apt-get install -y git curl  zip unzip tar pkg-config python3 
    7  git clone https://github.com/Microsoft/vcpkg.git ~/vcpkg && cd ~/vcpkg && ./bootstrap-vcpkg.sh 
    8  ./vcpkg install install gtest glm gl3w glfw3 rapidjson rapidxml fmt freetype openimageio  
    9  ./vcpkg install gtest glm gl3w glfw3 rapidjson rapidxml fmt freetype openimageio  
   10  ./vcpkg install gl3w
   11  code       /home/jmacey/vcpkg/buildtrees/gl3w/config-x64-linux-out.log
   12  sudo apt-get install -y mesa-devel
   13  apt search mesa
   14  apt search mesa-gl
   15  sudo apt install mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev
   16  ./vcpkg install gl3w
   17  ./vcpkg install install gtest glm gl3w glfw3 rapidjson rapidxml fmt freetype openimageio  
   18  ./vcpkg install  gtest glm gl3w glfw3 rapidjson rapidxml fmt freetype openimageio  
   19  sudo apt install libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev pkg-config
   20  ./vcpkg install  gtest glm gl3w glfw3 rapidjson rapidxml fmt freetype openimageio  
   21  cd ..
   22  ls
   23  git clone --depth 1 https://github.com:/NCCA/NGL ~/NGLBuild && cd ~/NGLBuild/ && cmake -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -G Ninja -B build -S . &&cd build && cmake --build .
   24  ./NGLTests 
   25  cd ..
   26  cd 
   27  ls
   28  cd vcpkg/
   29  ./vcpkg install sdl2 sdl2_image
   30  ./vcpkg install sdl2 sdl2-image
   31  cd
   32  git clone https://github.com:/NCCA/SDLNGL 
   33  cd SDLNGL/
   34  # cmake -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -G Ninja -B build -S . &&cd build && cmake --build .
   35  mkdir build
   36  cd build/
   37  ls
   38  # cmake -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -G Ninja ..
   39  ls
   40  cmake -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -G Ninja ..
   41  cmake --build .
   42  cd .
   43  cd ..
   44  ls
   45  ccd ..
   46  lcd ..
   47  ls
   48  cd ..
   49  cd NGLBuild/
   50  cd build/
   51  ls
   52  cmake -DCMAKE_INSTALL_PREFIX=
   53  cmake -DCMAKE_INSTALL_PREFIX=~/NGL ..
   54  make install
   55  cmake --build . --target install
   56  cd
   57  cd SDLNGL/
   58  cd build/
   59  cmake -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -G Ninja ..
   60  rm CMakeCache.txt 
   61  cmake -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -G Ninja -DCMAKE_PREFIX_PATH=~/NGL  ..
   62  cmake --build . --target install
   63  cmake --build . 
   64  ls
   65  ./SDLNGL 
   66  cd 
   67  history 
   68  history &>WSL.md 
   69  cd
   70  cd vcpkg/
   71  ls
   72* 
   73  ./vcpkg search Qt6 
   74  ./vcpkg search qt6
   75  ./vcpkg search qt
   76  ./vcpkg install qtbase[opengl]
   77  code       /home/jmacey/vcpkg/buildtrees/fontconfig/config-x64-linux-dbg-out.log'
   78  code       /home/jmacey/vcpkg/buildtrees/fontconfig/config-x64-linux-dbg-out.log
   79  python3
   80  python
   81  ls
   82  alias python='python3'
   83  python
   84  ./vcpkg install qtbase[opengl]
   85  code /home/jmacey/vcpkg/buildtrees/fontconfig/x64-linux-dbg/meson-logs/meson-log.txt
   86  python3 -m pip install distutils 
   87  python3 -m pip3 install distutils 
   88  pip
   89  /usr/bin/python3 -m pip3 install distutils 
   90  cd
   91  ls
   92  pwd
   93  ls -al
   94  python
   95  apt install pip
   96  sudo apt install pip
   97  cd vcpkg/
   98  ./vcpkg install qtbase[opengl]
   99  ./vcpkg install icu
  100  apt search Qt
  101  /home/jmacey/vcpkg/buildtrees/fontconfig/x64-linux-dbg/meson-logs/meson-log.txt
  102  sudo apt-get install qt5-default
  103  sudo apt-get install qt5
  104  apt search Qt6
  105  apt search rg
  106  apt search rip
  107  apt search ripgrep
  108  sudo apt install ripgrep
  109  apt search Qt6 | rg base
  110  apt search Qt6 | rg default
  111  apt search Qt6 | rg devel
  112  apt search Qt6 
  113  apt search Qt6 | rg opengl
  114  sudo apt install libqt6opengl6-dev
  115  cd
  116  git clone https://github.com:/NCCA/SimpleNGL 
  117  cd SimpleNGL/
  118  ls
  119  mkdir build
  120  cd build/
  121  history | rg cmake
  122  cmake -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -G Ninja -DCMAKE_PREFIX_PATH=~/NGL  ..
  123  cmake --build .
  124  ./SimpleNGL
  125  history | rg cmake
  126  cd
  127  ls
  128  history &>WSL.md 
