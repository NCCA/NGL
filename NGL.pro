TEMPLATE=subdirs
SUBDIRS+= NGL PyNGL tests/NGLTests.pro
tests.depends=NGL
OTHER_FILES+=.travis.yml
