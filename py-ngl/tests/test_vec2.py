import math

import pytest

from ngl import Vec2


def test_init():
    v = Vec2(1.0, 2.0)
    assert v.x == 1.0
    assert v.y == 2.0
    v = Vec2()
    assert v.x == 0.0
    assert v.y == 0.0


def test_iter():
    v = Vec2(1.0, 2.0)
    assert list(v) == [1.0, 2.0]


def test_clone():
    v1 = Vec2(1.0, 2.0)
    v2 = v1.clone()
    assert v1 == v2
    assert v1 is not v2


def test_getitem():
    v = Vec2(1.0, 2.0)
    assert v[0] == 1.0
    assert v[1] == 2.0
    with pytest.raises(IndexError):
        v[2]


def test_validate_and_set():
    v = Vec2()
    v.x = 1.0
    assert v.x == 1.0
    with pytest.raises(ValueError):
        v.y = "hello"


def test_add():
    v1 = Vec2(1.0, 2.0)
    v2 = Vec2(3.0, 4.0)
    v3 = v1 + v2
    assert v3.x == 4.0
    assert v3.y == 6.0


def test_iadd():
    v1 = Vec2(1.0, 2.0)
    v2 = Vec2(3.0, 4.0)
    v1 += v2
    assert v1.x == 4.0
    assert v1.y == 6.0


def test_sub():
    v1 = Vec2(1.0, 2.0)
    v2 = Vec2(3.0, 4.0)
    v3 = v1 - v2
    assert v3.x == -2.0
    assert v3.y == -2.0


def test_isub():
    v1 = Vec2(1.0, 2.0)
    v2 = Vec2(3.0, 4.0)
    v1 -= v2
    assert v1.x == -2.0
    assert v1.y == -2.0


def test_eq():
    v1 = Vec2(1.0, 2.0)
    v2 = Vec2(1.0, 2.0)
    assert v1 == v2
    v3 = Vec2(2.0, 2.0)
    assert v1 != v3
    assert (v1 == "hello") is False


def test_neq():
    v1 = Vec2(1.0, 2.0)
    v2 = Vec2(1.0, 2.0)
    assert not (v1 != v2)
    v3 = Vec2(2.0, 2.0)
    assert v1 != v3
    v4 = Vec2(3.0, 4.0)
    assert v1 != v4
    assert (v1 != 1) is True


def test_neq_not_implemented():
    v = Vec2(1, 2)
    assert v.__neq__(2) is NotImplemented


def test_neg():
    v1 = Vec2(1.0, 2.0)
    v2 = -v1
    assert v2.x == -1.0
    assert v2.y == -2.0


def test_set():
    v = Vec2()
    v.set(1.0, 2.0)
    assert v.x == 1.0
    assert v.y == 2.0
    with pytest.raises(ValueError):
        v.set("a", "b")


def test_dot():
    v1 = Vec2(1.0, 2.0)
    v2 = Vec2(3.0, 4.0)
    assert v1.dot(v2) == 11.0


def test_length():
    v = Vec2(3.0, 4.0)
    assert v.length() == 5.0


def test_length_squared():
    v = Vec2(3.0, 4.0)
    assert v.length_squared() == 25.0


def test_inner():
    v1 = Vec2(1.0, 2.0)
    v2 = Vec2(3.0, 4.0)
    assert v1.inner(v2) == 11.0


def test_null():
    v = Vec2(1.0, 2.0)
    v.null()
    assert v.x == 0.0
    assert v.y == 0.0


def test_cross():
    v1 = Vec2(1.0, 2.0)
    v2 = Vec2(3.0, 4.0)
    assert v1.cross(v2) == -2.0


def test_normalize():
    v = Vec2(3.0, 4.0)
    v.normalize()
    assert math.isclose(v.length(), 1.0)
    v = Vec2(0.0, 0.0)
    with pytest.raises(ZeroDivisionError):
        v.normalize()


def test_reflect():
    v = Vec2(1.0, -1.0)
    n = Vec2(0.0, 1.0)
    r = v.reflect(n)
    assert r.x == 1.0
    assert r.y == 1.0


def test_clamp():
    v = Vec2(1.5, -1.5)
    v.clamp(0.0, 1.0)
    assert v.x == 1.0
    assert v.y == 0.0


def test_repr():
    v = Vec2(1.0, 2.0)
    assert repr(v) == "Vec2 [1.0,2.0]"


def test_truediv():
    v = Vec2(2.0, 4.0)
    v2 = v / 2.0
    assert v2.x == 1.0
    assert v2.y == 2.0


def test_str():
    v = Vec2(1.0, 2.0)
    assert str(v) == "[1.0,2.0]"


def test_mul():
    v = Vec2(1.0, 2.0)
    v2 = v * 2.0
    assert v2.x == 2.0
    assert v2.y == 4.0
    with pytest.raises(ValueError):
        v * "a"


def test_rmul():
    v = Vec2(1.0, 2.0)
    v2 = 2.0 * v
    assert v2.x == 2.0
    assert v2.y == 4.0


def test_sizeof():
    assert Vec2.sizeof() == 8
