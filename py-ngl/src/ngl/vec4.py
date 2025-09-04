import math
from typing import Self

import numpy as np

from .vec3 import Vec3


class Vec4:
    """A 4-component vector class.

    This class represents a 4D vector and provides various vector operations.
    It uses a numpy array for the underlying data storage.
    """

    __slots__ = ["_m"]
    _m: np.ndarray

    def __init__(self, x: float = 0.0, y: float = 0.0, z: float = 0.0, w: float = 1.0) -> None:
        """Initializes a new Vec4 instance.

        Args:
            x: The x-component of the vector.
            y: The y-component of the vector.
            z: The z-component of the vector.
            w: The w-component of the vector.
        """
        self._m = np.array([x, y, z, w], dtype=np.float32)

    @property
    def x(self) -> float:
        """The x-component of the vector."""
        return self._m[0]

    @x.setter
    def x(self, value: float) -> None:
        self._m[0] = value

    @property
    def y(self) -> float:
        """The y-component of the vector."""
        return self._m[1]

    @y.setter
    def y(self, value: float) -> None:
        self._m[1] = value

    @property
    def z(self) -> float:
        """The z-component of the vector."""
        return self._m[2]

    @z.setter
    def z(self, value: float) -> None:
        self._m[2] = value

    @property
    def w(self) -> float:
        """The w-component of the vector."""
        return self._m[3]

    @w.setter
    def w(self, value: float) -> None:
        self._m[3] = value

    def __repr__(self) -> str:
        """Return a string representation of the vector."""
        return f"Vec4({self.x}, {self.y}, {self.z}, {self.w})"

    def __getitem__(self, key: int) -> float:
        """Get a component of the vector using index access."""
        return self._m[key]

    def __setitem__(self, key: int, value: float) -> None:
        """Set a component of the vector using index access."""
        self._m[key] = value

    def __eq__(self, other: Self) -> bool:
        """Check for equality between two Vec4 vectors."""
        return np.allclose(self._m, other._m)

    def __ne__(self, other: Self) -> bool:
        """Check for inequality between two Vec4 vectors."""
        return not self.__eq__(other)

    def __add__(self, other: Self) -> Self:
        """Add two Vec4 vectors."""
        result = Vec4()
        result._m[:3] = self._m[:3] + other._m[:3]
        result.w = self.w
        return result

    def __iadd__(self, other: Self) -> Self:
        """Add a Vec4 vector to this vector in-place."""
        self._m += other._m
        return self

    def __sub__(self, other: Self) -> Self:
        """Subtract one Vec4 vector from another."""
        result = Vec4()
        result._m[:3] = self._m[:3] - other._m[:3]
        result.w = self.w
        return result

    def __isub__(self, other: Self) -> Self:
        """Subtract a Vec4 vector from this vector in-place."""
        self._m -= other._m
        return self

    def __mul__(self, other: float | Self | "Mat4") -> Self:
        """Multiply the vector by a scalar, another vector, or a matrix."""
        from .mat4 import Mat4

        if isinstance(other, (int, float, np.floating)):
            result = Vec4()
            result._m[:3] = self._m[:3] * other
            result.w = self.w
            return result
        elif isinstance(other, Mat4):
            result = Vec4()
            result._m = np.dot(self._m, other.to_numpy())
            return result
        elif isinstance(other, Vec4):
            result = Vec4()
            result._m = self._m * other._m
            return result
        else:
            raise TypeError(f"Unsupported operand type(s) for *: 'Vec4' and '{type(other)}'")

    def __rmul__(self, other: float) -> Self:
        """Multiply the vector by a scalar from the right."""
        result = Vec4()
        result._m = self._m * other
        return result

    def __imul__(self, other: float | Self) -> Self:
        """Multiply this vector by a scalar or another vector in-place."""
        if isinstance(other, (int, float)):
            self._m *= other
        else:
            self._m *= other._m
        return self

    def __truediv__(self, other: float | Self) -> Self:
        """Divide the vector by a scalar or another vector."""
        result = Vec4()
        if isinstance(other, (int, float)):
            result._m = self._m / other
        else:
            result._m = self._m / other._m
        return result

    def __itruediv__(self, other: float | Self) -> Self:
        """Divide this vector by a scalar or another vector in-place."""
        if isinstance(other, (int, float)):
            self._m /= other
        else:
            self._m /= other._m
        return self

    def __neg__(self) -> Self:
        """Negate the vector."""
        result = Vec4()
        result._m = -self._m
        return result

    def set(self, x: float, y: float, z: float, w: float = 1.0) -> None:
        """Set the components of the vector.

        Args:
            x: The new x-component.
            y: The new y-component.
            z: The new z-component.
            w: The new w-component.
        """
        self._m[0] = x
        self._m[1] = y
        self._m[2] = z
        self._m[3] = w

    def dot(self, other: Self) -> float:
        """Calculate the dot product with another Vec4 vector.

        Args:
            other: The other Vec4 vector.

        Returns:
            The dot product of the two vectors.
        """
        return np.dot(self._m[:3], other._m[:3])

    def null(self) -> None:
        """Reset the vector to (0, 0, 0, 1)."""
        self.set(0.0, 0.0, 0.0, 1.0)

    def normalize(self) -> None:
        """Normalize the vector to unit length."""
        length = self.length()
        self._m[:3] /= length

    def length(self) -> float:
        """Calculate the length (magnitude) of the vector.

        Returns:
            The length of the vector.
        """
        return np.linalg.norm(self._m[:3])

    def length_squared(self) -> float:
        """Calculate the squared length of the vector.

        Returns:
            The squared length of the vector.
        """
        return self.dot(self)

    def cross(self, other: Self) -> Self:
        """Calculate the cross product with another Vec4 vector.

        Args:
            other: The other Vec4 vector.

        Returns:
            The cross product of the two vectors.
        """
        result = Vec4()
        result._m[:3] = np.cross(self._m[:3], other._m[:3])
        result.w = 0.0
        return result

    def angle_between(self, other: Self) -> float:
        """Calculate the angle between this vector and another.

        Args:
            other: The other vector.

        Returns:
            The angle in degrees.
        """
        v1 = self.copy()
        v1.normalize()
        v2 = other.copy()
        v2.normalize()
        return math.degrees(math.acos(v1.dot(v2)))

    def to_vec3(self) -> Vec3:
        """Return the vector as a Vec3."""
        return Vec3(self.x, self.y, self.z)

    def clamp(self, min_val: float, max_val: float) -> None:
        """Clamp the vector's components between a min and max value.

        Args:
            min_val: The minimum value.
            max_val: The maximum value.
        """
        self._m = np.clip(self._m, min_val, max_val)

    def copy(self) -> Self:
        """Return a copy of the vector."""
        return Vec4(self.x, self.y, self.z, self.w)

    @staticmethod
    def up() -> Self:
        """Return a unit vector pointing up (0, 1, 0, 0)."""
        return Vec4(0.0, 1.0, 0.0, 0.0)

    @staticmethod
    def down() -> Self:
        """Return a unit vector pointing down (0, -1, 0, 0)."""
        return Vec4(0.0, -1.0, 0.0, 0.0)

    @staticmethod
    def left() -> Self:
        """Return a unit vector pointing left (-1, 0, 0, 0)."""
        return Vec4(-1.0, 0.0, 0.0, 0.0)

    @staticmethod
    def right() -> Self:
        """Return a unit vector pointing right (1, 0, 0, 0)."""
        return Vec4(1.0, 0.0, 0.0, 0.0)

    @staticmethod
    def in_vec() -> Self:
        """Return a unit vector pointing in (0, 0, 1, 0)."""
        return Vec4(0.0, 0.0, 1.0, 0.0)

    @staticmethod
    def out() -> Self:
        """Return a unit vector pointing out (0, 0, -1, 0)."""
        return Vec4(0.0, 0.0, -1.0, 0.0)

    @staticmethod
    def zero() -> Self:
        """Return a zero vector (0, 0, 0, 0)."""
        return Vec4(0.0, 0.0, 0.0, 0.0)

    def outer(self, other: Self) -> "Mat4":
        from .mat4 import Mat4

        result = Mat4()
        result._m = np.outer(self._m, other._m).flatten(order="F")
        return result
