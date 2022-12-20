@echo off
set HOME=%HOMEDRIVE%%HOMEPATH%\
cd %HOME%
IF EXIST %HOME%\vcpkg (
  echo It seems you have a vcpkg folder already You may just need to install the following components
  echo .\vcpkg install  gtest:x64-windows glm:x64-windows glfw3:x64-windows openimageio:x64-windows rapidjson:x64-windows rapidxml:x64-windows fmt:x64-windows freetype:x64-windows
  exit 0
) ELSE (
  echo Installing vcpkg
  git clone https://github.com/microsoft/vcpkg
  cd vcpkg
  .\bootstrap-vcpkg.bat -disableMetrics
  echo Installing the ngl pre-requisites for x64 this may take some time.
  .\vcpkg install  gtest:x64-windows glm:x64-windows glfw3:x64-windows gl3w:x64-windows rapidjson:x64-windows rapidxml:x64-windows fmt:x64-windows freetype:x64-windows
  echo Installation completed, please read the instructions on installing NGL
)