import mat3Data  # this is generated from the julia file gen_mat4_tests.jl
import pytest

from ngl import Mat3, Mat3Error, Mat3NotSquare, Mat4, Vec3


def test_ctor():
    m = Mat3()
    ident = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
    assert m.get_matrix() == pytest.approx(ident)


def test_identity():
    m = Mat3.identity()
    values = m.get_matrix()
    ident = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
    assert values == pytest.approx(ident)


def test_get_numpy():
    m = Mat3.from_list([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    n = m.get_numpy()
    value = 1
    for c in range(0, 3):
        for r in range(0, 3):
            assert n[c][r] == value
            value += 1


def test_zero():
    m = Mat3.zero()
    values = m.get_matrix()
    ident = [0.0] * 9
    assert values == pytest.approx(ident)


def test_from_list():
    m = Mat3.from_list([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]])
    result = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0]
    assert m.get_matrix() == pytest.approx(result)
    m = Mat3.from_list([1, 2, 3, 4, 5, 6, 7, 8, 9])
    assert m.get_matrix() == pytest.approx(result)


def test_not_square():
    with pytest.raises(Mat3NotSquare):
        Mat3.from_list([[1.0, 2.0, 3.0, 50], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]])

    with pytest.raises(Mat3NotSquare):
        Mat3.from_list([[1, 2, 3], [4, 5, 6], [7, 8, 9], []])


def test_transpose():
    a = Mat3.from_list([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    a.transpose()
    result = [1, 4, 7, 2, 5, 8, 3, 6, 9]
    assert a.get_matrix() == pytest.approx(result)


def test_get_transpose():
    a = Mat3.from_list([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    b = a.get_transpose()
    result = [1, 4, 7, 2, 5, 8, 3, 6, 9]
    assert b.get_matrix() == pytest.approx(result)


def test_scale():
    a = Mat3.scale(2.0, 3.0, 4.0)
    result = [2.0, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 4.0]
    assert a.get_matrix() == pytest.approx(result)


def test_rotate_x():
    a = Mat3.rotate_x(45.0)
    result = [1.0, 0.0, 0.0, 0.0, 0.707107, 0.707107, 0.0, -0.707107, 0.707107]
    assert a.get_matrix() == pytest.approx(result)


def test_rotate_y():
    a = Mat3.rotate_y(25.0)
    result = [0.906308, 0.0, -0.422618, 0.0, 1.0, 0.0, 0.422618, 0.0, 0.906308]
    assert a.get_matrix() == pytest.approx(result)


def test_rotate_z():
    a = Mat3.rotate_z(-36.0)
    result = [0.809017, -0.587785, 0.0, 0.587785, 0.809017, 0.0, 0.0, 0.0, 1.0]
    assert a.get_matrix() == pytest.approx(result)


def test_mult_mat3_mat3():
    t1 = Mat3.rotate_x(45.0)
    t2 = Mat3.rotate_y(35.0)
    test = t1 @ t2
    # fmt: off
    result = [0.8191, 0.4055, -0.405,0.0, 0.707, 0.707,0.5735, -0.5792, 0.5792]
    # fmt: on
    assert test.get_matrix() == pytest.approx(result, rel=1e-3, abs=1e-3)

    t1 = Mat3.from_list([1, 2, 3, 2, 3, 4, 4, 5, 6])
    test = t1 @ t1
    result = [17, 23, 29, 24, 33, 42, 38, 53, 68]
    assert test.get_matrix() == pytest.approx(result, rel=1e-3, abs=1e-3)


def test_mult_error():
    with pytest.raises(Mat3Error):
        a = Mat3()
        _ = a @ 2
        a * "a"


def test_mat3_times_mat3():
    for a, b, result in zip(mat3Data.a, mat3Data.b, mat3Data.a_times_b):
        m1 = Mat3.from_list(a)
        m2 = Mat3.from_list(b)
        value = m1 @ m2
        assert value.get_matrix() == pytest.approx(result)


def test_mult_mat3_equal():
    for a, b, result in zip(mat3Data.a, mat3Data.b, mat3Data.a_times_b):
        m1 = Mat3.from_list(a)
        m2 = Mat3.from_list(b)
        m1 @= m2
        assert m1.get_matrix() == pytest.approx(result)


def test_mat3_mult_vec3():
    t1 = Mat3()
    v1 = Vec3(1.0, 2.0, 3.0)
    t1 = Mat3.rotate_x(45.0)
    result = t1 @ v1
    assert result.x == pytest.approx(1.0)
    assert result.y == pytest.approx(3.535534)
    assert result.z == pytest.approx(0.707107)


def test_add():
    a = Mat3.from_list([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    b = Mat3.from_list([[2, 2, 2], [3, 3, 3], [4, 4, 4]])
    c = a + b
    result = c.get_matrix()
    value = [3, 4, 5, 7, 8, 9, 11, 12, 13]
    assert result == pytest.approx(value)


def test_mat3_plus_mat3():
    for a, b, result in zip(mat3Data.a, mat3Data.b, mat3Data.a_plus_b):
        m1 = Mat3.from_list(a)
        m2 = Mat3.from_list(b)
        values = m1 + m2
        assert values.get_matrix() == pytest.approx(result)


def test_mat3_plus_equal():
    for a, b, result in zip(mat3Data.a, mat3Data.b, mat3Data.a_plus_b):
        m1 = Mat3.from_list(a)
        m2 = Mat3.from_list(b)
        m1 += m2
        assert m1.get_matrix() == pytest.approx(result)


def test_mat3_mult_float():
    a = Mat3.from_list([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    b = a * 2
    result = [2, 4, 6, 8, 10, 12, 14, 16, 18]
    assert b.get_matrix() == pytest.approx(result)
    with pytest.raises(Mat3Error):
        a = a * "hello"


def test_mat3_minus_mat3():
    for a, b, result in zip(mat3Data.a, mat3Data.b, mat3Data.a_minus_b):
        m1 = Mat3.from_list(a)
        m2 = Mat3.from_list(b)
        values = m1 - m2
        assert values.get_matrix() == pytest.approx(result)


def test_mat3_minus_equal():
    for a, b, result in zip(mat3Data.a, mat3Data.b, mat3Data.a_minus_b):
        m1 = Mat3.from_list(a)
        m2 = Mat3.from_list(b)
        m1 -= m2
        assert m1.get_matrix() == pytest.approx(result)


def test_det():
    for a, result in zip(mat3Data.a, mat3Data.a_det):
        m1 = Mat3.from_list(a)
        value = m1.determinant()
        assert value == pytest.approx(result[0])


def test_inverse():
    for a, result in zip(mat3Data.a, mat3Data.a_inv):
        m1 = Mat3.from_list(a)
        value = m1.inverse()
        assert value.get_matrix() == pytest.approx(result)
    with pytest.raises(Mat3Error):
        m = Mat3.zero()
        m.inverse()


def test_subscript():
    a = Mat3.from_list([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    assert a[0][0] == 1
    assert a[0][1] == 2
    assert a[0][2] == 3
    assert a[1][0] == 4
    assert a[1][1] == 5
    assert a[1][2] == 6
    assert a[2][0] == 7
    assert a[2][1] == 8
    assert a[2][2] == 9


def test_subscript_set():
    a = Mat3.identity()
    a[0] = [1, 1, 1]
    a[1] = [2, 2, 2]
    a[2] = [3, 3, 3]

    assert a[0] == [1, 1, 1]
    assert a[1] == [2, 2, 2]
    assert a[2] == [3, 3, 3]


def test_strings():
    a = Mat3.identity()
    assert str(a) == "[[1.0, 0.0, 0.0]\n[0.0, 1.0, 0.0]\n[0.0, 0.0, 1.0]]"
    assert repr(a) == "Mat3([[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]])"


def test_from_mat4():
    m4 = Mat4.identity()
    m3 = Mat3.from_mat4(m4)
    assert m3.get_matrix() == pytest.approx(
        [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
    )
