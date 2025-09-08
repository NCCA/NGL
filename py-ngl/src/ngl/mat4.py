import math
from typing import Self

import numpy as np

from .vec4 import Vec4


class Mat4:
    """A 4x4 matrix class.

    This class represents a 4x4 matrix and provides various matrix operations.
    It uses a numpy array for the underlying data storage in column-major order.
    """

    __slots__ = ["_m"]
    _m: np.ndarray

    def __init__(self, *args) -> None:
        """Initializes a new Mat4 instance.

        If no arguments are given, an identity matrix is created.
        If one argument is given, it is treated as a scalar to create a scaled identity matrix.
        If 16 arguments are given, they are used to populate the matrix in column-major order.
        """
        if len(args) == 0:
            self._m = np.identity(4, dtype=np.float32).flatten(order="F")
        elif len(args) == 1 and isinstance(args[0], (int, float)):
            self._m = np.identity(4, dtype=np.float32).flatten(order="F")
            self._m[0] = args[0]
            self._m[5] = args[0]
            self._m[10] = args[0]
        elif len(args) == 16:
            self._m = np.array(args, dtype=np.float32)
        else:
            raise ValueError("Invalid number of arguments for Mat4 constructor")

    def __repr__(self) -> str:
        """Return a string representation of the matrix."""
        return f"Mat4({', '.join(map(str, self._m))})"

    def __getitem__(self, key: int) -> float:
        """Get a component of the matrix using index access."""
        return self._m[key]

    def __setitem__(self, key: int, value: float) -> None:
        """Set a component of the matrix using index access."""
        self._m[key] = value

    def __eq__(self, other: Self) -> bool:
        """Check for equality between two Mat4 matrices."""
        return np.allclose(self._m, other._m)

    def __ne__(self, other: Self) -> bool:
        """Check for inequality between two Mat4 matrices."""
        return not self.__eq__(other)

    def __add__(self, other: Self) -> Self:
        """Add two Mat4 matrices."""
        result = Mat4()
        result._m = self._m + other._m
        return result

    def __iadd__(self, other: Self) -> Self:
        """Add a Mat4 matrix to this matrix in-place."""
        self._m += other._m
        return self

    def __mul__(self, other: float | Self | Vec4) -> Self | Vec4:
        """Multiply the matrix by a scalar, another matrix, or a vector."""
        if isinstance(other, (int, float)):
            result = Mat4()
            result._m = self._m * other
            return result
        elif isinstance(other, Mat4):
            result = Mat4()
            result._m = np.dot(self.to_numpy(), other.to_numpy()).flatten(order="F")
            return result
        elif isinstance(other, Vec4):
            return Vec4(*np.dot(self.to_numpy(), other._m))
        else:
            raise TypeError(f"Unsupported operand type(s) for *: 'Mat4' and '{type(other)}'")

    def __imul__(self, other: float | Self) -> Self:
        """Multiply this matrix by a scalar or another matrix in-place."""
        if isinstance(other, (int, float)):
            self._m *= other
        elif isinstance(other, Mat4):
            self._m = np.dot(self.to_numpy(), other.to_numpy()).flatten(order="F")
        else:
            raise TypeError(f"Unsupported operand type(s) for *=: 'Mat4' and '{type(other)}'")
        return self

    def to_numpy(self) -> np.ndarray:
        """Return the matrix as a numpy array."""
        return self._m.reshape((4, 4), order="F")

    def identity(self) -> None:
        """Reset the matrix to the identity matrix."""
        self._m = np.identity(4, dtype=np.float32).flatten(order="F")

    def null(self) -> None:
        """Reset the matrix to all zeros."""
        self._m.fill(0)

    def transpose(self) -> None:
        """Transpose the matrix in-place."""
        self._m = self.to_numpy().transpose().flatten(order="F")

    def determinant(self) -> float:
        """Calculate the determinant of the matrix."""
        return np.linalg.det(self.to_numpy())

    def inverse(self) -> Self:
        """Calculate the inverse of the matrix."""
        result = Mat4()
        result._m = np.linalg.inv(self.to_numpy()).flatten(order="F")
        return result

    @staticmethod
    def translate(x: float, y: float, z: float) -> Self:
        """Create a translation matrix."""
        mat = Mat4()
        mat[12] = x
        mat[13] = y
        mat[14] = z
        return mat

    @staticmethod
    def scale(x: float, y: float, z: float) -> Self:
        """Create a scaling matrix."""
        mat = Mat4()
        mat[0] = x
        mat[5] = y
        mat[10] = z
        return mat

    @staticmethod
    def rotate_x(angle: float) -> Self:
        """Create a rotation matrix around the X axis."""
        mat = Mat4()
        rad = math.radians(angle)
        c = math.cos(rad)
        s = math.sin(rad)
        mat[5] = c
        mat[6] = s
        mat[9] = -s
        mat[10] = c
        return mat

    @staticmethod
    def rotate_y(angle: float) -> Self:
        """Create a rotation matrix around the Y axis."""
        mat = Mat4()
        rad = math.radians(angle)
        c = math.cos(rad)
        s = math.sin(rad)
        mat[0] = c
        mat[2] = -s
        mat[8] = s
        mat[10] = c
        return mat

    @staticmethod
    def rotate_z(angle: float) -> Self:
        """Create a rotation matrix around the Z axis."""
        mat = Mat4()
        rad = math.radians(angle)
        c = math.cos(rad)
        s = math.sin(rad)
        mat[0] = c
        mat[1] = s
        mat[4] = -s
        mat[5] = c
        return mat

    def as_quaternion(self) -> "Quaternion":
        from .quaternion import Quaternion

        q = Quaternion()
        trace = self._m[0] + self._m[5] + self._m[10] + 1.0
        if trace > 0.00000001:
            s = math.sqrt(trace) * 2.0
            q.x = (self._m[6] - self._m[9]) / s
            q.y = (self._m[8] - self._m[2]) / s
            q.z = (self._m[1] - self._m[4]) / s
            q.s = 0.25 * s
        elif self._m[0] > self._m[5] and self._m[0] > self._m[10]:
            s = math.sqrt(1.0 + self._m[0] - self._m[5] - self._m[10]) * 2.0
            q.x = 0.25 * s
            q.y = (self._m[1] + self._m[4]) / s
            q.z = (self._m[8] + self._m[2]) / s
            q.s = (self._m[6] - self._m[9]) / s
        elif self._m[5] > self._m[10]:
            s = math.sqrt(1.0 + self._m[5] - self._m[0] - self._m[10]) * 2.0
            q.x = (self._m[1] + self._m[4]) / s
            q.y = 0.25 * s
            q.z = (self._m[6] + self._m[9]) / s
            q.s = (self._m[8] - self._m[2]) / s
        else:
            s = math.sqrt(1.0 + self._m[10] - self._m[0] - self._m[5]) * 2.0
            q.x = (self._m[8] + self._m[2]) / s
            q.y = (self._m[6] + self._m[9]) / s
            q.z = 0.25 * s
            q.s = (self._m[1] - self._m[4]) / s
        return q

    def to_list(self):
        return self._m
