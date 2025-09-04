import pytest

from ngl import Plane, Vec3


def test_default_ctor():
    test = Plane()
    p = test.point
    assert p.x == 0.0
    assert p.y == 0.0
    assert p.z == 0.0
    p = test.normal
    assert p.x == 0.0
    assert p.y == 1.0
    assert p.z == 0.0


def test_user_ctor():
    test = Plane(Vec3(1.0, 0.0, 1.0), Vec3(1.0, 0.0, 2.0), Vec3(2.0, 0.0, 4.0))
    p = test.point
    assert p.x == 1.0
    assert p.y == 0.0
    assert p.z == 2.0
    p = test.normal
    assert p.x == 0.0
    assert p.y == 1.0
    assert p.z == 0.0


def test_points():
    test = Plane()
    test.set_points(Vec3(1.0, 0.0, 1.0), Vec3(1.0, 0.0, 2.0), Vec3(2.0, 0.0, 4.0))
    p = test.point
    assert p.x == 1.0
    assert p.y == 0.0
    assert p.z == 2.0
    p = test.normal
    assert p.x == 0.0
    assert p.y == 1.0
    assert p.z == 0.0


def test_normal_point():
    test = Plane()
    test.set_normal_point(Vec3(0.0, 1.0, 0.0), Vec3(0.5, 0.0, 0.5))
    p = test.point
    assert p.x == 0.5
    assert p.y == 0.0
    assert p.z == 0.5
    p = test.normal
    assert p.x == 0.0
    assert p.y == 1.0
    assert p.z == 0.0


def test_floats():
    test = Plane()
    test.set_floats(0.0, 1.0, 0.0, 0.5)
    p = test.point
    assert p.x == 0.0
    assert p.y == 0.0
    assert p.z == 0.0
    p = test.normal
    assert p.x == 0.0
    assert p.y == 1.0
    assert p.z == 0.0
    assert test.d == pytest.approx(0.5)


def test_distance():
    test = Plane()
    test.set_points(Vec3(-1.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0))
    p = test.distance(Vec3(0.0, 0.5, 0.0))
    assert p == pytest.approx(-0.5)
