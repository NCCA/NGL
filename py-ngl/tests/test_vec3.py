import copy

import pytest

from ngl import Mat3, Vec3


def test_properties():
    v = Vec3()
    v.x = 2.0
    v.y = 3.0
    v.z = 4.0
    assert v.x == pytest.approx(2.0)
    assert v.y == pytest.approx(3.0)
    assert v.z == pytest.approx(4.0)
    with pytest.raises(ValueError):
        v.x = "fail"
    with pytest.raises(ValueError):
        v.y = "fail"
    with pytest.raises(ValueError):
        v.z = "fail"


def test_ctor():
    v = Vec3()
    assert v.x == pytest.approx(0.0)
    assert v.y == pytest.approx(0.0)
    assert v.z == pytest.approx(0.0)


def test_userCtor():
    v = Vec3(2.0, 3.0, 4.0)
    assert v.x == pytest.approx(2.0)
    assert v.y == pytest.approx(3.0)
    assert v.z == pytest.approx(4.0)


def test_ctor_single_value():
    v = Vec3(x=2.0)
    assert v.x == pytest.approx(2.0)
    assert v.y == pytest.approx(0.0)
    assert v.z == pytest.approx(0.0)

    v = Vec3(y=2.0)
    assert v.x == pytest.approx(0.0)
    assert v.y == pytest.approx(2.0)
    assert v.z == pytest.approx(0.0)

    v = Vec3(z=2.0)
    assert v.x == pytest.approx(0.0)
    assert v.y == pytest.approx(0.0)
    assert v.z == pytest.approx(2.0)


def test_add():
    a = Vec3(1, 2, 3)
    b = Vec3(4, 5, 6)
    c = a + b
    assert c.x == pytest.approx(5)
    assert c.y == pytest.approx(7)
    assert c.z == pytest.approx(9)

    # negative test
    a = Vec3(1, 2, 3)
    b = Vec3(-4, -5, -6)
    c = a + b
    assert c.x == pytest.approx(-3)
    assert c.y == pytest.approx(-3)
    assert c.z == pytest.approx(-3)


def test_plus_equals():
    a = Vec3(1, 2, 3)
    b = Vec3(4, 5, 6)
    a += b
    assert a.x == pytest.approx(5)
    assert a.y == pytest.approx(7)
    assert a.z == pytest.approx(9)


def test_sub():
    a = Vec3(1, 2, 3)
    b = Vec3(4, 5, 6)
    c = a - b
    assert c.x == pytest.approx(-3)
    assert c.y == pytest.approx(-3)
    assert c.z == pytest.approx(-3)


def test_sub_equals():
    a = Vec3(1, 2, 3)
    b = Vec3(4, 5, 6)
    a -= b
    assert a.x == pytest.approx(-3)
    assert a.y == pytest.approx(-3)
    assert a.z == pytest.approx(-3)


def test_set():
    a = Vec3()
    a.set(2.5, 0.1, 0.5)
    assert a.x == pytest.approx(2.5)
    assert a.y == pytest.approx(0.1)
    assert a.z == pytest.approx(0.5)


def test_error_set():
    with pytest.raises(ValueError):
        a = Vec3()
        a.set(2, 3, "hello")


def test_dot():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)
    assert a.dot(b) == pytest.approx(32.0)


def test_length():
    a = Vec3(22, 1, 32)
    assert a.length() == pytest.approx(38.845, rel=1e-2)


def test_length_squared():
    a = Vec3(22, 1, 32)
    assert a.length_squared() == pytest.approx(1509, rel=1e-2)


def test_normalize():
    a = Vec3(22.3, 0.5, 10.0)
    a.normalize()
    assert a.x == pytest.approx(0.912266, rel=1e-2)
    assert a.y == pytest.approx(0.0204544, rel=1e-2)
    assert a.z == pytest.approx(0.409088, rel=1e-2)
    with pytest.raises(ZeroDivisionError):
        a = Vec3(0, 0, 0)
        a.normalize()


def test_equal():
    a = Vec3(0.1, 0.2, 0.3)
    b = Vec3(0.1, 0.2, 0.3)
    assert a == b
    assert a.__eq__(1) == NotImplemented


def test_not_equal():
    a = Vec3(0.3, 0.4, 0.3)
    b = Vec3(0.1, 0.2, 0.3)
    assert a != b
    a = Vec3(0.3, 0.4, 0.3)
    b = Vec3(0.3, 0.2, 0.3)
    assert a != b
    a = Vec3(0.3, 0.2, 0.3)
    b = Vec3(0.3, 0.4, 0.3)
    assert a != b
    a = Vec3(0.3, 0.4, 0.3)
    b = Vec3(0.3, 0.4, 0.5)
    assert a != b
    c = Vec3(1, 2, 3)
    d = Vec3(4, 5, 6)
    assert c != d
    assert a.__neq__(1) == NotImplemented


def test_inner():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(3.0, 4.0, 5.0)
    inner = a.inner(b)
    assert inner == pytest.approx(26.0)


def test_negate():
    a = Vec3(0.1, 0.5, -12)
    a = -a
    assert a.x == pytest.approx(-0.1)
    assert a.y == pytest.approx(-0.5)
    assert a.z == pytest.approx(12.0)


def test_reflect():
    N = Vec3(0, 1, 0)
    a = Vec3(2, 2, 0)
    a.normalize()
    ref = a.reflect(N)
    assert ref.x == pytest.approx(0.707, rel=1e-2)
    assert ref.y == pytest.approx(-0.707, rel=1e-2)
    assert ref.z == pytest.approx(0.0, rel=1e-2)


def test_clamp():
    a = Vec3(0.1, 5.0, 1.7)
    a.clamp(0.5, 1.8)
    assert a.x == pytest.approx(0.5)
    assert a.y == pytest.approx(1.8)
    assert a.z == pytest.approx(1.7)


def test_outer():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(3.0, 4.0, 5.0)
    outer = a.outer(b)
    result = [3, 4, 5, 6, 8, 10, 9, 12, 15]
    value = outer.get_matrix()
    assert result == pytest.approx(value)


def test_null():
    a = Vec3(2, 3, 5)
    a.null()
    assert a.x == pytest.approx(0.0)
    assert a.y == pytest.approx(0.0)
    assert a.z == pytest.approx(0.0)


def test_cross():
    a = Vec3(0.0, 1.0, 0.0)
    b = Vec3(-1.0, 0.0, 0.0)
    c = a.cross(b)
    assert c.x == pytest.approx(0.0)
    assert c.y == pytest.approx(0.0)
    assert c.z == pytest.approx(1.0)
    assert c == Vec3(0.0, 0.0, 1.0)


def test_mul_scalar():
    a = Vec3(1.0, 1.5, 2.0)
    a = a * 2
    assert a.x == pytest.approx(2.0)
    assert a.y == pytest.approx(3.0)
    assert a.z == pytest.approx(4.0)

    a = Vec3(1.5, 4.2, 2.8)
    a = 2 * a
    assert a.x == pytest.approx(3.0)
    assert a.y == pytest.approx(8.4)
    assert a.z == pytest.approx(5.6)

    with pytest.raises(ValueError):
        a = a * "hello"


def test_getAttr():
    a = Vec3(1, 2, 3)
    assert getattr(a, "x") == pytest.approx(1.0)
    assert getattr(a, "y") == pytest.approx(2.0)
    assert getattr(a, "z") == pytest.approx(3.0)

    # check to see if we can get non attr
    with pytest.raises(AttributeError):
        getattr(a, "b")
    # check to see that adding an attrib fails
    with pytest.raises(AttributeError):
        setattr(a, "b", 20.0)


def test_matmul():
    a = Vec3(1, 2, 3)
    b = Mat3.rotate_x(45.0)
    c = a @ b
    assert c.x == pytest.approx(1.0)
    assert c.y == pytest.approx(-0.707107, rel=1e-2)
    assert c.z == pytest.approx(3.535534, rel=1e-2)


def test_string():
    a = Vec3(1, 2, 3)
    assert str(a) == "[1,2,3]"
    assert repr(a) == "Vec3 [1,2,3]"


def test_iterable():
    a = Vec3(1, 2, 3)
    b = [x for x in a]
    assert b == [1, 2, 3]
    assert a[0] == 1
    assert a[1] == 2
    assert a[2] == 3
    with pytest.raises(IndexError):
        a[3]

    v = []
    v.extend(a)
    assert v == [1, 2, 3]


def test_copy():
    a = Vec3(1, 2, 3)
    b = copy.copy(a)
    assert a == b
    b.x = 10
    assert a != b
    assert a.x == 1
    assert b.x == 10


def test_clone():
    a = Vec3(1, 2, 3)
    b = a.clone()
    assert a == b
    assert a is not b  # Ensure it's a different object


def test_sizeof():
    assert Vec3.sizeof() == 12
