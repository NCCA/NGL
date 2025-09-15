import numpy as np


class Vec3:
    def __init__(self, x=0.0, y=0.0, z=0.0):
        self.v = np.array([x, y, z], dtype=np.float32)

    @property
    def x(self):
        return self.v[0]

    @x.setter
    def x(self, value):
        self.v[0] = value

    @property
    def y(self):
        return self.v[1]

    @y.setter
    def y(self, value):
        self.v[1] = value

    @property
    def z(self):
        return self.v[2]

    @z.setter
    def z(self, value):
        self.v[2] = value

    def set(self, x, y, z):
        self.v[0] = x
        self.v[1] = y
        self.v[2] = z

    def __eq__(self, other):
        return np.allclose(self.v, other.v)

    def __str__(self):
        return f"({self.x}, {self.y}, {self.z})"

    def __getitem__(self, item):
        return self.v[item]

    def __setitem__(self, key, value):
        self.v[key] = value

    def dot(self, other):
        return np.dot(self.v, other.v)

    def null(self):
        self.v.fill(0)

    def normalize(self):
        norm = np.linalg.norm(self.v)
        if norm == 0:
            self.v.fill(np.nan)
            return
        self.v = self.v / norm

    def inner(self, other):
        return np.inner(self.v, other.v)

    def length(self):
        return np.linalg.norm(self.v)

    def length_squared(self):
        return self.dot(self)

    def cross(self, other):
        return Vec3(*np.cross(self.v, other.v))

    def __add__(self, other):
        return Vec3(*(self.v + other.v))

    def __iadd__(self, other):
        self.v += other.v
        return self

    def __sub__(self, other):
        return Vec3(*(self.v - other.v))

    def __isub__(self, other):
        self.v -= other.v
        return self

    def __mul__(self, other):
        from .mat3 import Mat3

        if isinstance(other, (int, float)):
            return Vec3(*(self.v * other))
        if isinstance(other, Mat3):
            return Vec3(*(self.v @ other.m))
        return Vec3(*(self.v * other.v))

    def __rmul__(self, other):
        if isinstance(other, (int, float)):
            return Vec3(*(self.v * other))
        return NotImplemented

    def __imul__(self, other):
        if isinstance(other, (int, float)):
            self.v *= other
        else:
            self.v *= other.v
        return self

    def __truediv__(self, other):
        if isinstance(other, (int, float)):
            return Vec3(*(self.v / other))
        return Vec3(*(self.v / other.v))

    def __itruediv__(self, other):
        if isinstance(other, (int, float)):
            self.v /= other
        else:
            self.v /= other.v
        return self

    def __neg__(self):
        return Vec3(*(-self.v))

    def reflect(self, normal):
        return self - 2 * self.dot(normal) * normal

    def clamp(self, min_val, max_val=None):
        if max_val is None:
            max_val = min_val
            min_val = -min_val
        self.v = np.clip(self.v, min_val, max_val)

    @staticmethod
    def up():
        return Vec3(0, 1, 0)

    @staticmethod
    def down():
        return Vec3(0, -1, 0)

    @staticmethod
    def left():
        return Vec3(-1, 0, 0)

    @staticmethod
    def right():
        return Vec3(1, 0, 0)

    @staticmethod
    def in_():
        return Vec3(0, 0, 1)

    @staticmethod
    def out():
        return Vec3(0, 0, -1)

    @staticmethod
    def zero():
        return Vec3(0, 0, 0)
