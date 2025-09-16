import mat4Data  # noqa
import pytest

from ngl import Mat4, Mat4Error, Mat4NotSquare, Vec4


def test_ctor():
    m = Mat4()
    # fmt: off
    ident = [1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0]
    # fmt: on
    assert m.get_matrix() == pytest.approx(ident)


def test_identity():
    m = Mat4.identity()
    # fmt: off
    ident = [1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0]
    # fmt: on
    assert m.get_matrix() == pytest.approx(ident)


def test_zero():
    m = Mat4.zero()
    values = m.get_matrix()
    ident = [0.0] * 16
    assert values == pytest.approx(ident)


def test_get_numpy():
    m = Mat4.from_list([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]])
    n = m.get_numpy()
    value = 1
    for c in range(0, 4):
        for r in range(0, 4):
            assert n[c][r] == value
            value += 1


def test_from_list():
    m = Mat4.from_list([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]])
    result = [i for i in range(1, 17)]
    assert m.get_matrix() == pytest.approx(result)
    m = Mat4.from_list([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16])
    assert m.get_matrix() == pytest.approx(result)


def test_not_square():
    with pytest.raises(Mat4NotSquare):
        _ = Mat4.from_list([[1.0, 2.0, 3.0, 50], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]])
    with pytest.raises(Mat4NotSquare):
        _ = Mat4.from_list([[], [], [], []])


def test_transpose():
    m = Mat4.from_list([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]])
    m.transpose()
    values = m.get_matrix()
    result = [1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16]
    assert values == pytest.approx(result)


def test_get_transpose():
    m = Mat4.from_list([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]])
    b = m.get_transpose()
    values = b.get_matrix()
    result = [1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16]
    assert values == pytest.approx(result)


def test_scale():
    a = Mat4.scale(2.0, 3.0, 4.0)
    value = a.get_matrix()
    # fmt: off
    result = [2.0,0.0,0.0,0.0,0.0,3.0,0.0,0.0,0.0,0.0,4.0,0.0,0.0,0.0,0.0,1.0]
    # fmt: on
    assert value == pytest.approx(result)


def test_rotate_x():
    a = Mat4.rotate_x(45.0)
    value = a.get_matrix()
    # fmt: off
    result = [1.0,0.0,0.0,0.0,
                0.0,0.707107,0.707107,0.0,
                0.0,-0.707107,0.707107,0.0,
                0.0,0.0,0.0,1.0]

    # fmt: on
    assert value == pytest.approx(result)


def test_rotate_y():
    a = Mat4.rotate_y(25.0)
    value = a.get_matrix()
    # fmt: off
    result = [0.906308,0.0,-0.422618,0.0,
                0.0,1.0,0.0,0.0,
                0.422618,0.0,0.906308,0.0,
                0.0,0.0,0.0,1.0]

    #         # fmt: on
    assert value == pytest.approx(result)


def test_rotate_z():
    a = Mat4.rotate_z(-36.0)
    value = a.get_matrix()
    # fmt: off
    result = [0.809,-0.5877,0.0,0.0,
                0.5877, 0.809, 0.0, 0.0,
                0.0,0.0,1.0, 0.0,
                0.0, 0.0,0.0,1.0,]
    # fmt: on
    assert value == pytest.approx(result, abs=1e-3)


def test_mat4_times_mat4():
    for a, b, result in zip(mat4Data.a, mat4Data.b, mat4Data.a_times_b):
        m1 = Mat4.from_list(a)
        m2 = Mat4.from_list(b)
        value = m1 @ m2
        assert value.get_matrix() == pytest.approx(result)


def test_rotate_mat4_mat4():
    t1 = Mat4.rotate_x(45.0)
    t2 = Mat4.rotate_y(35.0)
    test = t1 @ t2
    # fmt: off
    result=[0.819152,0.405580,-0.405580,0.0,
            0.0,0.707107,0.707107,0.0,
            0.573577,-0.579228,0.579228,0.0,
            0.0,0.0,0.0,1.0]
    # fmt: on
    value = test.get_matrix()
    assert value == pytest.approx(result, abs=1e-3)
    test = t1 @ t2
    value = test.get_matrix()
    assert value == pytest.approx(result, abs=1e-3)


def test_mult_error():
    with pytest.raises(Mat4Error):
        a = Mat4()
        _ = a @ 2


def test_mult_mat4_equal():
    for a, b, result in zip(mat4Data.a, mat4Data.b, mat4Data.a_times_b):
        m1 = Mat4.from_list(a)
        m2 = Mat4.from_list(b)
        m1 @= m2
        assert m1.get_matrix() == pytest.approx(result)


def test_mat4_mult_vec4():
    test = Vec4(1.0, 2.0, 3.0, 1.0)
    t1 = Mat4.rotate_x(45.0)
    test = t1 @ test
    assert test.x == pytest.approx(1.0)
    assert test.y == pytest.approx(3.535534)
    assert test.z == pytest.approx(0.707107)
    assert test.w == pytest.approx(1.0)


def test_mat4_plus_mat4():
    for a, b, result in zip(mat4Data.a, mat4Data.b, mat4Data.a_plus_b):
        m1 = Mat4.from_list(a)
        m2 = Mat4.from_list(b)
        values = m1 + m2
        assert values.get_matrix() == pytest.approx(result)


def test_mat4_plus_equal():
    for a, b, result in zip(mat4Data.a, mat4Data.b, mat4Data.a_plus_b):
        m1 = Mat4.from_list(a)
        m2 = Mat4.from_list(b)
        m1 += m2
        assert m1.get_matrix() == pytest.approx(result)


def test_mat4_minus_mat4():
    for a, b, result in zip(mat4Data.a, mat4Data.b, mat4Data.a_minus_b):
        m1 = Mat4.from_list(a)
        m2 = Mat4.from_list(b)
        values = m1 - m2
        assert values.get_matrix() == pytest.approx(result)


def test_mat4_minus_equal():
    for a, b, result in zip(mat4Data.a, mat4Data.b, mat4Data.a_minus_b):
        m1 = Mat4.from_list(a)
        m2 = Mat4.from_list(b)
        m1 -= m2
        assert m1.get_matrix() == pytest.approx(result)


def test_det():
    for a, result in zip(mat4Data.a, mat4Data.a_det):
        m1 = Mat4.from_list(a)
        value = m1.determinant()
        assert value == pytest.approx(result[0])


def test_inverse():
    for a, result in zip(mat4Data.a, mat4Data.a_inv):
        m1 = Mat4.from_list(a)
        value = m1.inverse()
        assert value.get_matrix() == pytest.approx(result)
    with pytest.raises(Mat4Error):
        m1 = Mat4.zero()
        m1.inverse()


def test_subscript():
    a = Mat4.from_list([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]])
    assert a[0] == [1, 2, 3, 4]
    assert a[1] == [5, 6, 7, 8]
    assert a[2] == [9, 10, 11, 12]
    assert a[3] == [13, 14, 15, 16]


def test_subscript_set():
    a = Mat4()
    a[0] = [1, 2, 3, 4]
    a[1] = [5, 6, 7, 8]
    a[2] = [9, 10, 11, 12]
    a[3] = [13, 14, 15, 16]
    assert a.get_matrix() == pytest.approx(
        [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
    )


def test_mult():
    a = Mat4.from_list([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]])
    b = a * 2
    result = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32]
    assert b.get_matrix() == pytest.approx(result)
    with pytest.raises(Mat4Error):
        a = a * "hello"


def test_strings():
    a = Mat4.identity()
    assert (
        str(a)
        == "[[1.0, 0.0, 0.0, 0.0]\n[0.0, 1.0, 0.0, 0.0]\n[0.0, 0.0, 1.0, 0.0]\n[0.0, 0.0, 0.0, 1.0]]"
    )
    assert (
        repr(a)
        == "Mat4([[1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0, 0.0], [0.0, 0.0, 1.0, 0.0], [0.0, 0.0, 0.0, 1.0]])"
    )


def test_ngl():
    t1 = Mat4.rotate_x(45.0)
    t2 = Mat4.rotate_y(35.0)
    test = t2 @ t1
    result = Mat4.from_list(
        [
            0.819152,
            0,
            -0.573577,
            0,
            0.40558,
            0.707107,
            0.579228,
            0,
            0.40558,
            -0.707107,
            0.579228,
            0,
            0,
            0,
            0,
            1,
        ]
    )
    assert test.to_list() == pytest.approx(result.to_list(), abs=1e-3)
