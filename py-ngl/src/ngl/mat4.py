"""
Simple Mat4 class which can be used with the Vec4 class
"""

import copy
import functools
import math
import operator

import numpy as np


class Mat4Error(Exception):
    """An exception class for Mat3"""

    pass


class Mat4NotSquare(Exception):
    """Make sure we have 3x3"""

    pass


_identity = [
    [1.0, 0.0, 0.0, 0.0],
    [0.0, 1.0, 0.0, 0.0],
    [0.0, 0.0, 1.0, 0.0],
    [0.0, 0.0, 0.0, 1.0],
]


class Mat4:
    __slots__ = ["m"]

    def __init__(self):
        "construct to identity matrix"
        self.m = copy.deepcopy(_identity)

    def get_matrix(self):
        "return matrix elements as list ideal for OpenGL etc"
        return functools.reduce(operator.concat, self.m)

    def get_numpy(self):
        "return matrix as a numpy array ideal for WebGPU etc"
        return np.array(self.get_matrix(), dtype=np.float32).reshape([4, 4])

    @classmethod
    def identity(cls):
        "class method to return a new identity matrix"
        v = Mat4()
        return v

    @classmethod
    def zero(cls):
        "class method to return a zero matrix"
        v = Mat4()
        v.m = [
            [0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0],
        ]
        return v

    @classmethod
    def from_list(cls, lst):
        "class method to create mat4 from list"
        v = Mat4()
        v.m = lst
        if not v._is_square():
            if len(lst) == 16:  # can convert
                v.m = [lst[0:4], lst[4:8], lst[8:12], lst[12:16]]
                return v
            else:
                raise Mat4NotSquare
        else:
            return v

    def _is_square(self) -> bool:
        "ensure matrix is square"
        return len(self.m) == 4 and all(len(i) == 4 for i in self.m)

    def to_list(self):
        "convert matrix to list"
        # flatten to single array
        return functools.reduce(operator.concat, self.m)

    def transpose(self):
        "transpose this matrix"
        self.m = [list(item) for item in zip(*self.m)]

    def get_transpose(self):
        "return a new matrix as the transpose of ourself"
        m = Mat4()
        m.m = [list(item) for item in zip(*self.m)]
        return m

    @classmethod
    def scale(cls, x: float, y: float, z: float):
        "return a new matrix as scale"
        a = Mat4()  # identity by default
        a.m[0][0] = x
        a.m[1][1] = y
        a.m[2][2] = z
        return a

    @classmethod
    def rotate_x(cls, angle):
        "return a rotation around the X axis by angle degrees"
        a = Mat4()
        beta = math.radians(angle)
        sr = math.sin(beta)
        cr = math.cos(beta)
        a.m[1][1] = cr
        a.m[1][2] = sr
        a.m[2][1] = -sr
        a.m[2][2] = cr
        return a

    @classmethod
    def rotate_y(cls, angle):
        "return a rotation around the Y axis by angle degrees"
        a = Mat4()
        beta = math.radians(angle)
        sr = math.sin(beta)
        cr = math.cos(beta)
        a.m[0][0] = cr
        a.m[0][2] = -sr
        a.m[2][0] = sr
        a.m[2][2] = cr
        return a

    @classmethod
    def rotate_z(cls, angle):
        "return a rotation around the Z axis by angle degrees"
        a = Mat4()
        beta = math.radians(angle)
        sr = math.sin(beta)
        cr = math.cos(beta)
        a.m[0][0] = cr
        a.m[0][1] = sr
        a.m[1][0] = -sr
        a.m[1][1] = cr
        return a

    def __getitem__(self, idx):
        "access array elements remember this is a list of lists [[4],[4],[4],[4]]"
        return self.m[idx]

    def __setitem__(self, idx, item):
        "set items remember this is a list of lists [[4],[4],[4],[4]]"
        self.m[idx] = item

    def __mul__(self, rhs):
        """Multiply matrix by scalar

        Parameters
        __________
            rhs : float int
                multiply each matrix element by rhs

        raises : Mat3Error
            if rhs is not a number
        """
        if isinstance(rhs, (int, float)):
            for i in range(0, len(self.m)):
                for j in range(0, len(self.m[i])):
                    self.m[i][j] *= rhs
            return self
        raise Mat4Error

    def _mat_mul(self, rhs):
        "matrix mult internal function"
        # fmt: off
        a00 = self.m[0][0] # cache values for speed? (works in C++ not sure about python)
        a01 = self.m[0][1]
        a02 = self.m[0][2]
        a03 = self.m[0][3]
        a10 = self.m[1][0]
        a11 = self.m[1][1]
        a12 = self.m[1][2]
        a13 = self.m[1][3]
        a20 = self.m[2][0]
        a21 = self.m[2][1]
        a22 = self.m[2][2]
        a23 = self.m[2][3]
        a30 = self.m[3][0]
        a31 = self.m[3][1]
        a32 = self.m[3][2]
        a33 = self.m[3][3]
        b00 = rhs.m[0][0]
        b01 = rhs.m[0][1]
        b02 = rhs.m[0][2]
        b03 = rhs.m[0][3]
        b10 = rhs.m[1][0]
        b11 = rhs.m[1][1]
        b12 = rhs.m[1][2]
        b13 = rhs.m[1][3]
        b20 = rhs.m[2][0]
        b21 = rhs.m[2][1]
        b22 = rhs.m[2][2]
        b23 = rhs.m[2][3]
        b30 = rhs.m[3][0]
        b31 = rhs.m[3][1]
        b32 = rhs.m[3][2]
        b33 = rhs.m[3][3]
        ret=Mat4() # result mat4
        ret.m[0][0] = b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30
        ret.m[0][1] = b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31
        ret.m[0][2] = b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32
        ret.m[0][3] = b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33
        ret.m[1][0] = b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30
        ret.m[1][1] = b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31
        ret.m[1][2] = b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32
        ret.m[1][3] = b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33
        ret.m[2][0] = b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30
        ret.m[2][1] = b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31
        ret.m[2][2] = b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32
        ret.m[2][3] = b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33
        ret.m[3][0] = b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30
        ret.m[3][1] = b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31
        ret.m[3][2] = b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32
        ret.m[3][3] = b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33
        return ret
        # fmt: on

    def __matmul__(self, rhs):
        from .vec4 import Vec4  # note relative import here

        "multiply matrix by another matrix"
        if isinstance(rhs, Mat4):
            return self._mat_mul(rhs)
        elif isinstance(rhs, (Vec4, Vec4)):
            # fmt: off
            return Vec4(
                rhs.x * self.m[0][0] + rhs.y * self.m[0][1]+ rhs.z * self.m[0][2]+ rhs.w * self.m[0][3],
                rhs.x * self.m[1][0]+ rhs.y * self.m[1][1]+ rhs.z * self.m[1][2]+ rhs.w * self.m[1][3],
                rhs.x * self.m[2][0]+ rhs.y * self.m[2][1]+ rhs.z * self.m[2][2]+ rhs.w * self.m[2][3],
                rhs.x * self.m[3][0]+ rhs.y * self.m[3][1]+ rhs.z * self.m[3][2]+ rhs.w * self.m[3][3])
            # fmt: on
        else:
            raise Mat4Error

    def __str__(self):
        return f"[{self.m[0]}\n{self.m[1]}\n{self.m[2]}\n{self.m[3]}]"

    def _addfunc(self, rhs):
        "internal add function"
        temp = Mat4()
        for i in range(0, len(temp.m)):
            temp.m[i] = [a + b for a, b in zip(self.m[i], rhs.m[i])]
        return temp

    def __add__(self, rhs):
        "piecewise addition of elements"
        return self._addfunc(rhs)

    def __iadd__(self, rhs):
        "piecewise addition of elements to this"
        return self._addfunc(rhs)

    def _sub(self, rhs):
        "internal sub function"
        temp = Mat4()
        for i in range(0, len(temp.m)):
            temp.m[i] = [a - b for a, b in zip(self.m[i], rhs.m[i])]
        return temp

    def __sub__(self, rhs):
        "piecewise subtraction of elements"
        return self._sub(rhs)

    def __isub__(self, rhs):
        "piecewise subtraction of elements to this"
        return self._sub(rhs)

    def determinant(self):
        "determinant of matrix"
        # Our matrices are 4.4 only, so we can just write the full formula instead of a complex algorithm.
        return (
            self.m[0][0] * self.m[1][1] * self.m[2][2] * self.m[3][3]
            - self.m[0][0] * self.m[1][1] * self.m[2][3] * self.m[3][2]
            + self.m[0][0] * self.m[1][2] * self.m[2][3] * self.m[3][1]
            - self.m[0][0] * self.m[1][2] * self.m[2][1] * self.m[3][3]
            + self.m[0][0] * self.m[1][3] * self.m[2][1] * self.m[3][2]
            - self.m[0][0] * self.m[1][3] * self.m[2][2] * self.m[3][1]
            - self.m[1][0] * self.m[2][1] * self.m[3][2] * self.m[0][3]
            + self.m[1][0] * self.m[2][1] * self.m[0][2] * self.m[3][3]
            - self.m[1][0] * self.m[3][1] * self.m[0][2] * self.m[2][3]
            + self.m[1][0] * self.m[3][1] * self.m[2][2] * self.m[0][3]
            - self.m[1][0] * self.m[0][1] * self.m[2][2] * self.m[3][3]
            + self.m[1][0] * self.m[0][1] * self.m[3][2] * self.m[2][3]
            + self.m[2][0] * self.m[3][1] * self.m[0][2] * self.m[1][3]
            - self.m[2][0] * self.m[3][1] * self.m[1][2] * self.m[0][3]
            + self.m[2][0] * self.m[0][1] * self.m[1][2] * self.m[3][3]
            - self.m[2][0] * self.m[0][1] * self.m[3][2] * self.m[1][3]
            + self.m[2][0] * self.m[1][1] * self.m[3][2] * self.m[0][3]
            - self.m[2][0] * self.m[1][1] * self.m[0][2] * self.m[3][3]
            - self.m[3][0] * self.m[0][1] * self.m[1][2] * self.m[2][3]
            + self.m[3][0] * self.m[0][1] * self.m[2][2] * self.m[1][3]
            - self.m[3][0] * self.m[1][1] * self.m[2][2] * self.m[0][3]
            + self.m[3][0] * self.m[1][1] * self.m[0][2] * self.m[2][3]
            - self.m[3][0] * self.m[2][1] * self.m[0][2] * self.m[1][3]
            + self.m[3][0] * self.m[2][1] * self.m[1][2] * self.m[0][3]
        )

    def inverse(self):
        "Inverse of matrix raise MatrixError if not calculable"
        try:
            det = self.determinant()
            tmp = Mat4()
            invdet = 1.0 / det
            tmp.m[0][0] = (
                self.m[1][1] * self.m[2][2] * self.m[3][3]
                + self.m[1][2] * self.m[2][3] * self.m[3][1]
                + self.m[1][3] * self.m[2][1] * self.m[3][2]
                - self.m[1][1] * self.m[3][2] * self.m[2][3]
                - self.m[1][2] * self.m[2][1] * self.m[3][3]
                - self.m[1][3] * self.m[2][2] * self.m[3][1]
            ) * invdet
            tmp.m[0][1] = (
                self.m[0][1] * self.m[2][3] * self.m[3][2]
                + self.m[0][2] * self.m[2][1] * self.m[3][3]
                + self.m[0][3] * self.m[2][2] * self.m[3][1]
                - self.m[0][1] * self.m[2][2] * self.m[3][3]
                - self.m[0][2] * self.m[2][3] * self.m[3][1]
                - self.m[0][3] * self.m[2][1] * self.m[3][2]
            ) * invdet
            tmp.m[0][2] = (
                self.m[0][1] * self.m[1][2] * self.m[3][3]
                + self.m[0][2] * self.m[1][3] * self.m[3][1]
                + self.m[0][3] * self.m[1][1] * self.m[3][2]
                - self.m[0][1] * self.m[1][3] * self.m[3][2]
                - self.m[0][2] * self.m[1][1] * self.m[3][3]
                - self.m[0][3] * self.m[1][2] * self.m[3][1]
            ) * invdet
            tmp.m[0][3] = (
                self.m[0][1] * self.m[1][3] * self.m[2][2]
                + self.m[0][2] * self.m[1][1] * self.m[2][3]
                + self.m[0][3] * self.m[1][2] * self.m[2][1]
                - self.m[0][1] * self.m[1][2] * self.m[2][3]
                - self.m[0][2] * self.m[1][3] * self.m[2][1]
                - self.m[0][3] * self.m[1][1] * self.m[2][2]
            ) * invdet
            tmp.m[1][0] = (
                self.m[1][0] * self.m[2][3] * self.m[3][2]
                + self.m[1][2] * self.m[2][0] * self.m[3][3]
                + self.m[1][3] * self.m[2][2] * self.m[3][0]
                - self.m[1][0] * self.m[2][2] * self.m[3][3]
                - self.m[1][2] * self.m[2][3] * self.m[3][0]
                - self.m[1][3] * self.m[2][0] * self.m[3][2]
            ) * invdet
            tmp.m[1][1] = (
                self.m[0][0] * self.m[2][2] * self.m[3][3]
                + self.m[0][2] * self.m[2][3] * self.m[3][0]
                + self.m[0][3] * self.m[2][0] * self.m[3][2]
                - self.m[0][0] * self.m[2][3] * self.m[3][2]
                - self.m[0][2] * self.m[2][0] * self.m[3][3]
                - self.m[0][3] * self.m[2][2] * self.m[3][0]
            ) * invdet
            tmp.m[1][2] = (
                self.m[0][0] * self.m[1][3] * self.m[3][2]
                + self.m[0][2] * self.m[1][0] * self.m[3][3]
                + self.m[0][3] * self.m[1][2] * self.m[3][0]
                - self.m[0][0] * self.m[1][2] * self.m[3][3]
                - self.m[0][2] * self.m[1][3] * self.m[3][0]
                - self.m[0][3] * self.m[1][0] * self.m[3][2]
            ) * invdet
            tmp.m[1][3] = (
                self.m[0][0] * self.m[1][2] * self.m[2][3]
                + self.m[0][2] * self.m[1][3] * self.m[2][0]
                + self.m[0][3] * self.m[1][0] * self.m[2][2]
                - self.m[0][0] * self.m[1][3] * self.m[2][2]
                - self.m[0][2] * self.m[1][0] * self.m[2][3]
                - self.m[0][3] * self.m[1][2] * self.m[2][0]
            ) * invdet
            tmp.m[2][0] = (
                self.m[1][0] * self.m[2][1] * self.m[3][3]
                + self.m[1][1] * self.m[2][3] * self.m[3][0]
                + self.m[1][3] * self.m[2][0] * self.m[3][1]
                - self.m[1][0] * self.m[2][3] * self.m[3][1]
                - self.m[1][1] * self.m[2][0] * self.m[3][3]
                - self.m[1][3] * self.m[2][1] * self.m[3][0]
            ) * invdet
            tmp.m[2][1] = (
                self.m[0][0] * self.m[2][3] * self.m[3][1]
                + self.m[0][1] * self.m[2][0] * self.m[3][3]
                + self.m[0][3] * self.m[2][1] * self.m[3][0]
                - self.m[0][0] * self.m[2][1] * self.m[3][3]
                - self.m[0][1] * self.m[2][3] * self.m[3][0]
                - self.m[0][3] * self.m[2][0] * self.m[3][1]
            ) * invdet
            tmp.m[2][2] = (
                self.m[0][0] * self.m[1][1] * self.m[3][3]
                + self.m[0][1] * self.m[1][3] * self.m[3][0]
                + self.m[0][3] * self.m[1][0] * self.m[3][1]
                - self.m[0][0] * self.m[1][3] * self.m[3][1]
                - self.m[0][1] * self.m[1][0] * self.m[3][3]
                - self.m[0][3] * self.m[1][1] * self.m[3][0]
            ) * invdet
            tmp.m[2][3] = (
                self.m[0][0] * self.m[1][3] * self.m[2][1]
                + self.m[0][1] * self.m[1][0] * self.m[2][3]
                + self.m[0][3] * self.m[1][1] * self.m[2][0]
                - self.m[0][0] * self.m[1][1] * self.m[2][3]
                - self.m[0][1] * self.m[1][3] * self.m[2][0]
                - self.m[0][3] * self.m[1][0] * self.m[2][1]
            ) * invdet
            tmp.m[3][0] = (
                self.m[1][0] * self.m[2][2] * self.m[3][1]
                + self.m[1][1] * self.m[2][0] * self.m[3][2]
                + self.m[1][2] * self.m[2][1] * self.m[3][0]
                - self.m[1][0] * self.m[2][1] * self.m[3][2]
                - self.m[1][1] * self.m[2][2] * self.m[3][0]
                - self.m[1][2] * self.m[2][0] * self.m[3][1]
            ) * invdet
            tmp.m[3][1] = (
                self.m[0][0] * self.m[2][1] * self.m[3][2]
                + self.m[0][1] * self.m[2][2] * self.m[3][0]
                + self.m[0][2] * self.m[2][0] * self.m[3][1]
                - self.m[0][0] * self.m[2][2] * self.m[3][1]
                - self.m[0][1] * self.m[2][0] * self.m[3][2]
                - self.m[0][2] * self.m[2][1] * self.m[3][0]
            ) * invdet
            tmp.m[3][2] = (
                self.m[0][0] * self.m[1][2] * self.m[3][1]
                + self.m[0][1] * self.m[1][0] * self.m[3][2]
                + self.m[0][2] * self.m[1][1] * self.m[3][0]
                - self.m[0][0] * self.m[1][1] * self.m[3][2]
                - self.m[0][1] * self.m[1][2] * self.m[3][0]
                - self.m[0][2] * self.m[1][0] * self.m[3][1]
            ) * invdet
            tmp.m[3][3] = (
                self.m[0][0] * self.m[1][1] * self.m[2][2]
                + self.m[0][1] * self.m[1][2] * self.m[2][0]
                + self.m[0][2] * self.m[1][0] * self.m[2][1]
                - self.m[0][0] * self.m[1][2] * self.m[2][1]
                - self.m[0][1] * self.m[1][0] * self.m[2][2]
                - self.m[0][2] * self.m[1][1] * self.m[2][0]
            ) * invdet
            return tmp
        except ZeroDivisionError:
            raise Mat4Error

    def __repr__(self) -> str:
        return f"Mat4({self.m})"
