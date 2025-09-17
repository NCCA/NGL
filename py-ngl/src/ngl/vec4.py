"""
Simple Float only Vec3 class for 3D graphics, very similar to the pyngl ones
"""

import math

import numpy as np
from ngl import logger


class Vec4:
    __slots__ = ["_x", "_y", "_z", "_w"]
    "by using slots we fix our class attributes to x,y,z,w"

    def __init__(self, x=0.0, y=0.0, z=0.0, w=1.0):
        """simple ctor"""
        self._x = x  # x component of vector : float
        self._y = y  # y component of vector : float
        self._z = z  # z component of vector : float
        self._w = w  # w component of vector : float

    @classmethod
    def sizeof(cls):
        return 4 * 4  # 4 floats, each 4 bytes

    def _validate_and_set(self, v, name):
        """
        check if v is a float or int
        Args:
            v (number): The value to check.
        Raises:
            ValueError: If v is not a float or int.
        """
        if not isinstance(v, (int, float)):
            raise ValueError("need float or int")
        else:
            setattr(self, name, v)

    def __iter__(self):
        """
        Make the Vec3 class iterable.
        Yields:
            float: The x, y, and z components of the vector.
        """
        yield self.x
        yield self.y
        yield self.z
        yield self.w

    def __getitem__(self, index):
        """
        Get the component of the vector at the given index.
        Args:
            index (int): The index of the component (0 for x, 1 for y, 2 for z).
        Returns:
            float: The value of the component at the given index.
        Raises:
            IndexError: If the index is out of range.
        """
        components = [self.x, self.y, self.z, self.w]
        try:
            return components[index]
        except IndexError:
            raise IndexError("Index out of range. Valid indices are 0, 1, 2, and 3.")

    def clone(self) -> "Vec4":
        """
        Create a copy of the vector.
        Returns:
            Vec4: A new Vec4 instance with the same values.
        """
        return Vec4(self.x, self.y, self.z, self.w)

    def __add__(self, rhs):
        "return a+b vector addition"
        r = Vec4()
        r.x = self.x + rhs.x
        r.y = self.y + rhs.y
        r.z = self.z + rhs.z
        r.w = self.w + rhs.w
        return r

    def __iadd__(self, rhs):
        "return a+=b vector addition"
        self.x += rhs.x
        self.y += rhs.y
        self.z += rhs.z
        self.w += rhs.w

        return self

    def __sub__(self, rhs):
        "return a+b vector addition"
        r = Vec4()
        r.x = self.x - rhs.x
        r.y = self.y - rhs.y
        r.z = self.z - rhs.z
        r.w = self.w - rhs.w
        return r

    def __isub__(self, rhs):
        "return a+=b vector addition"
        self.x -= rhs.x
        self.y -= rhs.y
        self.z -= rhs.z
        self.w -= rhs.w
        return self

    def set(self, x, y, z, w=1.0):
        "set from x,y,z,w will convert to float an raise value error if problem"
        try:
            self.x = float(x)
            self.y = float(y)
            self.z = float(z)
            self.w = float(w)
        except ValueError:
            logger.warning("need float values")
            raise

    def dot(self, rhs):
        return (self.x * rhs.x) + (self.y * rhs.y) + (self.z * rhs.z) + (self.w * rhs.w)

    def length(self):
        "length of vector"
        return math.sqrt(self.x**2 + self.y**2 + self.z**2 + self.w**2)

    def length_squared(self):
        "square length of vector"
        return self.x**2 + self.y**2 + self.z**2 + self.w**2

    def normalize(self):
        "normalize this vector"
        length = self.length()
        try:
            self.x /= length
            self.y /= length
            self.z /= length
            self.w /= length
        except ZeroDivisionError:
            raise ZeroDivisionError("cannot normalize the zero vector")
        return self

    def __eq__(self, rhs):
        "test a==b using math.isclose"
        if not isinstance(rhs, Vec4):
            return NotImplemented
        return (
            math.isclose(self.x, rhs.x)
            and math.isclose(self.y, rhs.y)
            and math.isclose(self.z, rhs.z)
            and math.isclose(self.w, rhs.w)
        )

    def __neq__(self, rhs):
        "test a==b using math.isclose"
        if not isinstance(rhs, Vec4):
            return NotImplemented
        return (
            math.isclose(self.x, rhs.x)
            or math.isclose(self.y, rhs.y)
            or math.isclose(self.z, rhs.z)
            or math.isclose(self.w, rhs.w)
        )

    def __neg__(self):
        self.x = -self.x
        self.y = -self.y
        self.z = -self.z
        self.w = -self.w
        return self

    def __mul__(self, rhs):
        if isinstance(rhs, (float, int)):
            "Vec4 * scalar multiplication"
            return Vec4(self.x * rhs, self.y * rhs, self.z * rhs, self.w * rhs)
        else:
            raise ValueError

    def __rmul__(self, rhs):
        return self * rhs

    def __matmul__(self, rhs):
        "Vec4 @ Mat4 matrix multiplication"
        return Vec4(
            self.x * rhs.m[0][0]
            + self.y * rhs.m[1][0]
            + self.z * rhs.m[2][0]
            + self.w * rhs.m[3][0],
            self.x * rhs.m[0][1]
            + self.y * rhs.m[1][1]
            + self.z * rhs.m[2][1]
            + self.w * rhs.m[3][1],
            self.x * rhs.m[0][2]
            + self.y * rhs.m[1][2]
            + self.z * rhs.m[2][2]
            + self.w * rhs.m[3][2],
            self.x * rhs.m[0][3]
            + self.y * rhs.m[1][3]
            + self.z * rhs.m[2][3]
            + self.w * rhs.m[3][3],
        )

    def __repr__(self):
        "repr for debugging purposes"
        return f"Vec4 [{self.x},{self.y},{self.z},{self.w}]"

    def __str__(self):
        "print out the vector as a string"
        return f"[{self.x},{self.y},{self.z},{self.w}]"

    def to_list(self):
        return [self.x, self.y, self.z, self.w]

    def to_numpy(self):
        return np.array([self.x, self.y, self.z, self.w])


# Helper function to create properties
def _create_property(attr_name):
    def getter(self):
        return getattr(self, f"_{attr_name}")

    def setter(self, value):
        self._validate_and_set(value, f"_{attr_name}")

    return property(getter, setter)


# Dynamically add properties for x, y, z,w
for attr in ["x", "y", "z", "w"]:
    setattr(Vec4, attr, _create_property(attr))
