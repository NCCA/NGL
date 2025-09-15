import numpy as np

from ngl import Mat2, Vec2


class TestMat2:
    def test_default_ctor(self):
        test = Mat2()
        result = Mat2(1, 0, 0, 1)
        assert test == result

    def test_null(self):
        test = Mat2()
        test.null()
        result = Mat2(0, 0, 0, 0)
        assert test == result

    def test_identity(self):
        test = Mat2(1, 2, 3, 4)
        test.identity()
        result = Mat2(1, 0, 0, 1)
        assert test == result

    def test_float_ctor(self):
        test = Mat2(2.0)
        result = Mat2(2, 0, 0, 2)
        assert test == result

    def test_copy_ctor(self):
        test = Mat2(2.0)
        copy = Mat2(test)
        result = Mat2(2, 0, 0, 2)
        assert copy == result

    def test_assign_operator(self):
        test = Mat2(2.0)
        copy = test
        result = Mat2(2, 0, 0, 2)
        assert copy == result

    def test_transpose(self):
        test = Mat2(1, 2, 3, 4)
        test.transpose()
        result = Mat2(1, 3, 2, 4)
        assert test == result

    def test_scale(self):
        test = Mat2.scale(1.0, 2.0)
        result = Mat2(1, 0, 0, 2)
        assert test == result

    def test_rotate(self):
        test = Mat2.rotate(45.0)
        result = Mat2(0.707107, -0.707107, 0.707107, 0.707107)
        assert test == result

    def test_mat2_x_mat2(self):
        t1 = Mat2(1, 2, 3, 4)
        t2 = Mat2(5, 6, 7, 8)
        result = t1 * t2
        assert result == Mat2(19, 22, 43, 50)

    def test_mat2_x_equals(self):
        t1 = Mat2(1, 2, 3, 4)
        t2 = Mat2(5, 6, 7, 8)
        t1 *= t2
        assert t1 == Mat2(19, 22, 43, 50)

    def test_plus_equal(self):
        t1 = Mat2(1, 2, 3, 4)
        t2 = Mat2(5, 6, 7, 8)
        t1 += t2
        assert t1 == Mat2(6, 8, 10, 12)

    def test_plus(self):
        t1 = Mat2(1, 2, 3, 4)
        t2 = Mat2(5, 6, 7, 8)
        res = t1 + t2
        assert res == Mat2(6, 8, 10, 12)

    def test_mat2_x_real(self):
        test = Mat2(1, 2, 3, 4)
        test = test * 4.0
        assert test == Mat2(4, 8, 12, 16)

    def test_mat2_x_equal_real(self):
        test = Mat2(1, 2, 3, 4)
        test *= 4.0
        assert test == Mat2(4, 8, 12, 16)

    def test_vec2_x_mat2(self):
        t1 = Mat2(1, 2, 3, 4)
        test = Vec2(1, 2)
        test = t1 * test
        result = Vec2(5, 11)
        assert test == result

    def test_sizeof(self):
        test = Mat2()
        assert test.sizeof() == 4 * np.float32().nbytes
