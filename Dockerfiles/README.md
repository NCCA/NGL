# Dockerfiles

This folder contains the Dockerfiles for different operating sytems to allow quick tests for new os versions etc. Each docker file is in it's own named folder

## Fedora 

This builds a fedora:latest image installs all the pre-requiste libs and clones NGL 

```
docker build -t ngl-fedora .
```