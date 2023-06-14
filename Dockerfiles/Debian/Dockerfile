#set the base image
FROM debian:latest
# install tools
RUN apt-get update && \
apt install -y build-essential wget vim cmake ninja-build && \
apt install -y libgl-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev && \
apt install -y git curl  zip unzip tar pkg-config python3 


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
# set default command to run  when starting the container in this case run the unit tests
ENTRYPOINT ["/bin/bash","-c"]
WORKDIR /home/ncca/NGLBuild/build
CMD [ "./NGLTests -g" ]
