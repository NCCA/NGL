#set the base image
FROM fedora:latest
# install tools
RUN dnf -y groupinstall "Development Tools" && \
dnf -y install g++ wget vim cmake  ninja-build && \
dnf -y install mesa-libGL-devel  libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel 



WORKDIR /home/ncca
ENV HOME /home/ncca
# download and install vcpkg
RUN git clone https://github.com/Microsoft/vcpkg.git ~/vcpkg && \
cd ~/vcpkg && \
./bootstrap-vcpkg.sh 

RUN VCPKG_FORCE_SYSTEM_BINARIES=1 /home/ncca/vcpkg/vcpkg install gtest glm \
gl3w glfw3 rapidjson rapidxml fmt freetype openimageio  

RUN git clone --depth 1 https://github.com:/NCCA/NGL ~/NGLBuild && \
cd ~/NGLBuild/ && \
cmake -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -G Ninja -B build -S . &&\
cd build && cmake --build .
RUN cd ~/NGLBuild/build && ./NGLTests -g
# set default command
ENTRYPOINT ["/bin/bash"]
