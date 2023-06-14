# Dockerfiles

This folder contains the Dockerfiles for different operating systems to allow quick tests for new os versions etc. Each docker file is in it's own named folder. 

These files are useful as you can see what base requirements are needed for each of the operating systems, in particular what development librates and tools are needed. Typically you will need to install some of these on your host machine to build NGL.

In particular look for the RUN section and the use of either dnf, apt-get or yum to install the required packages. There is also an ENV section which may be used to setup paths required for the build.

In some cases we need to install a newer version of cmake than the system packages as vcpkg requires a newer version. In this case we install cmake from source and set the path to use this version.

If the repo builds it should also run the NGLTests however you can't really see them as they are running in a headless mode. To see the tests you will need to run the docker image and then run the tests manually.

## Linux Versions

I have chosen all of the main popular distro's as well as the two recommended by the VFX Reference platform (Rocky Linux and Alma Linux). [https://vfxplatform.com/linux/](https://vfxplatform.com/linux/).

The main lab version at the NCCA is RHEL 8.5 which will be moving to 9.x soon. There is no Dockerfile for this as it requires a subscription to download the packages. However Rocky and Alma are both based on RHEL so should be close enough.

## [Alma Linux](Alma/Dockerfile)

This is a basic Alma Linux image with the required packages installed. It is based on the latest Alma Linux image.

```bash
docker build -t ngl-alma .
docker run -it ngl-alma
```

## [Rocky Linux](Rocky/Dockerfile)

This is a basic Rocky Linux image with the required packages installed. It is based on the latest Rocky Linux image.

```bash  
docker build -t ngl-rocky .
docker run -it ngl-rocky
```

## [Fedora](Fedora/Dockerfile)

This is a basic fedora image with the required packages installed. It is based on the latest fedora image.

```bash
docker build -t ngl-fedora .
docker run -it ngl-fedora
```

## [Ubuntu](Ubuntu/Dockerfile)

This is a basic ubuntu image with the required packages installed. It is based on the latest ubuntu image.

```bash    
docker build -t ngl-ubuntu .
docker run -it ngl-ubuntu
```

## [Debian](Debian/Dockerfile)

This is a basic Debian image with the required packages installed. It is based on the latest ubuntu image.

```bash    
docker build -t ngl-debian .
docker run -it ngl-debian
```

# Expected output
```
excluding tests
Note: Google Test filter = -ShaderLib.*:VAOPrimitives.*:NGLInit*: NGLMessage*
[==========]Running 260 tests from 17 test suites.
[----------]Global test environment set-up.
[----------]3 tests from AABB
[ RUN      ]AABB.DefaultCtor
[       OK ]AABB.DefaultCtor (0 ms)
[ RUN      ]AABB.userCtor
[       OK ]AABB.userCtor (0 ms)
[ RUN      ]AABB.set
[       OK ]AABB.set (0 ms)
[----------]3 tests from AABB (0 ms total)

[----------]14 tests from Util
[ RUN      ]Util.perspective
[       OK ]Util.perspective (0 ms)
[ RUN      ]Util.perspectiveFov
[       OK ]Util.perspectiveFov (0 ms)
[ RUN      ]Util.infinitePerspective
[       OK ]Util.infinitePerspective (0 ms)
[ RUN      ]Util._rad
[       OK ]Util._rad (0 ms)
[ RUN      ]Util.ortho
[       OK ]Util.ortho (0 ms)
[ RUN      ]Util.ortho2d
[       OK ]Util.ortho2d (0 ms)
[ RUN      ]Util.lookAt
[       OK ]Util.lookAt (0 ms)
[ RUN      ]Util.frustum
[       OK ]Util.frustum (0 ms)
[ RUN      ]Util.radians
[       OK ]Util.radians (0 ms)
[ RUN      ]Util.degrees
[       OK ]Util.degrees (0 ms)
[ RUN      ]Util.calcNormal1
[       OK ]Util.calcNormal1 (0 ms)
[ RUN      ]Util.calcNormal2
[       OK ]Util.calcNormal2 (0 ms)
[ RUN      ]Util.generateDistinctColoursReturnsCorrectNumberOfColours
[       OK ]Util.generateDistinctColoursReturnsCorrectNumberOfColours (0 ms)
[ RUN      ]Util.generateDistinctColoursReturnsDistinctColours
[       OK ]Util.generateDistinctColoursReturnsDistinctColours (0 ms)
[----------]14 tests from Util (0 ms total)

[----------]8 tests from BBox
[ RUN      ]BBox.DefaultCtor
[       OK ]BBox.DefaultCtor (0 ms)
[ RUN      ]BBox.CopyCtor
[       OK ]BBox.CopyCtor (0 ms)
[ RUN      ]BBox.AssignOperator
[       OK ]BBox.AssignOperator (0 ms)
[ RUN      ]BBox.ConstructWithCenter
[       OK ]BBox.ConstructWithCenter (0 ms)
[ RUN      ]BBox.ConstructFromExtents
[       OK ]BBox.ConstructFromExtents (0 ms)
[ RUN      ]BBox.setExtents
[       OK ]BBox.setExtents (0 ms)
[ RUN      ]BBox.setters
[       OK ]BBox.setters (0 ms)
[ RUN      ]BBox.getVerts
[       OK ]BBox.getVerts (0 ms)
[----------]8 tests from BBox (0 ms total)

[----------]6 tests from BezierCurve
[ RUN      ]BezierCurve.DefaultCtor
[       OK ]BezierCurve.DefaultCtor (0 ms)
[ RUN      ]BezierCurve.createFromCP
[       OK ]BezierCurve.createFromCP (0 ms)
[ RUN      ]BezierCurve.createFromCPXYZ
[       OK ]BezierCurve.createFromCPXYZ (0 ms)
[ RUN      ]BezierCurve.getPointOnCurve
[       OK ]BezierCurve.getPointOnCurve (0 ms)
[ RUN      ]BezierCurve.fromVec3AndKnots
[       OK ]BezierCurve.fromVec3AndKnots (0 ms)
[ RUN      ]BezierCurve.fromVec3
[       OK ]BezierCurve.fromVec3 (0 ms)
[----------]6 tests from BezierCurve (0 ms total)

[----------]28 tests from Vec4
[ RUN      ]Vec4.DefaultCtor
[       OK ]Vec4.DefaultCtor (0 ms)
[ RUN      ]Vec4.SubScript
[       OK ]Vec4.SubScript (0 ms)
[ RUN      ]Vec4.FloatCtor
[       OK ]Vec4.FloatCtor (0 ms)
[ RUN      ]Vec4.CopyCtor
[       OK ]Vec4.CopyCtor (0 ms)
[ RUN      ]Vec4.AssignOperator
[       OK ]Vec4.AssignOperator (0 ms)
[ RUN      ]Vec4.VectorTest
[       OK ]Vec4.VectorTest (0 ms)
[ RUN      ]Vec4.DotProduct
[       OK ]Vec4.DotProduct (0 ms)
[ RUN      ]Vec4.__null
[       OK ]Vec4.__null (0 ms)
[ RUN      ]Vec4.normalize
[       OK ]Vec4.normalize (0 ms)
[ RUN      ]Vec4.Inner
[       OK ]Vec4.Inner (0 ms)
[ RUN      ]Vec4.Outer
[       OK ]Vec4.Outer (0 ms)
[ RUN      ]Vec4.Length
[       OK ]Vec4.Length (0 ms)
[ RUN      ]Vec4.LengthSquared
[       OK ]Vec4.LengthSquared (0 ms)
[ RUN      ]Vec4.Cross2
[       OK ]Vec4.Cross2 (0 ms)
[ RUN      ]Vec4.Cross1
[       OK ]Vec4.Cross1 (0 ms)
[ RUN      ]Vec4.fromGLM
[       OK ]Vec4.fromGLM (0 ms)
[ RUN      ]Vec4.toGLM
[       OK ]Vec4.toGLM (0 ms)
[ RUN      ]Vec4.setGLM
[       OK ]Vec4.setGLM (0 ms)
[ RUN      ]Vec4.add
[       OK ]Vec4.add (0 ms)
[ RUN      ]Vec4.addEqual
[       OK ]Vec4.addEqual (0 ms)
[ RUN      ]Vec4.subtract
[       OK ]Vec4.subtract (0 ms)
[ RUN      ]Vec4.subtractEqual
[       OK ]Vec4.subtractEqual (0 ms)
[ RUN      ]Vec4.multiplyFloat
[       OK ]Vec4.multiplyFloat (0 ms)
[ RUN      ]Vec4.multiplyFloatEqual
[       OK ]Vec4.multiplyFloatEqual (0 ms)
[ RUN      ]Vec4.divideFloatEqual
[       OK ]Vec4.divideFloatEqual (0 ms)
[ RUN      ]Vec4.divideFloat
[       OK ]Vec4.divideFloat (0 ms)
[ RUN      ]Vec4.divideVec
[       OK ]Vec4.divideVec (0 ms)
[ RUN      ]Vec4.divideEqualVec
[       OK ]Vec4.divideEqualVec (0 ms)
[----------]28 tests from Vec4 (0 ms total)

[----------]17 tests from Mat2
[ RUN      ]Mat2.DefaultCtor
[       OK ]Mat2.DefaultCtor (0 ms)
[ RUN      ]Mat2.null
[       OK ]Mat2.null (0 ms)
[ RUN      ]Mat2.identity
[       OK ]Mat2.identity (0 ms)
[ RUN      ]Mat2.FloatCtor
[       OK ]Mat2.FloatCtor (0 ms)
[ RUN      ]Mat2.CopyCtor
[       OK ]Mat2.CopyCtor (0 ms)
[ RUN      ]Mat2.AssignOperator
[       OK ]Mat2.AssignOperator (0 ms)
[ RUN      ]Mat2.setAtXY
[       OK ]Mat2.setAtXY (0 ms)
[ RUN      ]Mat2.transpose
[       OK ]Mat2.transpose (0 ms)
[ RUN      ]Mat2.scale
[       OK ]Mat2.scale (0 ms)
[ RUN      ]Mat2.rotate
[       OK ]Mat2.rotate (0 ms)
[ RUN      ]Mat2.Mat2xMat2
[       OK ]Mat2.Mat2xMat2 (0 ms)
[ RUN      ]Mat2.Mat2xeuqals
[       OK ]Mat2.Mat2xeuqals (0 ms)
[ RUN      ]Mat2.Mat2plusEqual
[       OK ]Mat2.Mat2plusEqual (0 ms)
[ RUN      ]Mat2.Mat2plus
[       OK ]Mat2.Mat2plus (0 ms)
[ RUN      ]Mat2.Mat2xReal
[       OK ]Mat2.Mat2xReal (0 ms)
[ RUN      ]Mat2.Mat2xEqualReal
[       OK ]Mat2.Mat2xEqualReal (0 ms)
[ RUN      ]Mat2.Vec2xMat2
[       OK ]Mat2.Vec2xMat2 (0 ms)
[----------]17 tests from Mat2 (0 ms total)

[----------]23 tests from Mat3
[ RUN      ]Mat3.DefaultCtor
[       OK ]Mat3.DefaultCtor (0 ms)
[ RUN      ]Mat3.null
[       OK ]Mat3.null (0 ms)
[ RUN      ]Mat3.identity
[       OK ]Mat3.identity (0 ms)
[ RUN      ]Mat3.FloatCtor
[       OK ]Mat3.FloatCtor (0 ms)
[ RUN      ]Mat3.CopyCtor
[       OK ]Mat3.CopyCtor (0 ms)
[ RUN      ]Mat3.AssignOperator
[       OK ]Mat3.AssignOperator (0 ms)
[ RUN      ]Mat3.setAtXY
[       OK ]Mat3.setAtXY (0 ms)
[ RUN      ]Mat3.transpose
[       OK ]Mat3.transpose (0 ms)
[ RUN      ]Mat3.scale
[       OK ]Mat3.scale (0 ms)
[ RUN      ]Mat3.rotateX
[       OK ]Mat3.rotateX (0 ms)
[ RUN      ]Mat3.rotateY
[       OK ]Mat3.rotateY (0 ms)
[ RUN      ]Mat3.rotateZ
[       OK ]Mat3.rotateZ (0 ms)
[ RUN      ]Mat3.Mat3xMat3
[       OK ]Mat3.Mat3xMat3 (0 ms)
[ RUN      ]Mat3.Mat3xeuqals
[       OK ]Mat3.Mat3xeuqals (0 ms)
[ RUN      ]Mat3.Mat3xeuqals2
[       OK ]Mat3.Mat3xeuqals2 (0 ms)
[ RUN      ]Mat3.Mat3plusEqual
[       OK ]Mat3.Mat3plusEqual (0 ms)
[ RUN      ]Mat3.Mat3plus
[       OK ]Mat3.Mat3plus (0 ms)
[ RUN      ]Mat3.Mat3xReal
[       OK ]Mat3.Mat3xReal (0 ms)
[ RUN      ]Mat3.Mat3xEqualReal
[       OK ]Mat3.Mat3xEqualReal (0 ms)
[ RUN      ]Mat3.determinant
[       OK ]Mat3.determinant (0 ms)
[ RUN      ]Mat3.inverse
[       OK ]Mat3.inverse (0 ms)
[ RUN      ]Mat3.Vec3xMat3
[       OK ]Mat3.Vec3xMat3 (0 ms)
[ RUN      ]Mat3.normalMatrix
[       OK ]Mat3.normalMatrix (0 ms)
[----------]23 tests from Mat3 (0 ms total)

[----------]30 tests from Obj
[ RUN      ]Obj.openForReading
[       OK ]Obj.openForReading (0 ms)
[ RUN      ]Obj.defaultCtor
[       OK ]Obj.defaultCtor (0 ms)
[ RUN      ]Obj.loadvalid
[       OK ]Obj.loadvalid (0 ms)
[ RUN      ]Obj.loadinvalid
[       OK ]Obj.loadinvalid (0 ms)
[ RUN      ]Obj.loadFail
[       OK ]Obj.loadFail (0 ms)
[ RUN      ]Obj.parseVertex
[       OK ]Obj.parseVertex (0 ms)
[ RUN      ]Obj.parseNormal
[       OK ]Obj.parseNormal (0 ms)
[ RUN      ]Obj.parseUV
[       OK ]Obj.parseUV (0 ms)
[ RUN      ]Obj.parseUV3
[       OK ]Obj.parseUV3 (0 ms)
[ RUN      ]Obj.checkVerts
[       OK ]Obj.checkVerts (0 ms)
[ RUN      ]Obj.checkNorm
[       OK ]Obj.checkNorm (0 ms)
[ RUN      ]Obj.checkUV
[       OK ]Obj.checkUV (0 ms)
[ RUN      ]Obj.checkFaceVertOnly
[       OK ]Obj.checkFaceVertOnly (0 ms)
[ RUN      ]Obj.checkFaceVertNormal
[       OK ]Obj.checkFaceVertNormal (0 ms)
[ RUN      ]Obj.checkFaceVertUV
[       OK ]Obj.checkFaceVertUV (0 ms)
[ RUN      ]Obj.checkFaceVertOnlyNegativeIndex
[       OK ]Obj.checkFaceVertOnlyNegativeIndex (0 ms)
[ RUN      ]Obj.checkFace
[       OK ]Obj.checkFace (0 ms)
[ RUN      ]Obj.addVertex
[       OK ]Obj.addVertex (0 ms)
[ RUN      ]Obj.addNormal
[       OK ]Obj.addNormal (0 ms)
[ RUN      ]Obj.addUVVec3
[       OK ]Obj.addUVVec3 (0 ms)
[ RUN      ]Obj.addUVVec2
[       OK ]Obj.addUVVec2 (0 ms)
[ RUN      ]Obj.addFace
[       OK ]Obj.addFace (0 ms)
[ RUN      ]Obj.buildObj
[       OK ]Obj.buildObj (0 ms)
[ RUN      ]Obj.saveVertsOnly
[       OK ]Obj.saveVertsOnly (0 ms)
[ RUN      ]Obj.saveVertsUV
[       OK ]Obj.saveVertsUV (0 ms)
[ RUN      ]Obj.saveVertsNormal
[       OK ]Obj.saveVertsNormal (0 ms)
[ RUN      ]Obj.saveObj
[       OK ]Obj.saveObj (0 ms)
[ RUN      ]Obj.copyctor
[       OK ]Obj.copyctor (0 ms)
[ RUN      ]Obj.passbyref
[       OK ]Obj.passbyref (0 ms)
[ RUN      ]Obj.isTriangular
[       OK ]Obj.isTriangular (0 ms)
[----------]30 tests from Obj (2 ms total)

[----------]1 test from Plane
[ RUN      ]Plane.DefaultCtor
[       OK ]Plane.DefaultCtor (0 ms)
[----------]1 test from Plane (0 ms total)

[----------]7 tests from Transformation
[ RUN      ]Transformation.DefaultCtor
[       OK ]Transformation.DefaultCtor (0 ms)
[ RUN      ]Transformation.Position
[       OK ]Transformation.Position (0 ms)
[ RUN      ]Transformation.Scale
[       OK ]Transformation.Scale (0 ms)
[ RUN      ]Transformation.Rotation
[       OK ]Transformation.Rotation (0 ms)
[ RUN      ]Transformation.setMatrix
[       OK ]Transformation.setMatrix (0 ms)
[ RUN      ]Transformation.copyAndAssign
[       OK ]Transformation.copyAndAssign (0 ms)
[ RUN      ]Transformation.reset
[       OK ]Transformation.reset (0 ms)
[----------]7 tests from Transformation (0 ms total)

[----------]24 tests from Vec2
[ RUN      ]Vec2.DefaultCtor
[       OK ]Vec2.DefaultCtor (0 ms)
[ RUN      ]Vec2.VectorTest
[       OK ]Vec2.VectorTest (0 ms)
[ RUN      ]Vec2.DotProduct
[       OK ]Vec2.DotProduct (0 ms)
[ RUN      ]Vec2.__null
[       OK ]Vec2.__null (0 ms)
[ RUN      ]Vec2.normalize
[       OK ]Vec2.normalize (0 ms)
[ RUN      ]Vec2.Length
[       OK ]Vec2.Length (0 ms)
[ RUN      ]Vec2.LengthSquared
[       OK ]Vec2.LengthSquared (0 ms)
[ RUN      ]Vec2.SubScript
[       OK ]Vec2.SubScript (0 ms)
[ RUN      ]Vec2.FloatCtor
[       OK ]Vec2.FloatCtor (0 ms)
[ RUN      ]Vec2.CopyCtor
[       OK ]Vec2.CopyCtor (0 ms)
[ RUN      ]Vec2.AssignOperator
[       OK ]Vec2.AssignOperator (0 ms)
[ RUN      ]Vec2.fromGLM
[       OK ]Vec2.fromGLM (0 ms)
[ RUN      ]Vec2.toGLM
[       OK ]Vec2.toGLM (0 ms)
[ RUN      ]Vec2.setGLM
[       OK ]Vec2.setGLM (0 ms)
[ RUN      ]Vec2.add
[       OK ]Vec2.add (0 ms)
[ RUN      ]Vec2.addEqual
[       OK ]Vec2.addEqual (0 ms)
[ RUN      ]Vec2.subtract
[       OK ]Vec2.subtract (0 ms)
[ RUN      ]Vec2.subtractEqual
[       OK ]Vec2.subtractEqual (0 ms)
[ RUN      ]Vec2.multiplyFloat
[       OK ]Vec2.multiplyFloat (0 ms)
[ RUN      ]Vec2.multiplyFloatEqual
[       OK ]Vec2.multiplyFloatEqual (0 ms)
[ RUN      ]Vec2.divideFloatEqual
[       OK ]Vec2.divideFloatEqual (0 ms)
[ RUN      ]Vec2.divideFloat
[       OK ]Vec2.divideFloat (0 ms)
[ RUN      ]Vec2.divideVec
[       OK ]Vec2.divideVec (0 ms)
[ RUN      ]Vec2.divideEqualVec
[       OK ]Vec2.divideEqualVec (0 ms)
[----------]24 tests from Vec2 (0 ms total)

[----------]29 tests from Mat4
[ RUN      ]Mat4.DefaultCtor
[       OK ]Mat4.DefaultCtor (0 ms)
[ RUN      ]Mat4.null
[       OK ]Mat4.null (0 ms)
[ RUN      ]Mat4.buildFromArray
[       OK ]Mat4.buildFromArray (0 ms)
[ RUN      ]Mat4.identity
[       OK ]Mat4.identity (0 ms)
[ RUN      ]Mat4.FloatCtor
[       OK ]Mat4.FloatCtor (0 ms)
[ RUN      ]Mat4.CopyCtor
[       OK ]Mat4.CopyCtor (0 ms)
[ RUN      ]Mat4.AssignOperator
[       OK ]Mat4.AssignOperator (0 ms)
[ RUN      ]Mat4.setAtXY
[       OK ]Mat4.setAtXY (0 ms)
[ RUN      ]Mat4.translate
[       OK ]Mat4.translate (0 ms)
[ RUN      ]Mat4.transpose
[       OK ]Mat4.transpose (0 ms)
[ RUN      ]Mat4.scale
[       OK ]Mat4.scale (0 ms)
[ RUN      ]Mat4.rotateX
[       OK ]Mat4.rotateX (0 ms)
[ RUN      ]Mat4.rotateY
[       OK ]Mat4.rotateY (0 ms)
[ RUN      ]Mat4.rotateZ
[       OK ]Mat4.rotateZ (0 ms)
[ RUN      ]Mat4.Mat4xMat4
[       OK ]Mat4.Mat4xMat4 (0 ms)
[ RUN      ]Mat4.Mat4xeuqals
[       OK ]Mat4.Mat4xeuqals (0 ms)
[ RUN      ]Mat4.Mat4xeuqals2
[       OK ]Mat4.Mat4xeuqals2 (0 ms)
[ RUN      ]Mat4.Mat4pluEqual
[       OK ]Mat4.Mat4pluEqual (0 ms)
[ RUN      ]Mat4.Mat4plus
[       OK ]Mat4.Mat4plus (0 ms)
[ RUN      ]Mat4.Mat4xReal
[       OK ]Mat4.Mat4xReal (0 ms)
[ RUN      ]Mat4.Mat4xEqualReal
[       OK ]Mat4.Mat4xEqualReal (0 ms)
[ RUN      ]Mat4.determinant
[       OK ]Mat4.determinant (0 ms)
[ RUN      ]Mat4.inverse
[       OK ]Mat4.inverse (0 ms)
[ RUN      ]Mat4.adjacent
[       OK ]Mat4.adjacent (0 ms)
[ RUN      ]Mat4.adjacentWithMat4
[       OK ]Mat4.adjacentWithMat4 (0 ms)
[ RUN      ]Mat4.Vec4xMat4
[       OK ]Mat4.Vec4xMat4 (0 ms)
[ RUN      ]Mat4.Mat4xVec4
[       OK ]Mat4.Mat4xVec4 (0 ms)
[ RUN      ]Mat4.fromGLM
[       OK ]Mat4.fromGLM (0 ms)
[ RUN      ]Mat4.toGLM
[       OK ]Mat4.toGLM (0 ms)
[----------]29 tests from Mat4 (2 ms total)

[----------]28 tests from Vec3
[ RUN      ]Vec3.DefaultCtor
[       OK ]Vec3.DefaultCtor (0 ms)
[ RUN      ]Vec3.VectorTest
[       OK ]Vec3.VectorTest (0 ms)
[ RUN      ]Vec3.DotProduct
[       OK ]Vec3.DotProduct (0 ms)
[ RUN      ]Vec3.__null
[       OK ]Vec3.__null (0 ms)
[ RUN      ]Vec3.normalize
[       OK ]Vec3.normalize (0 ms)
[ RUN      ]Vec3.Inner
[       OK ]Vec3.Inner (0 ms)
[ RUN      ]Vec3.Outer
[       OK ]Vec3.Outer (0 ms)
[ RUN      ]Vec3.Length
[       OK ]Vec3.Length (0 ms)
[ RUN      ]Vec3.LengthSquared
[       OK ]Vec3.LengthSquared (0 ms)
[ RUN      ]Vec3.Cross2
[       OK ]Vec3.Cross2 (0 ms)
[ RUN      ]Vec3.Cross1
[       OK ]Vec3.Cross1 (0 ms)
[ RUN      ]Vec3.SubScript
[       OK ]Vec3.SubScript (0 ms)
[ RUN      ]Vec3.FloatCtor
[       OK ]Vec3.FloatCtor (0 ms)
[ RUN      ]Vec3.CopyCtor
[       OK ]Vec3.CopyCtor (0 ms)
[ RUN      ]Vec3.AssignOperator
[       OK ]Vec3.AssignOperator (0 ms)
[ RUN      ]Vec3.fromGLM
[       OK ]Vec3.fromGLM (0 ms)
[ RUN      ]Vec3.toGLM
[       OK ]Vec3.toGLM (0 ms)
[ RUN      ]Vec3.setGLM
[       OK ]Vec3.setGLM (0 ms)
[ RUN      ]Vec3.add
[       OK ]Vec3.add (0 ms)
[ RUN      ]Vec3.addEqual
[       OK ]Vec3.addEqual (0 ms)
[ RUN      ]Vec3.subtract
[       OK ]Vec3.subtract (0 ms)
[ RUN      ]Vec3.subtractEqual
[       OK ]Vec3.subtractEqual (0 ms)
[ RUN      ]Vec3.multiplyFloat
[       OK ]Vec3.multiplyFloat (0 ms)
[ RUN      ]Vec3.multiplyFloatEqual
[       OK ]Vec3.multiplyFloatEqual (0 ms)
[ RUN      ]Vec3.divideFloatEqual
[       OK ]Vec3.divideFloatEqual (0 ms)
[ RUN      ]Vec3.divideFloat
[       OK ]Vec3.divideFloat (0 ms)
[ RUN      ]Vec3.divideVec
[       OK ]Vec3.divideVec (0 ms)
[ RUN      ]Vec3.divideEqualVec
[       OK ]Vec3.divideEqualVec (0 ms)
[----------]28 tests from Vec3 (0 ms total)

[----------]10 tests from Random
[ RUN      ]Random.vec2
[       OK ]Random.vec2 (0 ms)
[ RUN      ]Random.vec3
[       OK ]Random.vec3 (0 ms)
[ RUN      ]Random.point
[       OK ]Random.point (0 ms)
[ RUN      ]Random.vec4
[       OK ]Random.vec4 (0 ms)
[ RUN      ]Random.randomNumberDefault
[       OK ]Random.randomNumberDefault (0 ms)
[ RUN      ]Random.randomNumberParam
[       OK ]Random.randomNumberParam (0 ms)
[ RUN      ]Random.randomPositiveNumberDefault
[       OK ]Random.randomPositiveNumberDefault (0 ms)
[ RUN      ]Random.randomPositiveNumberParam
[       OK ]Random.randomPositiveNumberParam (0 ms)
[ RUN      ]Random.addIntGenerator
[       OK ]Random.addIntGenerator (0 ms)
[ RUN      ]Random.addFloatGenerator
[       OK ]Random.addFloatGenerator (0 ms)
[----------]10 tests from Random (0 ms total)

[----------]20 tests from Quaternion
[ RUN      ]Quaternion.DefaultCtor
[       OK ]Quaternion.DefaultCtor (0 ms)
[ RUN      ]Quaternion.UserCtor
[       OK ]Quaternion.UserCtor (0 ms)
[ RUN      ]Quaternion.fromMat4
[       OK ]Quaternion.fromMat4 (0 ms)
[ RUN      ]Quaternion.addition
[       OK ]Quaternion.addition (0 ms)
[ RUN      ]Quaternion.additionEqual
[       OK ]Quaternion.additionEqual (0 ms)
[ RUN      ]Quaternion.subtract
[       OK ]Quaternion.subtract (0 ms)
[ RUN      ]Quaternion.subtractEqual
[       OK ]Quaternion.subtractEqual (0 ms)
[ RUN      ]Quaternion.multiplyQuat
[       OK ]Quaternion.multiplyQuat (0 ms)
[ RUN      ]Quaternion.multiplyEqualQuat
[       OK ]Quaternion.multiplyEqualQuat (0 ms)
[ RUN      ]Quaternion.magnitude
[       OK ]Quaternion.magnitude (0 ms)
[ RUN      ]Quaternion.normalize
[       OK ]Quaternion.normalize (0 ms)
[ RUN      ]Quaternion.conjugate
[       OK ]Quaternion.conjugate (0 ms)
[ RUN      ]Quaternion.inverse
[       OK ]Quaternion.inverse (0 ms)
[ RUN      ]Quaternion.dot
[       OK ]Quaternion.dot (0 ms)
[ RUN      ]Quaternion.dotStatic
[       OK ]Quaternion.dotStatic (0 ms)
[ RUN      ]Quaternion.fromEuler
[       OK ]Quaternion.fromEuler (0 ms)
[ RUN      ]Quaternion.fromAxisAngle
[       OK ]Quaternion.fromAxisAngle (0 ms)
[ RUN      ]Quaternion.toAxisAngle
[       OK ]Quaternion.toAxisAngle (0 ms)
[ RUN      ]Quaternion.toMat4
[       OK ]Quaternion.toMat4 (0 ms)
[ RUN      ]Quaternion.SLERP
[       OK ]Quaternion.SLERP (0 ms)
[----------]20 tests from Quaternion (0 ms total)

[----------]5 tests from Image
[ RUN      ]Image.DefaultCtor
[       OK ]Image.DefaultCtor (0 ms)
[ RUN      ]Image.createSimpleImageRGBA
[       OK ]Image.createSimpleImageRGBA (3 ms)
[ RUN      ]Image.createSimpleImageRGB
[       OK ]Image.createSimpleImageRGB (0 ms)
[ RUN      ]Image.loadRGB
[       OK ]Image.loadRGB (1 ms)
[ RUN      ]Image.loadRGBA
[       OK ]Image.loadRGBA (0 ms)
[----------]5 tests from Image (6 ms total)

[----------]7 tests from Hash
[ RUN      ]Hash.Vec2
[       OK ]Hash.Vec2 (0 ms)
[ RUN      ]Hash.Vec3
[       OK ]Hash.Vec3 (0 ms)
[ RUN      ]Hash.Vec4
[       OK ]Hash.Vec4 (0 ms)
[ RUN      ]Hash.Quaternion
[       OK ]Hash.Quaternion (0 ms)
[ RUN      ]Hash.Mat2
[       OK ]Hash.Mat2 (0 ms)
[ RUN      ]Hash.Mat3
[       OK ]Hash.Mat3 (0 ms)
[ RUN      ]Hash.Mat4
[       OK ]Hash.Mat4 (0 ms)
[----------]7 tests from Hash (0 ms total)

[----------]Global test environment tear-down
[==========]260 tests from 17 test suites ran. (13 ms total)
[  PASSED  ]260 tests.
```