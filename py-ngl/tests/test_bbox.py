import pytest

from ngl import BBox, Vec3


def test_default_ctor():
    test = BBox()
    assert test.width == 2.0
    assert test.height == 2.0
    assert test.depth == 2.0
    assert test.min_x == -1.0
    assert test.min_y == -1.0
    assert test.min_z == -1.0
    assert test.max_x == 1.0
    assert test.max_y == 1.0
    assert test.max_z == 1.0
    assert test.center == Vec3(0.0, 0.0, 0.0)


def test_construct_with_center():
    test = BBox(center=Vec3(2.0, 2.0, 2.0), width=2.0, height=3.0, depth=4.0)
    assert test.min_x == 1.0
    assert test.max_x == 3.0
    assert test.min_y == 0.5
    assert test.max_y == 3.5
    assert test.min_z == 0.0
    assert test.max_z == 4.0
    assert test.center == Vec3(2.0, 2.0, 2.0)
    assert test.width == 2.0
    assert test.height == 3.0
    assert test.depth == 4.0


def test_construct_from_extents():
    test = BBox.from_extents(-5, 5, -2, 2, -3.2, 2.4)
    assert test.min_x == -5.0
    assert test.max_x == 5.0
    assert test.min_y == -2.0
    assert test.max_y == 2.0
    assert test.min_z == pytest.approx(-3.2)
    assert test.max_z == pytest.approx(2.4)
    assert test.center == Vec3(0.0, 0.0, -0.4)
    assert test.width == 10.0
    assert test.height == 4.0
    assert test.depth == pytest.approx(5.6)


def test_set_extents():
    test = BBox()
    test.set_extents(-5, 5, -2, 2, -3.2, 2.4)
    assert test.min_x == -5.0
    assert test.max_x == 5.0
    assert test.min_y == -2.0
    assert test.max_y == 2.0
    assert test.min_z == pytest.approx(-3.2)
    assert test.max_z == pytest.approx(2.4)
    assert test.center == Vec3(0.0, 0.0, -0.4)
    assert test.width == 10.0
    assert test.height == 4.0
    assert test.depth == pytest.approx(5.6)


def test_setters():
    test = BBox()
    test.width = 5
    test.height = 25
    test.depth = 15
    assert test.width == 5.0
    assert test.height == 25.0
    assert test.depth == 15.0
    assert test.min_x == -2.5
    assert test.max_x == 2.5
    assert test.min_y == -12.5
    assert test.max_y == 12.5
    assert test.min_z == -7.5
    assert test.max_z == 7.5


def test_get_verts():
    test = BBox()
    verts = test.get_vertex_array()
    assert len(verts) == 8
    assert verts[0] == Vec3(-1, 1, -1)
    assert verts[1] == Vec3(1, 1, -1)
    assert verts[2] == Vec3(1, 1, 1)
    assert verts[3] == Vec3(-1, 1, 1)
    assert verts[4] == Vec3(-1, -1, -1)
    assert verts[5] == Vec3(1, -1, -1)
    assert verts[6] == Vec3(1, -1, 1)
    assert verts[7] == Vec3(-1, -1, 1)


def test_center():
    test = BBox()
    test.center = Vec3(0, 2, 3)
    assert test.center == Vec3(0, 2, 3)


def test_get_normal_array():
    test = BBox()
    normals = test.get_normal_array()
    assert len(normals) == 6
    assert normals[0] == Vec3(0.0, 1.0, 0.0)
    assert normals[1] == Vec3(0.0, -1.0, 0.0)
    assert normals[2] == Vec3(1.0, 0.0, 0.0)
    assert normals[3] == Vec3(-1.0, 0.0, 0.0)
    assert normals[4] == Vec3(0.0, 0.0, 1.0)
    assert normals[5] == Vec3(0.0, 0.0, -1.0)
