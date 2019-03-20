TEMPLATE=subdirs
# if on mac and linux build all projects
macx:SUBDIRS+= NGL PyNGL tests/NGLTests.pro PyNGL/tests/PyTests.pro
linux*:SUBDIRS+= NGL PyNGL tests/NGLTests.pro PyNGL/tests/PyTests.pro
# on windows only do the core NGL lib for ease.
win32*:SUBDIRS+= NGL
tests.depends=NGL
OTHER_FILES+=.travis.yml
OTHER_FILES+=.circleci/config.yml
