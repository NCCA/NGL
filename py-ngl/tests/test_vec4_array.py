import numpy as np
import pytest

from ngl import Vec4, Vec4Array


def test_init():
    """Test the constructor of Vec4Array"""
    a = Vec4Array()
    assert len(a) == 0
    v = [Vec4(1, 2, 3, 4), Vec4(5, 6, 7, 8)]
    a = Vec4Array(v)
    assert len(a) == 2
    assert a[0] == Vec4(1, 2, 3, 4)
    assert a[1] == Vec4(5, 6, 7, 8)
    with pytest.raises(TypeError):
        Vec4Array([1, 2, 3, 4])


def test_append():
    """Test the append method"""
    a = Vec4Array()
    v = Vec4(1, 2, 3, 4)
    a.append(v)
    assert len(a) == 1
    assert a[0] == v
    with pytest.raises(TypeError):
        a.append("not a vec4")


def test_extend():
    """Test the extend method"""
    a = Vec4Array()
    v = [Vec4(1, 2, 3, 4), Vec4(5, 6, 7, 8)]
    a.extend(v)
    assert len(a) == 2
    assert a[0] == Vec4(1, 2, 3, 4)
    assert a[1] == Vec4(5, 6, 7, 8)
    with pytest.raises(TypeError):
        a.extend(["not a vec4"])


def test_getitem():
    """Test the __getitem__ method"""
    v = [Vec4(1, 2, 3, 4), Vec4(5, 6, 7, 8)]
    a = Vec4Array(v)
    assert a[0] == Vec4(1, 2, 3, 4)
    assert a[1] == Vec4(5, 6, 7, 8)
    with pytest.raises(IndexError):
        _ = a[2]


def test_len():
    """Test the __len__ method"""
    a = Vec4Array()
    assert len(a) == 0
    a.append(Vec4())
    assert len(a) == 1


def test_iter():
    """Test the __iter__ method"""
    v = [Vec4(1, 2, 3, 4), Vec4(5, 6, 7, 8)]
    a = Vec4Array(v)
    for i, vec in enumerate(a):
        assert vec == v[i]


def test_to_list():
    """Test the to_list method"""
    v = [Vec4(1, 2, 3, 4), Vec4(5, 6, 7, 8)]
    a = Vec4Array(v)
    assert a.to_list() == [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0]
    a = Vec4Array()
    assert a.to_list() == []


def test_to_numpy():
    """Test the to_numpy method"""
    v = [Vec4(1, 2, 3, 4), Vec4(5, 6, 7, 8)]
    a = Vec4Array(v)
    n = a.to_numpy()
    assert isinstance(n, np.ndarray)
    assert n.dtype == np.float32
    assert n.shape == (8,)
    np.testing.assert_array_almost_equal(n, [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0])
    a = Vec4Array()
    n = a.to_numpy()
    assert n.shape == (0,)


def test_repr():
    a = Vec4Array([Vec4(1, 2, 3, 4)])
    assert repr(a) == "Vec4Array([Vec4 [1,2,3,4]])"


def test_str():
    a = Vec4Array([Vec4(1, 2, 3, 4)])
    assert str(a) == "[Vec4 [1,2,3,4]]"
