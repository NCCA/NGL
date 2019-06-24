TEMPLATE=subdirs
# if on mac and linux build all projects
macx|linux {
    SUBDIRS= NGL PyNGL tests/NGLTests.pro PyNGL/tests/PyTests.pro
}
# on windows only do the core NGL lib for ease.
win32 {
    message("Doing winwindows subdir")
    SUBDIRS= NGL tests/NGLTests.pro
}
tests.depends=NGL
OTHER_FILES+=.travis.yml
OTHER_FILES+=.circleci/config.yml
