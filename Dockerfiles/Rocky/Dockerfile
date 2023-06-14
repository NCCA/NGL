#set the base image
FROM rockylinux:9.2
# install tools
RUN dnf -y groupinstall "Development Tools" && \
dnf -y --enablerepo=crb install g++ wget vim  ninja-build cmake \
mesa-libGL-devel  libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel openssl-devel



WORKDIR /home/ncca
ENV HOME /home/ncca
ENV PATH=$PATH:/usr/local/bin
# the cmake version in the repo is too old for vcpkg!
RUN wget https://github.com/Kitware/CMake/releases/download/v3.23.2/cmake-3.23.2.tar.gz && \
tar -zxvf cmake-3.23.2.tar.gz && \
cd cmake-3.23.2 && \
./bootstrap  && \
make && make install 

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
# set default command to run  when starting the container in this case run the unit tests
ENTRYPOINT ["/bin/bash","-c"]
WORKDIR /home/ncca/NGLBuild/build
CMD [ "./NGLTests -g" ]
