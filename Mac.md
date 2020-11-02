# Mac install




cmake -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_INSTALL_PREFIX:PATH=~/NGL/  ..



## Libsquish errors

If you get errors with cmake complaining about missing Libsquish::Libsqush find this in the file "vcpkg/installed/x64-osx/share/OpenImageIO/OpenImageIOTargets.cmake"

remove the line that says
```\$<LINK_ONLY:Libsquish::Libsquish>;```

and add the following to the end of the INTERFACE_LINK_LIBRARIES line.
${_IMPORT_PREFIX}/lib/libsquish.a;

```
set_target_properties(OpenImageIO::OpenImageIO PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "OIIO_STATIC_DEFINE=1"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/../../include"
  INTERFACE_LINK_LIBRARIES "IlmBase::Imath;IlmBase::IlmThread;IlmBase::IexMath;IlmBase::Iex;IlmBase::Half;OpenEXR::IlmImfUtil;OpenEXR::IlmImf;\$<LINK_ONLY:OpenEXR::IlmImfUtil>;\$<LINK_ONLY:OpenEXR::IlmImf>;\$<\$<NOT:\$<CONFIG:DEBUG>>:${_IMPORT_PREFIX}/lib/libpng.a>;\$<\$<CONFIG:DEBUG>:${_IMPORT_PREFIX}/debug/lib/libpng16d.a>;${_IMPORT_PREFIX}/lib/libz.a;${_IMPORT_PREFIX}/lib/libz.a;${_IMPORT_PREFIX}/lib/libjpeg.a;\$<LINK_ONLY:OpenEXR::IlmImfUtil>;\$<LINK_ONLY:OpenEXR::IlmImf>;\$<\$<NOT:\$<CONFIG:DEBUG>>:${_IMPORT_PREFIX}/lib/libpng.a>;\$<\$<CONFIG:DEBUG>:${_IMPORT_PREFIX}/debug/lib/libpng16d.a>;${_IMPORT_PREFIX}/lib/libz.a;${_IMPORT_PREFIX}/lib/libz.a;${_IMPORT_PREFIX}/lib/libjpeg.a;\$<\$<NOT:\$<CONFIG:DEBUG>>:${_IMPORT_PREFIX}/lib/libtiff.a>;\$<\$<CONFIG:DEBUG>:${_IMPORT_PREFIX}/debug/lib/libtiffd.a>;\$<\$<NOT:\$<CONFIG:DEBUG>>:${_IMPORT_PREFIX}/lib/liblzma.a>;\$<\$<CONFIG:DEBUG>:${_IMPORT_PREFIX}/debug/lib/liblzmad.a>;${_IMPORT_PREFIX}/lib/libjpeg.a;${_IMPORT_PREFIX}/lib/libz.a;\$<LINK_ONLY:m>;${_IMPORT_PREFIX}/lib/libjpeg.a;${_IMPORT_PREFIX}/lib/libz.a;${_IMPORT_PREFIX}/lib/libz.a;\$<LINK_ONLY:\$<\$<BOOL:FALSE>:OpenColorIO::OpenColorIO>>;/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/usr/lib/libbz2.tbd;${_IMPORT_PREFIX}/lib/libz.a;${_IMPORT_PREFIX}/lib/libboost_filesystem.a;${_IMPORT_PREFIX}/lib/libboost_system.a;${_IMPORT_PREFIX}/lib/libboost_thread.a;${_IMPORT_PREFIX}/lib/libboost_chrono.a;${_IMPORT_PREFIX}/lib/libboost_date_time.a;${_IMPORT_PREFIX}/lib/libboost_atomic.a;${_IMPORT_PREFIX}/lib/libsquish.a"
)```