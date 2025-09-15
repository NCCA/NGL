import numpy as np
import pytest

from ngl import Mat3, Vec3


class TestMat3:
    def test_default_ctor(self):
        test = Mat3()
        result = Mat3(1, 0, 0, 0, 1, 0, 0, 0, 1)
        assert test == result

    def test_null(self):
        test = Mat3()
        test.null()
        result = Mat3(0, 0, 0, 0, 0, 0, 0, 0, 0)
        assert test == result

    def test_identity(self):
        test = Mat3(1, 2, 3, 4, 5, 6, 7, 8, 9)
        test.identity()
        result = Mat3(1, 0, 0, 0, 1, 0, 0, 0, 1)
        assert test == result

    def test_float_ctor(self):
        test = Mat3(2.0)
        result = Mat3(2, 0, 0, 0, 2, 0, 0, 0, 2)
        assert test == result

    def test_copy_ctor(self):
        test = Mat3(2.0)
        copy = Mat3(test)
        result = Mat3(2, 0, 0, 0, 2, 0, 0, 0, 2)
        assert copy == result

    def test_assign_operator(self):
        test = Mat3(2.0)
        copy = test
        result = Mat3(2, 0, 0, 0, 2, 0, 0, 0, 2)
        assert copy == result

    def test_transpose(self):
        test = Mat3(1, 2, 3, 4, 5, 6, 7, 8, 9)
        test.transpose()
        result = Mat3(1, 4, 7, 2, 5, 8, 3, 6, 9)
        assert test == result

    def test_scale(self):
        test = Mat3.scale(1.0, 2.0, 3.0)
        result = Mat3(1, 0, 0, 0, 2, 0, 0, 0, 3)
        assert test == result

    def test_rotate_x(self):
        test = Mat3.rotateX(45.0)
        result = Mat3(1.0, 0.0, 0.0, 0.0, 0.707107, 0.707107, 0.0, -0.707107, 0.707107)
        assert test == result

    def test_rotate_y(self):
        test = Mat3.rotateY(25.0)
        result = Mat3(0.906308, 0.0, -0.422618, 0.0, 1.0, 0.0, 0.422618, 0.0, 0.906308)
        assert test == result

    def test_rotate_z(self):
        test = Mat3.rotateZ(-36.0)
        result = Mat3(0.809017, -0.587785, 0.0, 0.587785, 0.809017, 0.0, 0.0, 0.0, 1.0)
        assert test == result

    def test_mat3_x_mat3(self):
        t1 = Mat3.rotateX(45.0)
        t2 = Mat3.rotateY(35.0)
        test = t1 * t2
        result = Mat3(0.819152, 0.0, -0.573577, 0.40558, 0.707107, 0.579228, 0.40558, -0.707107, 0.579228)
        assert test == result

    def test_plus_equal(self):
        t1 = Mat3.rotateX(45.0)
        t2 = Mat3.rotateY(35.0)
        t1 += t2
        result = Mat3(1.81915, 0, -0.573577, 0, 1.70711, 0.707107, 0.573577, -0.707107, 1.52626)
        assert t1 == result

    def test_plus(self):
        t1 = Mat3.rotateX(45.0)
        t2 = Mat3.rotateY(35.0)
        res = t1 + t2
        result = Mat3(1.81915, 0, -0.573577, 0, 1.70711, 0.707107, 0.573577, -0.707107, 1.52626)
        assert res == result

    def test_mat3_x_real(self):
        test = Mat3(0, 1, 2, 3, 4, 5, 6, 7, 8)
        test = test * 4.2
        result = Mat3(0.0, 4.2, 8.4, 12.6, 16.8, 21.0, 25.2, 29.4, 33.6)
        # It is difficult to assert floating point values so we will round them
        assert np.allclose(test.m, result.m, atol=1e-5)

    def test_mat3_x_equal_real(self):
        test = Mat3(0, 1, 2, 3, 4, 5, 6, 7, 8)
        test *= 4.2
        result = Mat3(0.0, 4.2, 8.4, 12.6, 16.8, 21.0, 25.2, 29.4, 33.6)
        assert np.allclose(test.m, result.m, atol=1e-5)

    def test_determinant(self):
        test = Mat3(1, 0, 0, 0, 2, 2, 0, -0.5, 2)
        det = test.determinant()
        assert det == pytest.approx(5.0)

    def test_inverse(self):
        test = Mat3(1, 0, 0, 0, 2, 2, 0, -0.5, 2)
        test.inverse()
        result = Mat3(1.0, 0.0, 0.0, 0.0, 0.4, -0.4, 0.0, 0.1, 0.4)
        assert test == result

    def test_vec3_x_mat3(self):
        t1 = Mat3.rotateX(45.0)
        test = Vec3(2, 1, 2)
        test = test * t1
        result = Vec3(2, -0.707107, 2.12132)
        assert test == result
