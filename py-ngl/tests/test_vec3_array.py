import numpy as np
import pytest

from ngl import Vec3, Vec3Array


def test_init():
    """Test the constructor of Vec3Array"""
    a = Vec3Array()
    assert len(a) == 0
    v = [Vec3(1, 2, 3), Vec3(4, 5, 6)]
    a = Vec3Array(v)
    assert len(a) == 2
    assert a[0] == Vec3(1, 2, 3)
    assert a[1] == Vec3(4, 5, 6)
    with pytest.raises(TypeError):
        Vec3Array([1, 2, 3])


def test_append():
    """Test the append method"""
    a = Vec3Array()
    v = Vec3(1, 2, 3)
    a.append(v)
    assert len(a) == 1
    assert a[0] == v
    with pytest.raises(TypeError):
        a.append("not a vec3")


def test_getitem():
    """Test the __getitem__ method"""
    v = [Vec3(1, 2, 3), Vec3(4, 5, 6)]
    a = Vec3Array(v)
    assert a[0] == Vec3(1, 2, 3)
    assert a[1] == Vec3(4, 5, 6)
    with pytest.raises(IndexError):
        _ = a[2]


def test_len():
    """Test the __len__ method"""
    a = Vec3Array()
    assert len(a) == 0
    a.append(Vec3())
    assert len(a) == 1


def test_iter():
    """Test the __iter__ method"""
    v = [Vec3(1, 2, 3), Vec3(4, 5, 6)]
    a = Vec3Array(v)
    for i, vec in enumerate(a):
        assert vec == v[i]


def test_to_list():
    """Test the to_list method"""
    v = [Vec3(1, 2, 3), Vec3(4, 5, 6)]
    a = Vec3Array(v)
    assert a.to_list() == [1.0, 2.0, 3.0, 4.0, 5.0, 6.0]
    a = Vec3Array()
    assert a.to_list() == []


def test_to_numpy():
    """Test the to_numpy method"""
    v = [Vec3(1, 2, 3), Vec3(4, 5, 6)]
    a = Vec3Array(v)
    n = a.to_numpy()
    assert isinstance(n, np.ndarray)
    assert n.dtype == np.float32
    assert n.shape == (6,)
    np.testing.assert_array_almost_equal(n, [1.0, 2.0, 3.0, 4.0, 5.0, 6.0])
    a = Vec3Array()
    n = a.to_numpy()
    assert n.shape == (0,)


def test_extend():
    """Test the extend method"""
    a = Vec3Array()
    v = [Vec3(1, 2, 3), Vec3(4, 5, 6)]
    a.extend(v)
    assert len(a) == 2
    assert a[0] == Vec3(1, 2, 3)
    assert a[1] == Vec3(4, 5, 6)
    with pytest.raises(TypeError):
        a.extend(["not a vec3"])


def test_repr():
    a = Vec3Array([Vec3(1, 2, 3)])
    assert repr(a) == "Vec3Array([Vec3 [1,2,3]])"


def test_str():
    a = Vec3Array([Vec3(1, 2, 3)])
    assert str(a) == "[Vec3 [1,2,3]]"
