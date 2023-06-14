# Dockerfiles

This folder contains the Dockerfiles for different operating systems to allow quick tests for new os versions etc. Each docker file is in it's own named folder. 

These files are useful as you can see what base requirements are needed for each of the operating systems, in particular what development librates and tools are needed. Typically you will need to install some of these on your host machine to build NGL.

In particular look for the RUN section and the use of either dnf, apt-get or yum to install the required packages. There is also an ENV section which may be used to setup paths required for the build.

In some cases we need to install a newer version of cmake than the system packages as vcpkg requires a newer version. In this case we install cmake from source and set the path to use this version.

If the repo builds it should also run the NGLTests however you can't really see them as they are running in a headless mode. To see the tests you will need to run the docker image and then run the tests manually.

## Linux Versions

I have chosen all of the main popular distro's as well as the two recommended by the VFX Reference platform (Rocky Linux and Alma Linux). [https://vfxplatform.com/linux/](https://vfxplatform.com/linux/).

The main lab version at the NCCA is RHEL 8.5 which will be moving to 9.x soon. There is no Dockerfile for this as it requires a subscription to download the image. However Rocky and Alma are both based on RHEL so should be close enough.

## [Alma Linux](Alma/Dockerfile)

This is a basic Alma Linux image with the required packages installed. It is based on the latest Alma Linux image.

```bash
docker build -t ngl-alma .
docker run -it ngl-alma
cd NGLBuild/build
./NGLTests -g 
```

## [Rocky Linux](Rocky/Dockerfile)

This is a basic Rocky Linux image with the required packages installed. It is based on the latest Rocky Linux image.

```bash  
docker build -t ngl-rocky .
docker run -it ngl-rocky
cd NGLBuild/build
./NGLTests -g 
```

## [Fedora](Fedora/Dockerfile)

This is a basic fedora image with the required packages installed. It is based on the latest fedora image.

```bash
docker build -t ngl-fedora .
docker run -it ngl-fedora
cd NGLBuild/build
./NGLTests -g 
```

## [Ubuntu](Ubuntu/Dockerfile)

This is a basic ubuntu image with the required packages installed. It is based on the latest ubuntu image.

```bash    
docker build -t ngl-ubuntu .
docker run -it ngl-ubuntu
cd NGLBuild/build
./NGLTests -g 
```

## [Debian](Debian/Dockerfile)

This is a basic Debian image with the required packages installed. It is based on the latest ubuntu image.

```bash    
docker build -t ngl-debian .
docker run -it ngl-debian
cd NGLBuild/build
./NGLTests -g 
```
