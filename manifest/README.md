# VCPKG Manifest files

I've decided to add these not to the root of the project but in a different folder.

The main reason for this is I don't want to use the manifest mode by default as we use most of these libraries in other demos. 

I also have a ci version in a different folder so I can build using the ci without OpenImageIO which is slow.

On ci/GitHub actions  we add the command line -DVCPKG_MANIFEST_DIR=./manifest/ci/ to point to the non OpenImageIO manifest.

For building at home I will now advise using -DVCPKG_MANIFEST_DIR=./manifest/ 