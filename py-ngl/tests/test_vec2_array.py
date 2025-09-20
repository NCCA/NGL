import numpy as np
import pytest

from ngl import Vec2, Vec2Array


def test_init():
    """Test the constructor of Vec2Array"""
    a = Vec2Array()
    assert len(a) == 0
    v = [Vec2(1, 2), Vec2(4, 5)]
    a = Vec2Array(v)
    assert len(a) == 2
    assert a[0] == Vec2(1, 2)
    assert a[1] == Vec2(4, 5)
    with pytest.raises(TypeError):
        Vec2Array([1, 2])


def test_append():
    """Test the append method"""
    a = Vec2Array()
    v = Vec2(1, 2)
    a.append(v)
    assert len(a) == 1
    assert a[0] == v
    with pytest.raises(TypeError):
        a.append("not a vec2")


def test_extend():
    """Test the extend method"""
    a = Vec2Array()
    v = [Vec2(1, 2), Vec2(4, 5)]
    a.extend(v)
    assert len(a) == 2
    assert a[0] == Vec2(1, 2)
    assert a[1] == Vec2(4, 5)
    with pytest.raises(TypeError):
        a.extend(["not a vec2"])


def test_getitem():
    """Test the __getitem__ method"""
    v = [Vec2(1, 2), Vec2(4, 5)]
    a = Vec2Array(v)
    assert a[0] == Vec2(1, 2)
    assert a[1] == Vec2(4, 5)
    with pytest.raises(IndexError):
        _ = a[2]


def test_len():
    """Test the __len__ method"""
    a = Vec2Array()
    assert len(a) == 0
    a.append(Vec2())
    assert len(a) == 1


def test_iter():
    """Test the __iter__ method"""
    v = [Vec2(1, 2), Vec2(4, 5)]
    a = Vec2Array(v)
    for i, vec in enumerate(a):
        assert vec == v[i]


def test_to_list():
    """Test the to_list method"""
    v = [Vec2(1, 2), Vec2(4, 5)]
    a = Vec2Array(v)
    assert a.to_list() == [1.0, 2.0, 4.0, 5.0]
    a = Vec2Array()
    assert a.to_list() == []


def test_to_numpy():
    """Test the to_numpy method"""
    v = [Vec2(1, 2), Vec2(4, 5)]
    a = Vec2Array(v)
    n = a.to_numpy()
    assert isinstance(n, np.ndarray)
    assert n.dtype == np.float32
    assert n.shape == (4,)
    np.testing.assert_array_almost_equal(n, [1.0, 2.0, 4.0, 5.0])
    a = Vec2Array()
    n = a.to_numpy()
    assert n.shape == (0,)


def test_repr():
    a = Vec2Array([Vec2(1, 2)])
    assert repr(a) == "Vec2Array([Vec2 [1,2]])"


def test_str():
    a = Vec2Array([Vec2(1, 2)])
    assert str(a) == "[Vec2 [1,2]]"
