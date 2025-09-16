"""
Simple Mat3 class which can be used with the Vec3 class. By default it will be set to the identity matrix

all matrix values are stored in a 3x3 list in the format

.. highlight:: python
.. code-block:: python

  m=[[1.0,0.0,0.0],
     [0.0,1.0,0.0],
     [0.0,1.0,0.0]]

"""

import copy
import functools
import math
import operator

import numpy as np


class Mat3Error(Exception):
    """This exception will be raised if we have issues with matrix multiplication or other mathematical operations"""

    pass


class Mat3NotSquare(Exception):
    """If we try to construct from a non square (3x3) value or 9 elements this exception will be thrown"""

    pass


_identity = [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]


class Mat3:
    """Simple Mat3 class for basic affine transforms"""

    __slots__ = ["m"]
    """m : list
        the matrix values
    """

    def __init__(self):
        """construct to identity matrix"""
        self.m = copy.deepcopy(_identity)

    def get_matrix(self):
        """return matrix elements as list ideal for OpenGL

        Returns
        -------
        list
           the 9 float elements of the matrix, ideal
           for OpenGL or Renderman consumption
        """

        return functools.reduce(operator.concat, self.m)

    def get_numpy(self):
        "return matrix as a numpy array ideal for WebGPU etc"
        return np.array(self.get_matrix()).reshape([3, 3])

    @classmethod
    def identity(cls):
        """class method to return a new identity matrix

        Returns
        -------
        Mat3
            new Mat3 matrix as Identity

        """
        v = Mat3()
        return v

    @classmethod
    def zero(cls):
        """class method to return a new zero matrix

        Returns
        -------
        Mat3
            new Mat3 matrix as all zeros

        """
        v = Mat3()
        v.m = [[0.0, 0.0, 0.0], [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]]
        return v

    @classmethod
    def from_list(cls, lst):
        """class method to create Mat3 from list

        Parameters
        ----------
        lst : list

            list of 9 numbers to construct a new Mat3 from, we will accept either 9 floats or 3 lists of size 3

            .. highlight:: python
            .. code-block:: python

                a=Mat3.from_list([1,2,3,4,5,6,7,8,9])
                b=Mat3.from_list([1,2,3],[4,5,6],[7,8,9])

        Returns
        -------
            Mat3
                new Mat3 from list elements

        :raises:
            Mat3NotSquare : if we don't get a 3x3 we raise this

        """
        v = Mat3()
        v.m = lst
        if not v._is_square():
            if len(lst) == 9:  # can convert
                v.m = [lst[0:3], lst[3:6], lst[6:]]
                return v
            else:
                raise Mat3NotSquare
        else:
            return v

    def _is_square(self) -> bool:
        """ensure matrix is square"""
        return len(self.m) == 3 and all(len(i) == 3 for i in self.m)

    def transpose(self):
        """transpose this matrix"""
        self.m = [list(item) for item in zip(*self.m)]

    def get_transpose(self):
        """return a new matrix as the transpose of ourself

        Returns
        -------
            Mat3
                The transpose of the current matrix
        """
        m = Mat3()
        m.m = [list(item) for item in zip(*self.m)]
        return m

    @classmethod
    def scale(cls, x: float, y: float, z: float):
        """return a scale matrix resetting to identity first

        Parameters
        ----------
            x : float
                uniform scale in the x axis
            y : float
                uniform scale in the y axis
            z : float
                uniform scale in the z axis

        .. highlight:: python
        .. code-block:: python

            scale=Mat3.scale(2.0,1.0,3.0)

        Returns
        -------
            Mat3
                matrix with diagonals set to the scale

        """
        s = Mat3()
        s.m[0][0] = x
        s.m[1][1] = y
        s.m[2][2] = z
        return s

    @classmethod
    def rotate_x(cls, angle: float):
        """return a matrix as the rotation around the Cartesian X axis by angle degrees

        Parameters
        ----------

            angle : float
                the angle in degrees to rotate

        .. highlight:: python
        .. code-block:: python

            rotx=Mat3.rotateX(45.0)

        Returns
        -------
            Mat3
                rotation matrix
        """
        x = Mat3()
        beta = math.radians(angle)
        sr = math.sin(beta)
        cr = math.cos(beta)
        x.m[1][1] = cr
        x.m[1][2] = sr
        x.m[2][1] = -sr
        x.m[2][2] = cr
        return x

    @classmethod
    def rotate_y(cls, angle: float):
        """return a matrix as the rotation around the Cartesian Y axis by angle degrees

        Parameters
        ----------

            angle : float
                the angle in degrees to rotate

        .. highlight:: python
        .. code-block:: python

            roty=Mat3.rotateY(45.0)

        Returns
        -------
            Mat3
                rotation matrix
        """
        y = Mat3()
        beta = math.radians(angle)
        sr = math.sin(beta)
        cr = math.cos(beta)
        y.m[0][0] = cr
        y.m[0][2] = -sr
        y.m[2][0] = sr
        y.m[2][2] = cr
        return y

    @classmethod
    def rotate_z(cls, angle: float):
        """return a matrix as the rotation around the Cartesian Z axis by angle degrees

        Parameters
        ----------

            angle : float
                the angle in degrees to rotate

        .. highlight:: python
        .. code-block:: python

            rotz=Mat3.rotateZ(45.0)

        Returns
        -------
            Mat3
                rotation matrix
        """
        z = Mat3()
        beta = math.radians(angle)
        sr = math.sin(beta)
        cr = math.cos(beta)
        z.m[0][0] = cr
        z.m[0][1] = sr
        z.m[1][0] = -sr
        z.m[1][1] = cr
        return z

    def __getitem__(self, idx):
        """access array elements remember this is a list of lists [[3],[3],[3]]
        Parameters
        ----------
            idx : int
                the index into the list to get the sub list


        """
        return self.m[idx]

    def __setitem__(self, idx, item):
        """set array elements remember this is a list of lists [[3],[3],[3]]

        Parameters
        ----------
            idx : int
                the index into the list to set the sub list
        """
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
        raise Mat3Error

    def _mat_mul(self, rhs):
        "matrix mult internal function"
        # fmt: off
        a00 = self.m[0][0] # cache values for speed? (works in C++ not sure about python)
        a01 = self.m[0][1]
        a02 = self.m[0][2]
        a10 = self.m[1][0]
        a11 = self.m[1][1]
        a12 = self.m[1][2]
        a20 = self.m[2][0]
        a21 = self.m[2][1]
        a22 = self.m[2][2]

        b00 = rhs.m[0][0]
        b01 = rhs.m[0][1]
        b02 = rhs.m[0][2]
        b10 = rhs.m[1][0]
        b11 = rhs.m[1][1]
        b12 = rhs.m[1][2]
        b20 = rhs.m[2][0]
        b21 = rhs.m[2][1]
        b22 = rhs.m[2][2]

        ret=Mat3() # result mat4
        ret.m[0][0] = b00 * a00 + b01 * a10 + b02 * a20
        ret.m[0][1] = b00 * a01 + b01 * a11 + b02 * a21
        ret.m[0][2] = b00 * a02 + b01 * a12 + b02 * a22
        ret.m[1][0] = b10 * a00 + b11 * a10 + b12 * a20
        ret.m[1][1] = b10 * a01 + b11 * a11 + b12 * a21
        ret.m[1][2] = b10 * a02 + b11 * a12 + b12 * a22
        ret.m[2][0] = b20 * a00 + b21 * a10 + b22 * a20
        ret.m[2][1] = b20 * a01 + b21 * a11 + b22 * a21
        ret.m[2][2] = b20 * a02 + b21 * a12 + b22 * a22
        return ret
        # fmt: on

    def __matmul__(self, rhs):
        "multiply matrix by another matrix"
        from .vec3 import Vec3  # note relative import

        if isinstance(rhs, Mat3):
            return self._mat_mul(rhs)
        elif isinstance(rhs, Vec3):
            return Vec3(
                rhs.x * self.m[0][0] + rhs.y * self.m[0][1] + rhs.z * self.m[0][2],
                rhs.x * self.m[1][0] + rhs.y * self.m[1][1] + rhs.z * self.m[1][2],
                rhs.x * self.m[2][0] + rhs.y * self.m[2][1] + rhs.z * self.m[2][2],
            )
        else:
            raise Mat3Error

    def _add(self, rhs):
        "internal add function"
        temp = Mat3()
        for i in range(0, len(temp.m)):
            temp.m[i] = [a + b for a, b in zip(self.m[i], rhs.m[i])]
        return temp

    def __add__(self, rhs):
        "piecewise addition of elements"
        return self._add(rhs)

    def __iadd__(self, rhs):
        "piecewise addition of elements to this"
        return self._add(rhs)

    def _sub(self, rhs):
        "internal subtract function"
        temp = Mat3()
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
        return (
            +self.m[0][0] * (self.m[1][1] * self.m[2][2] - self.m[2][1] * self.m[1][2])
            - self.m[0][1] * (self.m[1][0] * self.m[2][2] - self.m[1][2] * self.m[2][0])
            + self.m[0][2] * (self.m[1][0] * self.m[2][1] - self.m[1][1] * self.m[2][0])
        )

    def to_list(self):
        "convert matrix to list"
        # flatten to single array
        return functools.reduce(operator.concat, self.m)

    def inverse(self):
        "Inverse of matrix raise MatrixError if not calculable"
        det = self.determinant()
        try:
            invdet = 1 / det
            tmp = Mat3()
            # minor matrix + co-factor
            tmp.m[0][0] = (
                +(self.m[1][1] * self.m[2][2] - self.m[1][2] * self.m[2][1]) * invdet
            )
            tmp.m[1][0] = (
                -(self.m[1][0] * self.m[2][2] - self.m[1][2] * self.m[2][0]) * invdet
            )
            tmp.m[2][0] = (
                +(self.m[1][0] * self.m[2][1] - self.m[1][1] * self.m[2][0]) * invdet
            )

            tmp.m[0][1] = (
                -(self.m[0][1] * self.m[2][2] - self.m[0][2] * self.m[2][1]) * invdet
            )
            tmp.m[1][1] = (
                +(self.m[0][0] * self.m[2][2] - self.m[0][2] * self.m[2][0]) * invdet
            )
            tmp.m[2][1] = (
                -(self.m[0][0] * self.m[2][1] - self.m[0][1] * self.m[2][0]) * invdet
            )

            tmp.m[0][2] = (
                +(self.m[0][1] * self.m[1][2] - self.m[0][2] * self.m[1][1]) * invdet
            )
            tmp.m[1][2] = (
                -(self.m[0][0] * self.m[1][2] - self.m[0][2] * self.m[1][0]) * invdet
            )
            tmp.m[2][2] = (
                +(self.m[0][0] * self.m[1][1] - self.m[0][1] * self.m[1][0]) * invdet
            )

            return tmp
        except ZeroDivisionError:
            raise Mat3Error

    def __str__(self):
        """return string representation"""
        return f"[{self.m[0]}\n{self.m[1]}\n{self.m[2]}]"

    def __repr__(self):
        """return string representation"""
        return f"Mat3({self.m})"

    @classmethod
    def from_mat4(cls, mat4):
        """Create a Mat3 from a Mat4"""
        return Mat3.from_list(
            [
                mat4.m[0][0],
                mat4.m[0][1],
                mat4.m[0][2],
                mat4.m[1][0],
                mat4.m[1][1],
                mat4.m[1][2],
                mat4.m[2][0],
                mat4.m[2][1],
                mat4.m[2][2],
            ]
        )
