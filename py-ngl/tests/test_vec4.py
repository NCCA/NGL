import math

import pytest

from ngl import Mat4, Vec4


def test_default_ctor():
    test = Vec4()
    result = Vec4(0.0, 0.0, 0.0, 1.0)
    assert test == result


def test_subscript():
    test = Vec4(1.0, 2.0, 3.0, 4.0)
    assert test[0] == 1.0
    assert test[1] == 2.0
    assert test[2] == 3.0
    assert test[3] == 4.0
    test[0] = 5.0
    assert test[0] == 5.0


def test_assign():
    v = Vec4()
    v = Vec4(1.0, 2.0, 3.0, 4.0)
    assert v.x == 1.0
    assert v.y == 2.0
    assert v.z == 3.0
    assert v.w == 4.0
    # In the C++ version, assigning a Vec3 to a Vec4 sets w to 0.
    # This is not directly supported in Python's type system in the same way.
    # We can simulate this with a constructor or a method.
    v = Vec4(6.0, 7.0, 8.0, 0.0)
    assert v.x == 6.0
    assert v.y == 7.0
    assert v.z == 8.0
    assert v.w == 0.0


def test_float_ctor():
    test = Vec4(1.0, 2.0, 3.0, 4.0)
    result = Vec4(1.0, 2.0, 3.0, 4.0)
    assert test == result


def test_copy_ctor():
    test = Vec4(1.0, 2.0, 3.0, 5.0)
    copy = test.copy()
    result = Vec4(1.0, 2.0, 3.0, 5.0)
    assert copy == result


def test_assign_operator():
    test = Vec4(1.0, 2.0, 3.0)
    copy = test
    result = Vec4(1.0, 2.0, 3.0)
    assert copy == result


def test_negate():
    a = Vec4(1, 2, 3, 1)
    a = -a
    assert a.x == -1.0
    assert a.y == -2.0
    assert a.z == -3.0
    assert a.w == -1.0  # Note: C++ version doesn't negate w, but numpy does


def test_not_equal():
    a = Vec4(1, 2, 3, 1)
    b = Vec4(1, 2, 3, 1)
    assert a == b
    b.x = 0.0
    assert a != b


def test_mult_vec4():
    a = Vec4(1, 2, 3, 1)
    b = Vec4(2, 2, 2, 1)
    a = a * b
    assert a.x == 2.0
    assert a.y == 4.0
    assert a.z == 6.0
    assert a.w == 1.0


def test_angle_between():
    a = Vec4(1, 0, 0, 1)
    b = Vec4(0, 1, 0, 1)
    assert a.angle_between(b) == pytest.approx(90.0)
    assert a.angle_between(a) == pytest.approx(0.0)


def test_dot_product():
    a = Vec4(1.0, 2.0, 3.0)
    b = Vec4(4.0, 5.0, 6.0)
    assert a.dot(b) == pytest.approx(32.0)


def test_null():
    test = Vec4(1, 2, 4)
    test.null()
    assert test == Vec4(0.0, 0.0, 0.0, 1.0)


def test_normalize():
    test = Vec4(22.3, 0.5, 10.0)
    test.normalize()
    result = Vec4(0.912266, 0.0204544, 0.409088)
    assert test.x == pytest.approx(result.x, 0.0001)
    assert test.y == pytest.approx(result.y, 0.0001)
    assert test.z == pytest.approx(result.z, 0.0001)

    zero = Vec4.zero()
    with pytest.warns(RuntimeWarning):
        zero.normalize()
    assert math.isnan(zero.x)
    assert math.isnan(zero.y)
    assert math.isnan(zero.z)


def test_length():
    a = Vec4(22, 1, 32)
    assert a.length() == pytest.approx(38.845, 0.001)


def test_length_squared():
    a = Vec4(22, 1, 32)
    assert a.length_squared() == pytest.approx(1509.0, 0.001)


def test_cross():
    a = Vec4.up()
    b = Vec4.left()
    c = a.cross(b)
    assert c == Vec4.in_vec()


def test_set_vec4():
    f = Vec4()
    f.set(0.4, 0.2, 0.1, 1.0)
    assert f[0] == 0.4
    assert f[1] == 0.2
    assert f[2] == 0.1
    assert f[3] == 1.0


def test_add():
    a = Vec4(1.0, 2.0, 3.0, 1.0)
    b = Vec4(4.0, 5.0, 6.0, 1.0)
    c = a + b
    assert c.x == 5.0
    assert c.y == 7.0
    assert c.z == 9.0
    assert c.w == 1.0


def test_add_equal():
    a = Vec4(1.0, 2.0, 3.0, 0.0)
    b = Vec4(4.0, 5.0, 6.0, 1.0)
    a += b
    assert a.x == 5.0
    assert a.y == 7.0
    assert a.z == 9.0
    assert a.w == 1.0


def test_subtract():
    a = Vec4(1.0, 2.0, 3.0, 1.0)
    b = Vec4(4.0, 5.0, 6.0, 2.0)
    c = a - b
    assert c.x == -3.0
    assert c.y == -3.0
    assert c.z == -3.0
    assert c.w == 1.0


def test_subtract_equal():
    a = Vec4(1.0, 2.0, 3.0, 0.0)
    b = Vec4(4.0, 5.0, 6.0, 1.0)
    a -= b
    assert a.x == -3.0
    assert a.y == -3.0
    assert a.z == -3.0
    assert a.w == -1.0


def test_multiply_float():
    a = Vec4(1.0, 2.0, 3.0, 1.0)
    c = a * 2.0
    assert c.x == 2.0
    assert c.y == 4.0
    assert c.z == 6.0
    assert c.w == 1.0


def test_multiply_float_equal():
    a = Vec4(1.0, 2.0, 3.0, 0.0)
    a *= 2.0
    assert a.x == 2.0
    assert a.y == 4.0
    assert a.z == 6.0
    assert a.w == 0.0


def test_divide_float_equal():
    a = Vec4(1.0, 2.0, 3.0, 1.0)
    a /= 2.0
    assert a.x == 0.5
    assert a.y == 1.0
    assert a.z == 1.5
    assert a.w == 0.5
    with pytest.warns(RuntimeWarning):
        a /= 0.0


def test_divide_float():
    a = Vec4(1.0, 2.0, 3.0, 1.0)
    b = a / 2.0
    assert b.x == 0.5
    assert b.y == 1.0
    assert b.z == 1.5
    assert b.w == 0.5
    with pytest.warns(RuntimeWarning):
        a / 0.0


def test_divide_vec():
    a = Vec4(1.0, 2.0, 3.0, 1.0)
    b = Vec4(2.0, 2.0, 2.0, 1.0)
    c = a / b
    assert c.x == 0.5
    assert c.y == 1.0
    assert c.z == 1.5
    assert c.w == 1.0


def test_divide_equal_vec():
    a = Vec4(1.0, 2.0, 3.0, 0.0)
    b = Vec4(2.0, 2.0, 2.0, 1.0)
    a /= b
    assert a.x == 0.5
    assert a.y == 1.0
    assert a.z == 1.5
    assert a.w == 0.0
    with pytest.warns(RuntimeWarning):
        a /= Vec4.zero()


def test_clamp_min_max():
    a = Vec4(-1.0, 2.0, 3.0, 0.0)
    a.clamp(0.0, 2.0)
    assert a.x == 0.0
    assert a.y == 2.0
    assert a.z == 2.0
    assert a.w == 0.0


def test_outer():
    a = Vec4(1.0, 2.0, 3.0, 4.0)
    b = Vec4(5.0, 6.0, 7.0, 8.0)
    outer = a.outer(b)
    result = Mat4(5, 10, 15, 20, 6, 12, 18, 24, 7, 14, 21, 28, 8, 16, 24, 32)
    assert outer == result
