import math

import numpy as np
import pytest

from ngl import Mat4, Vec4


def test_default_ctor():
    test = Mat4()
    result = Mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0)
    assert test == result


def test_null():
    test = Mat4()
    test.null()
    result = Mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    assert test == result


def test_identity():
    test = Mat4()
    test.identity()
    result = Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)
    assert test == result


def test_float_ctor():
    test = Mat4(2.0)
    result = Mat4(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1)
    # This is different from the C++ version, which sets the last element to 1.
    # In our python version, the constructor with a single scalar creates a scaled identity matrix.
    # We will adjust the test to match the python implementation.
    result = Mat4()
    result[0] = 2.0
    result[5] = 2.0
    result[10] = 2.0
    assert test == result


def test_copy_ctor():
    test = Mat4(2.0)
    copy = Mat4(*test._m)
    result = Mat4(2.0)
    assert copy == result


def test_assign_operator():
    test = Mat4(2.0)
    copy = test
    result = Mat4(2.0)
    assert copy == result


def test_translate():
    test = Mat4.translate(1.0, 2.0, 3.0)
    result = Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 2, 3, 1)
    assert test == result


def test_transpose():
    test = Mat4.translate(1.0, 2.0, 3.0)
    test.transpose()
    result = Mat4(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1)
    assert test == result


def test_scale():
    test = Mat4.scale(1.0, 2.0, 3.0)
    result = Mat4(1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1)
    assert test == result


def test_rotate_x():
    angle = 45.0
    test = Mat4.rotate_x(angle)
    rad = math.radians(angle)
    c = math.cos(rad)
    s = math.sin(rad)
    result = Mat4(1, 0, 0, 0, 0, c, s, 0, 0, -s, c, 0, 0, 0, 0, 1)
    assert test == result


def test_rotate_y():
    angle = 35.0
    test = Mat4.rotate_y(angle)
    rad = math.radians(angle)
    c = math.cos(rad)
    s = math.sin(rad)
    result = Mat4(c, 0, -s, 0, 0, 1, 0, 0, s, 0, c, 0, 0, 0, 0, 1)
    assert test == result


def test_rotate_z():
    angle = 25.0
    test = Mat4.rotate_z(angle)
    rad = math.radians(angle)
    c = math.cos(rad)
    s = math.sin(rad)
    result = Mat4(c, s, 0, 0, -s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)
    assert test == result


def test_mat4_x_mat4():
    t1 = Mat4.rotate_x(45.0)
    t2 = Mat4.rotate_y(35.0)
    test = t1 * t2
    result = Mat4(
        0.819152, 0.40558, -0.40558, 0, 0, 0.707107, 0.707107, 0, 0.573577, -0.579228, 0.579228, 0, 0, 0, 0, 1
    )
    assert np.allclose(test._m, result._m, atol=1e-6)


def test_mat4_plus_equal():
    t1 = Mat4.rotate_x(45.0)
    t2 = Mat4.rotate_y(35.0)
    t1 += t2
    result = Mat4(1.81915, 0, -0.573577, 0, 0, 1.70711, 0.707107, 0, 0.573577, -0.707107, 1.52626, 0, 0, 0, 0, 2)
    assert np.allclose(t1._m, result._m, atol=1e-5)


def test_mat4_plus():
    t1 = Mat4.rotate_x(45.0)
    t2 = Mat4.rotate_y(35.0)
    res = t1 + t2
    result = Mat4(1.81915, 0, -0.573577, 0, 0, 1.70711, 0.707107, 0, 0.573577, -0.707107, 1.52626, 0, 0, 0, 0, 2)
    assert np.allclose(res._m, result._m, atol=1e-5)


def test_mat4_x_real():
    test = Mat4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)
    test = test * 4.2
    result = Mat4(4.2, 8.4, 12.6, 16.8, 21.0, 25.2, 29.4, 33.6, 37.8, 42.0, 46.2, 50.4, 54.6, 58.8, 63.0, 67.2)
    assert test == result


def test_mat4_x_equal_real():
    test = Mat4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)
    test *= 4.2
    result = Mat4(4.2, 8.4, 12.6, 16.8, 21.0, 25.2, 29.4, 33.6, 37.8, 42.0, 46.2, 50.4, 54.6, 58.8, 63.0, 67.2)
    assert test == result


def test_determinant():
    test = Mat4(1, 0, 0, 0, 0, 2, 2, 0, 0, -0.5, 2, 0, 0, 0, 0, 1)
    det = test.determinant()
    assert det == pytest.approx(5.0)


def test_inverse():
    test = Mat4(1, 0, 0, 0, 0, 2, 2, 0, 0, -0.5, 2, 0, 0, 0, 0, 1)
    test = test.inverse()
    result = Mat4(1, 0, 0, 0, 0, 0.4, -0.4, 0, 0, 0.1, 0.4, 0, 0, 0, 0, 1)
    assert np.allclose(test._m, result._m, atol=1e-6)


def test_mat4_x_vec4():
    t1 = Mat4.rotate_x(45.0)
    test = Vec4(2, 1, 2, 1)
    result_vec = t1 * test
    expected = Vec4(2, -0.707107, 2.12132, 1)
    assert np.allclose(result_vec._m, expected._m, atol=1e-5)


def test_vec4_x_mat4():
    t1 = Mat4.rotate_x(45.0)
    test = Vec4(2, 1, 2, 1)
    result_vec = test * t1
    expected = Vec4(2, 2.12132, 0.707107, 1)
    assert np.allclose(result_vec._m, expected._m, atol=1e-5)


def test_as_quaternion():
    tx = Mat4.rotate_x(45.0)
    test = tx.as_quaternion()
    assert test.s == pytest.approx(0.92388, abs=1e-5)
    assert test.x == pytest.approx(0.382683, abs=1e-5)
    assert test.y == 0.0
    assert test.z == 0.0
