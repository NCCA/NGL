import math

import numpy as np

from .vec2 import Vec2


class Mat2:
    def __init__(self, *args):
        if not args:
            self.m = np.identity(2, dtype=np.float32)
        elif len(args) == 1:
            if isinstance(args[0], Mat2):  # Copy constructor
                self.m = np.copy(args[0].m)
            else:  # From a single value
                self.m = np.zeros((2, 2), dtype=np.float32)
                self.m[0, 0] = args[0]
                self.m[1, 1] = args[0]
        elif len(args) == 4:
            self.m = np.array([args[0], args[1], args[2], args[3]], dtype=np.float32).reshape(2, 2)

    def to_list(self):
        return self.m.flatten().tolist()

    def __eq__(self, other):
        return np.allclose(self.m, other.m)

    def null(self):
        self.m.fill(0)

    def identity(self):
        self.m = np.identity(2, dtype=np.float32)

    def transpose(self):
        self.m = self.m.transpose()
        return self

    @staticmethod
    def scale(x, y):
        mat = Mat2(0)
        mat.m[0, 0] = x
        mat.m[1, 1] = y
        return mat

    @staticmethod
    def rotate(deg):
        mat = Mat2()
        rad = math.radians(deg)
        sr = math.sin(rad)
        cr = math.cos(rad)
        mat.m[0, 0] = cr
        mat.m[0, 1] = -sr
        mat.m[1, 0] = sr
        mat.m[1, 1] = cr
        return mat

    def __mul__(self, other):
        if isinstance(other, Mat2):
            result = Mat2()
            result.m = self.m @ other.m
            return result
        elif isinstance(other, (int, float)):
            result = Mat2(self)
            result.m = self.m * other
            return result
        elif isinstance(other, Vec2):
            result = Vec2()
            result.v = self.m @ other.v
            return result
        else:
            return NotImplemented

    def __imul__(self, other):
        if isinstance(other, Mat2):
            self.m = self.m @ other.m
            return self
        elif isinstance(other, (int, float)):
            self.m *= other
            return self
        else:
            return NotImplemented

    def __add__(self, other):
        if isinstance(other, Mat2):
            result = Mat2(self)
            result.m = self.m + other.m
            return result
        else:
            return NotImplemented

    def __iadd__(self, other):
        if isinstance(other, Mat2):
            self.m += other.m
            return self
        else:
            return NotImplemented

    def __str__(self):
        return str(self.m)

    def sizeof(self):
        return self.m.nbytes
