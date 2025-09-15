import pytest

from ngl import (
    Face,
    Obj,
    ObjParseNormalError,
    ObjParseUVError,
    ObjParseVertexError,
    Vec3,
)

validfiles = [
    "tests/files/Triangle1.obj",
    "tests/files/TriangleVertNormal.obj",
    "tests/files/TriangleVertsOnly.obj",
    "tests/files/TriangleVertsUV.obj",
    "tests/files/Triangle3UV.obj",
    "tests/files/TriMessedFormat.obj",
    "tests/files/CubeNegativeIndex.obj",
]
invalidfiles = [
    "files/BrokenFloats.obj",
    "files/BrokenNormal.obj",
    "files/BrokenUV.obj",
]


def test_ctor():
    o = Obj()
    assert len(o.faces) == 0
    assert len(o.vertex) == 0
    assert len(o.normals) == 0
    assert len(o.uv) == 0


def test_load_valid():
    o = Obj()
    for file in validfiles:
        assert o.load(file)


def test_load_not_found():
    o = Obj()
    with pytest.raises(FileNotFoundError):
        o.load("bogus.obj")


def test_parse_vertex():
    obj = Obj.from_file("tests/files/Triangle1.obj")
    assert len(obj.vertex) == 3
    with pytest.raises(ObjParseVertexError):
        obj = Obj.from_file("tests/files/BrokenFloats.obj")


def test_parse_normal():
    obj = Obj.from_file("tests/files/Triangle1.obj")
    assert len(obj.normals) == 3
    with pytest.raises(ObjParseNormalError):
        obj = Obj.from_file("tests/files/BrokenNormals.obj")


def test_parse_uv():
    obj = Obj.from_file("tests/files/Triangle1.obj")
    assert len(obj.uv) == 3
    with pytest.raises(ObjParseUVError):
        obj = Obj.from_file("tests/files/BrokenUV.obj")


def test_check_verts():
    obj = Obj.from_file("tests/files/Triangle1.obj")

    result = [Vec3(2.0, 0.0, 0.0), Vec3(0.0, 4.0, 0.0), Vec3(-2.0, 0.0, 0.0)]
    assert [r == v for r, v in zip(result, obj.vertex)]


def test_check_normals():
    obj = Obj.from_file("tests/files/Triangle1.obj")

    result = [Vec3(0.0, 0.0, 1.0), Vec3(0.0, 0.0, 1.0), Vec3(0.0, 0.0, 1.0)]
    assert [r == v for r, v in zip(result, obj.normals)]


def test_check_uvs():
    obj = Obj.from_file("tests/files/Triangle1.obj")

    result = [Vec3(1.0, 0.0, 0.0), Vec3(0.5, 1.0, 0.0), Vec3(0.004399, 0.008916, 0.0)]
    assert [r == v for r, v in zip(result, obj.uv)]


def test_check_face_vert_only():
    obj = Obj.from_file("tests/files/TriangleVertsOnly.obj")
    # face is f 1/1/1 2/2/2 3/3/3 but we index from 0
    assert obj.faces[0].vertex[0] == 0
    assert obj.faces[0].vertex[1] == 1
    assert obj.faces[0].vertex[2] == 2


def test_check_face_vert_normal():
    obj = Obj.from_file("tests/files/TriangleVertNormal.obj")
    # face is f 1/1/1 2/2/2 3/3/3 but we index from 0
    assert obj.faces[0].vertex[0] == 0
    assert obj.faces[0].vertex[1] == 1
    assert obj.faces[0].vertex[2] == 2
    assert obj.faces[0].normal[0] == 0
    assert obj.faces[0].normal[1] == 1
    assert obj.faces[0].normal[2] == 2


def test_check_face_vert_uv():
    obj = Obj.from_file("tests/files/TriangleVertsUV.obj")
    assert obj.faces[0].vertex[0] == 0
    assert obj.faces[0].vertex[1] == 1
    assert obj.faces[0].vertex[2] == 2
    assert obj.faces[0].uv[0] == 0
    assert obj.faces[0].uv[1] == 1
    assert obj.faces[0].uv[2] == 2


def test_check_face_vert_only_negative_index():
    obj = Obj.from_file("tests/files/CubeNegativeIndex.obj")
    # face is f -4 -3 -2 -1
    idx = 0
    for i in range(0, len(obj.faces)):
        assert obj.faces[i].vertex[0] == idx
        assert obj.faces[i].vertex[1] == idx + 1
        assert obj.faces[i].vertex[2] == idx + 2
        assert obj.faces[i].vertex[3] == idx + 3
        idx += 4


def test_check_face():
    obj = Obj.from_file("tests/files/Triangle1.obj")
    # face is f 1/1/1 2/2/2 3/3/3 but we index from 0
    for i in range(0, 3):
        assert obj.faces[0].vertex[i] == i
        assert obj.faces[0].normal[i] == i
        assert obj.faces[0].uv[i] == i


def test_add_vertex():
    obj = Obj()
    for i in range(0, 20):
        obj.add_vertex(Vec3(i, i, i))
    for i in range(0, 20):
        assert obj.vertex[i] == Vec3(i, i, i)


def test_add_normal():
    obj = Obj()
    for i in range(0, 20):
        obj.add_normal(Vec3(i, i, i))
    for i in range(0, 20):
        assert obj.normals[i] == Vec3(i, i, i)


def test_add_uv():
    obj = Obj()
    for i in range(0, 20):
        obj.add_uv(Vec3(i, i, i))
    for i in range(0, 20):
        assert obj.uv[i] == Vec3(i, i, i)


def test_add_face():
    f = Face()
    obj = Obj()
    for i in range(0, 3):
        f.vertex.append(i)
        f.normal.append(i)
        f.uv.append(i)
    obj.add_face(f)
    for i in range(0, 3):
        assert obj.faces[0].vertex[i] == i
        assert obj.faces[0].normal[i] == i
        assert obj.faces[0].uv[i] == i


def test_build_obj():
    obj = Obj()
    obj.add_vertex(Vec3(2.0, 0.0, 0.0))
    obj.add_vertex(Vec3(0.0, 4.0, 0.0))
    obj.add_vertex(Vec3(-2.0, 0.0, 0.0))
    obj.add_uv(Vec3(1.0, 0.0, 0.0))
    obj.add_uv(Vec3(0.5, 1.0, 0.0))
    obj.add_uv(Vec3(0.004399, 0.008916, 0.0))
    obj.add_normal(Vec3(0.0, 0.0, 1.0))
    # f 1/1/1 2/2/1 3/3/1
    face = Face()
    face.vertex.append(0)
    face.vertex.append(1)
    face.vertex.append(2)
    face.uv.append(0)
    face.uv.append(1)
    face.uv.append(2)
    face.normal.append(0)
    face.normal.append(0)
    face.normal.append(0)
    obj.add_face(face)
    obj.save("tests/tempObj.obj")
    # reload and check
    new = Obj.from_file("tests/tempObj.obj")
    assert new.vertex[0] == Vec3(2.0, 0.0, 0.0)
    assert new.vertex[1] == Vec3(0.0, 4.0, 0.0)
    assert new.vertex[2] == Vec3(-2.0, 0.0, 0.0)
    assert new.uv[0] == Vec3(1.0, 0.0, 0.0)
    assert new.uv[1] == Vec3(0.5, 1.0, 0.0)
    assert new.uv[2] == Vec3(0.004399, 0.008916, 0.0)
    assert new.normals[0] == Vec3(0.0, 0.0, 1.0)
    assert new.faces[0].vertex == [0, 1, 2]
    assert new.faces[0].uv == [0, 1, 2]
    assert new.faces[0].normal == [0, 0, 0]


def test_build_obj_with_colour():
    obj = Obj()
    obj.add_vertex_colour(Vec3(2.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0))
    obj.add_vertex_colour(Vec3(0.0, 4.0, 0.0), Vec3(0.0, 1.0, 0.0))
    obj.add_vertex_colour(Vec3(-2.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0))

    obj.add_uv(Vec3(1.0, 0.0, 0.0))
    obj.add_uv(Vec3(0.5, 1.0, 0.0))
    obj.add_uv(Vec3(0.004399, 0.008916, 0.0))
    obj.add_normal(Vec3(0.0, 0.0, 1.0))
    # f 1/1/1 2/2/1 3/3/1
    face = Face()
    face.vertex.append(0)
    face.vertex.append(1)
    face.vertex.append(2)
    face.uv.append(0)
    face.uv.append(1)
    face.uv.append(2)
    face.normal.append(0)
    face.normal.append(0)
    face.normal.append(0)
    obj.add_face(face)
    obj.save("tests/tempColourObj.obj")
    # reload and check
    new = Obj.from_file("tests/tempColourObj.obj")
    assert new.vertex[0] == Vec3(2.0, 0.0, 0.0)
    assert new.vertex[1] == Vec3(0.0, 4.0, 0.0)
    assert new.vertex[2] == Vec3(-2.0, 0.0, 0.0)
    assert new.uv[0] == Vec3(1.0, 0.0, 0.0)
    assert new.uv[1] == Vec3(0.5, 1.0, 0.0)
    assert new.uv[2] == Vec3(0.004399, 0.008916, 0.0)
    assert new.normals[0] == Vec3(0.0, 0.0, 1.0)
    assert new.faces[0].vertex == [0, 1, 2]
    assert new.faces[0].uv == [0, 1, 2]
    assert new.faces[0].normal == [0, 0, 0]
    assert new.colour[0] == Vec3(1.0, 0.0, 0.0)
    assert new.colour[1] == Vec3(0.0, 1.0, 0.0)
    assert new.colour[2] == Vec3(0.0, 0.0, 1.0)


def test_obj_with_colour():
    obj = Obj.from_file("tests/files/TriColour.obj")

    assert hasattr(obj, "colour")
    assert len(obj.colour) == 3
    assert obj.colour[0] == Vec3(1.0, 0.0, 0.0)
    assert obj.colour[1] == Vec3(0.0, 1.0, 0.0)
    assert obj.colour[2] == Vec3(0.0, 0.0, 1.0)
