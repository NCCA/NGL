TEMPLATE=subdirs
SUBDIRS+= NGL PyNGL tests/NGLTests.pro PyNGL/tests/PyTests.pro
tests.depends=NGL
OTHER_FILES+=.travis.yml
OTHER_FILES+=.circleci/config.yml
