import math

import pytest

from ngl import Vec3


def test_default_ctor():
    test = Vec3()
    result = Vec3(0.0, 0.0, 0.0)
    assert test == result


def test_dot_product():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)
    assert a.dot(b) == pytest.approx(32.0)


def test_null():
    test = Vec3(1, 2, 4)
    test.null()
    assert test == Vec3.zero()


def test_normalize():
    test = Vec3(22.3, 0.5, 10.0)
    test.normalize()
    result = Vec3(0.912266, 0.0204544, 0.409088)
    assert test == result

    zero = Vec3.zero()
    zero.normalize()
    assert math.isnan(zero.x)
    assert math.isnan(zero.y)
    assert math.isnan(zero.z)


def test_inner():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(3.0, 4.0, 5.0)
    assert a.inner(b) == pytest.approx(26.0)


def test_length():
    a = Vec3(22, 1, 32)
    assert a.length() == pytest.approx(38.845, 0.001)


def test_length_squared():
    a = Vec3(22, 1, 32)
    assert a.length_squared() == pytest.approx(1509.0, 0.001)


def test_cross():
    a = Vec3.up()
    b = Vec3.left()
    c = a.cross(b)
    assert c == Vec3.in_()


def test_subscript():
    test = Vec3(1.0, 2.0, 3.0)
    assert test[0] == 1.0
    assert test[1] == 2.0
    assert test[2] == 3.0
    test[0] = 4.0
    assert test[0] == 4.0


def test_float_ctor():
    test = Vec3(1.0, 2.0, 3.0)
    result = Vec3(1.0, 2.0, 3.0)
    assert test == result


def test_copy_ctor():
    test = Vec3(1.0, 2.0, 3.0)
    copy = Vec3(test.x, test.y, test.z)
    result = Vec3(1.0, 2.0, 3.0)
    assert copy == result


def test_assign_operator():
    test = Vec3(1.0, 2.0, 3.0)
    copy = test
    result = Vec3(1.0, 2.0, 3.0)
    assert copy == result
    assert test[0] == copy[0]
    assert test[1] == copy[1]
    assert test[2] == copy[2]


def test_set():
    v = Vec3()
    v.set(1.0, 2.0, 3.0)
    assert v[0] == 1.0
    assert v[1] == 2.0
    assert v[2] == 3.0


def test_negate():
    v = Vec3(1.0, 2.0, 3.0)
    v = -v
    assert v[0] == -1.0
    assert v[1] == -2.0
    assert v[2] == -3.0


def test_equality():
    v = Vec3(1.0, 2.0, 3.0)
    v1 = Vec3(1.0, 2.0, 3.0)
    assert v == v1
    assert not (v != v1)
    v1.set(2.0, 3.0, 4.0)
    assert not (v == v1)
    assert v != v1
    test = Vec3()
    zero = Vec3.zero()
    one = Vec3(1.0, 1.0, 1.0)
    assert test == zero
    assert not (test == one)
    assert test != one
    assert not (test != zero)


def test_mult_vec3():
    v = Vec3(1.0, 2.0, 3.0)
    v1 = Vec3(2.0, 3.0, 4.0)
    v = v * v1
    assert v[0] == 2.0
    assert v[1] == 6.0
    assert v[2] == 12.0


def test_add():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)
    c = a + b
    assert c.x == 5.0
    assert c.y == 7.0
    assert c.z == 9.0


def test_add_equal():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)
    a += b
    assert a.x == 5.0
    assert a.y == 7.0
    assert a.z == 9.0


def test_subtract():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)
    c = a - b
    assert c.x == -3.0
    assert c.y == -3.0
    assert c.z == -3.0


def test_subtract_equal():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)
    a -= b
    assert a.x == -3.0
    assert a.y == -3.0
    assert a.z == -3.0


def test_multiply_float():
    a = Vec3(1.0, 2.0, 3.0)
    c = a * 2.0
    assert c.x == 2.0
    assert c.y == 4.0
    assert c.z == 6.0
    c = 2.0 * a
    assert c.x == 2.0
    assert c.y == 4.0
    assert c.z == 6.0


def test_multiply_float_equal():
    a = Vec3(1.0, 2.0, 3.0)
    a *= 2.0
    assert a.x == 2.0
    assert a.y == 4.0
    assert a.z == 6.0


def test_divide_float_equal():
    a = Vec3(1.0, 2.0, 3.0)
    a /= 2.0
    assert a.x == 0.5
    assert a.y == 1.0
    assert a.z == 1.5
    with pytest.warns(RuntimeWarning):
        a /= 0.0


def test_divide_float():
    a = Vec3(1.0, 2.0, 3.0)
    b = a / 2.0
    assert b.x == 0.5
    assert b.y == 1.0
    assert b.z == 1.5
    with pytest.warns(RuntimeWarning):
        a / 0.0


def test_divide_vec():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(2.0, 2.0, 2.0)
    c = a / b
    assert c.x == 0.5
    assert c.y == 1.0
    assert c.z == 1.5
    with pytest.warns(RuntimeWarning):
        a / Vec3.zero()


def test_divide_equal_vec():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(2.0, 2.0, 2.0)
    a /= b
    assert a.x == 0.5
    assert a.y == 1.0
    assert a.z == 1.5
    with pytest.warns(RuntimeWarning):
        a /= Vec3.zero()


def test_reflect():
    v = Vec3(0.5, 0.5, 0.0)
    n = Vec3(0.0, 1.0, 0.0)
    r = v.reflect(n)
    assert r.x == 0.5
    assert r.y == -0.5
    assert r.z == 0.0


def test_clamp_min_max():
    a = Vec3(-1.0, 2.0, 3.0)
    a.clamp(0.0, 2.0)
    assert a.x == 0.0
    assert a.y == 2.0
    assert a.z == 2.0
