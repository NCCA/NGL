import pytest
import numpy as np

from ngl.mat2 import Mat2
from ngl.vec2 import Vec2


def test_default_identity():
    m = Mat2()
    assert m.m == [[1.0, 0.0], [0.0, 1.0]]


def test_custom_init():
    mat = [[2.0, 3.0], [4.0, 5.0]]
    m = Mat2(mat)
    assert m.m == mat


def test_get_matrix():
    m = Mat2([[1.0, 2.0], [3.0, 4.0]])
    assert m.get_matrix() == [1.0, 2.0, 3.0, 4.0]


def test_get_numpy():
    m = Mat2([[1.0, 2.0], [3.0, 4.0]])
    arr = m.get_numpy()
    assert isinstance(arr, np.ndarray)
    assert arr.shape == (2, 2)
    np.testing.assert_array_equal(arr, np.array([[1.0, 2.0], [3.0, 4.0]]))


def test_identity_classmethod():
    m = Mat2.identity()
    assert m.m == [[1.0, 0.0], [0.0, 1.0]]


def test_matrix_multiplication():
    a = Mat2([[1, 2], [3, 4]])
    b = Mat2([[2, 0], [1, 2]])
    result = a @ b
    assert isinstance(result, Mat2)
    assert result.m == [[1 * 2 + 2 * 1, 1 * 0 + 2 * 2], [3 * 2 + 4 * 1, 3 * 0 + 4 * 2]]


def test_vector_transformation():
    m = Mat2([[1, 2], [3, 4]])
    v = Vec2(5, 6)
    result = m @ v
    assert isinstance(result, Vec2)
    assert result.x == 5 * 1 + 6 * 2
    assert result.y == 5 * 3 + 6 * 4


def test_str_representation():
    m = Mat2([[7, 8], [9, 10]])
    s = str(m)
    assert s == "Mat2([7, 8], [9, 10])"


def test_invalid_matmul_type():
    m = Mat2()
    with pytest.raises(ValueError):
        _ = m @ 42  # Not Mat2 or Vec2


def test_internal_mat_mul():
    a = Mat2([[1, 2], [3, 4]])
    b = Mat2([[2, 0], [1, 2]])
    result = a._mat_mul(b)
    assert isinstance(result, Mat2)
    assert result.m == [[1 * 2 + 2 * 1, 1 * 0 + 2 * 2], [3 * 2 + 4 * 1, 3 * 0 + 4 * 2]]
