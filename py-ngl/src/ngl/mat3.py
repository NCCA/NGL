import math

import numpy as np

from .mat4 import Mat4
from .vec3 import Vec3


class Mat3:
    def __init__(self, *args):
        if not args:
            self.m = np.identity(3, dtype=np.float32)
        elif len(args) == 1:
            if isinstance(args[0], Mat3):
                self.m = np.copy(args[0].m)
            elif isinstance(args[0], Mat4):
                self.m = args[0].m[:3, :3]
            else:
                self.m = np.identity(3, dtype=np.float32) * args[0]
        elif len(args) == 9:
            self.m = np.array(args, dtype=np.float32).reshape(3, 3)

    def to_list(self):
        return self.m.flatten().tolist()

    def __eq__(self, other):
        return np.allclose(self.m, other.m)

    def null(self):
        self.m.fill(0)

    def identity(self):
        self.m = np.identity(3, dtype=np.float32)

    def transpose(self):
        self.m = self.m.transpose()
        return self

    def inverse(self):
        self.m = np.linalg.inv(self.m)
        return self

    def determinant(self):
        return np.linalg.det(self.m)

    @staticmethod
    def scale(x, y, z):
        mat = Mat3()
        mat.m[0, 0] = x
        mat.m[1, 1] = y
        mat.m[2, 2] = z
        return mat

    @staticmethod
    def rotateX(deg):
        mat = Mat3()
        rad = math.radians(deg)
        sr = math.sin(rad)
        cr = math.cos(rad)
        mat.m[1, 1] = cr
        mat.m[1, 2] = sr
        mat.m[2, 1] = -sr
        mat.m[2, 2] = cr
        return mat

    @staticmethod
    def rotateY(deg):
        mat = Mat3()
        rad = math.radians(deg)
        sr = math.sin(rad)
        cr = math.cos(rad)
        mat.m[0, 0] = cr
        mat.m[0, 2] = -sr
        mat.m[2, 0] = sr
        mat.m[2, 2] = cr
        return mat

    @staticmethod
    def rotateZ(deg):
        mat = Mat3()
        rad = math.radians(deg)
        sr = math.sin(rad)
        cr = math.cos(rad)
        mat.m[0, 0] = cr
        mat.m[0, 1] = sr
        mat.m[1, 0] = -sr
        mat.m[1, 1] = cr
        return mat

    def __mul__(self, other):
        if isinstance(other, Mat3):
            result = Mat3()
            result.m = self.m @ other.m
            return result
        elif isinstance(other, (int, float)):
            result = Mat3(self)
            result.m = self.m * other
            return result
        elif isinstance(other, Vec3):
            result = Vec3()
            result.v = self.m @ other.v
            return result
        else:
            return NotImplemented

    def __imul__(self, other):
        if isinstance(other, Mat3):
            self.m = self.m @ other.m
            return self
        elif isinstance(other, (int, float)):
            self.m *= other
            return self
        else:
            return NotImplemented

    def __add__(self, other):
        if isinstance(other, Mat3):
            result = Mat3(self)
            result.m = self.m + other.m
            return result
        else:
            return NotImplemented

    def __iadd__(self, other):
        if isinstance(other, Mat3):
            self.m += other.m
            return self
        else:
            return NotImplemented

    def __rmul__(self, other):
        from .vec3 import Vec3

        if isinstance(other, Vec3):
            result = Vec3()
            result.v = other.v @ self.m
            return result
        else:
            return NotImplemented

    def __str__(self):
        return str(self.m)

    def sizeof(self):
        return self.m.nbytes
