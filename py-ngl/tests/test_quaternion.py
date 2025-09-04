import math

import numpy as np
import pytest

from ngl import Mat4, Quaternion, Vec3, Vec4


def test_default_ctor():
    test = Quaternion()
    assert test.s == 1.0
    assert test.x == 0.0
    assert test.y == 0.0
    assert test.z == 0.0


def test_user_ctor():
    test = Quaternion(0.2, 0.0, 1.0, 0.0)
    assert test.s == 0.2
    assert test.x == 0.0
    assert test.y == 1.0
    assert test.z == 0.0


def test_addition():
    q1 = Quaternion(0.5, 1.0, 0.0, 0.0)
    q2 = Quaternion(0.2, 0.0, 1.0, 0.0)
    res = q1 + q2
    assert res.s == 0.7
    assert res.x == 1.0
    assert res.y == 1.0
    assert res.z == 0.0


def test_addition_equal():
    q1 = Quaternion(0.5, 1.0, 0.0, 0.0)
    q2 = Quaternion(0.2, 0.0, 1.0, 0.0)
    q1 += q2
    assert q1.s == 0.7
    assert q1.x == 1.0
    assert q1.y == 1.0
    assert q1.z == 0.0


def test_subtract():
    q1 = Quaternion(0.5, 1.0, 1.0, 0.0)
    q2 = Quaternion(0.2, 1.0, 1.0, 0.0)
    res = q1 - q2
    assert res.s == pytest.approx(0.3)
    assert res.x == 0.0
    assert res.y == 0.0
    assert res.z == 0.0


def test_subtract_equal():
    q1 = Quaternion(0.5, 1.0, 1.0, 0.0)
    q2 = Quaternion(0.2, 1.0, 1.0, 0.0)
    q1 -= q2
    assert q1.s == pytest.approx(0.3)
    assert q1.x == 0.0
    assert q1.y == 0.0
    assert q1.z == 0.0


def test_multiply_quat():
    q1 = Quaternion(-math.sin(math.pi), 3.0, 4.0, 3.0)
    q2 = Quaternion(4.0, 3.9, -1.0, -3.0)
    res = q1 * q2
    assert res.s == pytest.approx(1.3)
    assert res.x == pytest.approx(3.0)
    assert res.y == pytest.approx(36.7)
    assert res.z == pytest.approx(-6.6)


def test_multiply_equal_quat():
    q1 = Quaternion(-math.sin(math.pi), 3.0, 4.0, 3.0)
    q2 = Quaternion(4.0, 3.9, -1.0, -3.0)
    q1 *= q2
    assert q1.s == pytest.approx(1.3)
    assert q1.x == pytest.approx(3.0)
    assert q1.y == pytest.approx(36.7)
    assert q1.z == pytest.approx(-6.6)


def test_magnitude():
    q1 = Quaternion(1.3, 3.0, 36.7, -6.6)
    assert q1.magnitude() == pytest.approx(37.4318)


def test_normalize():
    q1 = Quaternion(1.3, 3.0, 36.7, -6.6)
    q1.normalize()
    assert q1.s == pytest.approx(0.0347298, abs=1e-4)
    assert q1.x == pytest.approx(0.0801457, abs=1e-4)
    assert q1.y == pytest.approx(0.98045, abs=1e-4)
    assert q1.z == pytest.approx(-0.176321, abs=1e-4)


def test_conjugate():
    q1 = Quaternion(1.3, 3.0, 36.7, -6.6)
    q1 = q1.conjugate()
    assert q1.s == 1.3
    assert q1.x == -3.0
    assert q1.y == -36.7
    assert q1.z == 6.6


def test_inverse():
    q1 = Quaternion(1.3, -3.0, -36.7, 6.6)
    q1 = q1.inverse()
    assert q1.s == pytest.approx(0.000927816, abs=1e-5)
    assert q1.x == pytest.approx(0.00214111, abs=1e-5)
    assert q1.y == pytest.approx(0.026193, abs=1e-5)
    assert q1.z == pytest.approx(-0.00471045, abs=1e-5)


def test_from_axis_angle():
    q = Quaternion.from_axis_angle(Vec3(1, 0, 0), 45.0)
    assert q.s == pytest.approx(0.92388, abs=1e-5)
    assert q.x == pytest.approx(0.382683, abs=1e-5)
    assert q.y == 0.0
    assert q.z == 0.0


def test_to_axis_angle():
    q = Quaternion.from_axis_angle(Vec3(1, 0, 0), 45.0)
    axis, angle = q.to_axis_angle()
    assert angle == pytest.approx(45.0)
    assert axis == Vec3(1, 0, 0)


def test_to_mat4():
    q = Quaternion.from_axis_angle(Vec3(1, 0, 0), 45.0)
    m = q.to_mat4()
    m2 = Mat4.rotate_x(45.0)
    assert m == m2


def test_slerp():
    start = Quaternion(0.674380, -0.212631, 0.674380, 0.212631)
    end = Quaternion(0.612372, 0.353553, -0.612372, -0.353553)
    for i in np.arange(0.0, 1.1, 0.1):
        s1 = Quaternion.slerp(start, end, i)
        # The glm results are not available, so we can only do a basic check
        assert isinstance(s1, Quaternion)


def test_times_equal_float():
    a = Quaternion(0.2, 0.1, 0.3, 0.5)
    a *= 2.0
    assert a.s == 0.4
    assert a.x == 0.2
    assert a.y == 0.6
    assert a.z == 1.0


def test_mult_vec4():
    a = Quaternion(0.2, 0.1, 0.3, 0.5)
    b = Vec4(1.0, 2.0, 3.0, 1.0)
    c = a * b
    assert c.x == pytest.approx(0.7, abs=1e-5)
    assert c.y == pytest.approx(2.0, abs=1e-5)
    assert c.z == pytest.approx(3.06, abs=1e-5)
    assert c.w == 1.0
