"""
Simple float only Vec3 class for 3D graphics, very similar to the pyngl ones
"""

import math

import numpy as np

from .util import clamp


class Vec3:
    """
    A simple 3D vector class for 3D graphics, I use slots to fix the attributes to x,y,z
    Attributes:
        x (float): The x-coordinate of the vector.
        y (float): The y-coordinate of the vector.
        z (float): The z-coordinate of the vector.

    """

    __slots__ = ["_x", "_y", "_z"]  # fix the attributes to x,y,z

    def __init__(self, x=0.0, y=0.0, z=0.0):
        """
        Initializes a new instance of the Vec3 class.

        Args:
            x (float, optional): The x-coordinate of the vector. Defaults to 0.0.
            y (float, optional): The y-coordinate of the vector. Defaults to 0.0.
            z (float, optional): The z-coordinate of the vector. Defaults to 0.0.
        """
        self._x = x  # x component of vector : float
        self._y = y  # y component of vector : float
        self._z = z  # z component of vector : float

    @classmethod
    def sizeof(cls):
        return 3 * 4  # 3 floats, each 4 bytes

    def __iter__(self):
        """
        Make the Vec3 class iterable.
        Yields:
            float: The x, y, and z components of the vector.
        """
        yield self.x
        yield self.y
        yield self.z

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
        components = [self.x, self.y, self.z]
        try:
            return components[index]
        except IndexError:
            raise IndexError("Index out of range. Valid indices are 0, 1, and 2.")

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

    def clone(self) -> "Vec3":
        """
        Create a clone of the current vector.
        Returns:
            Vec3: A new instance of Vec3 with the same x, y, and z values.
        """
        return Vec3(self.x, self.y, self.z)

    def __add__(self, rhs):
        """
        vector addition a+b

        Args:
            rhs (Vec3): The right-hand side vector to add.
        Returns:
            Vec3: A new vector that is the result of adding this vector and the rhs vector.
        """
        r = Vec3()
        r.x = self.x + rhs.x
        r.y = self.y + rhs.y
        r.z = self.z + rhs.z
        return r

    def __iadd__(self, rhs):
        """
        vector addition a+=b

        Args:
            rhs (Vec3): The right-hand side vector to add.
        Returns:
            Vec3: returns this vector after adding the rhs vector.
        """
        self.x += rhs.x
        self.y += rhs.y
        self.z += rhs.z
        return self

    def __sub__(self, rhs):
        """
        vector subtraction a-b

        Args:
            rhs (Vec3): The right-hand side vector to subtract.
        Returns:
            Vec3: A new vector that is the result of subtracting this vector and the rhs vector.
        """
        r = Vec3()
        r.x = self.x - rhs.x
        r.y = self.y - rhs.y
        r.z = self.z - rhs.z
        return r

    def __isub__(self, rhs):
        """
        vector subtraction a-=b

        Args:
            rhs (Vec3): The right-hand side vector to add.
        Returns:
            Vec3: returns this vector after subtracting the rhs vector.
        """
        self.x -= rhs.x
        self.y -= rhs.y
        self.z -= rhs.z
        return self

    def __eq__(self, rhs):
        """
        vector comparison a==b using math.isclose not we only compare to 6 decimal places
        Args:
            rhs (Vec3): The right-hand side vector to compare.
        Returns:
            bool: True if the vectors are close, False otherwise.
            NotImplemented: If the right-hand side is not a Vec3.
        """

        if not isinstance(rhs, Vec3):
            return NotImplemented
        return (
            math.isclose(self.x, rhs.x)
            and math.isclose(self.y, rhs.y)
            and math.isclose(self.z, rhs.z)
        )

    def __neq__(self, rhs):
        """
        vector comparison a!=b using math.isclose not we only compare to 6 decimal places
        Args:
            rhs (Vec3): The right-hand side vector to compare.
        Returns:
            bool: True if the vectors are close, False otherwise.
            NotImplemented: If the right-hand side is not a Vec3.
        """
        if not isinstance(rhs, Vec3):
            return NotImplemented
        return (
            math.isclose(self.x, rhs.x)
            or math.isclose(self.y, rhs.y)
            or math.isclose(self.z, rhs.z)
        )

    def __neg__(self):
        """
        negate a vector -a
        """
        self.x = -self.x
        self.y = -self.y
        self.z = -self.z
        return self

    def set(self, x, y, z):
        """
        set the x,y,z values of the vector
        Args:
            x (float): The x-coordinate of the vector.
            y (float): The y-coordinate of the vector.
            z (float): The z-coordinate of the vector.
        Raises :
            ValueError: if x,y,z are not float
        """
        try:
            self.x = float(x)
            self.y = float(y)
            self.z = float(z)
        except ValueError:
            raise ValueError(f"Vec3.set {x=} {y=} {z=} all need to be float")

    def dot(self, rhs):
        """
        dot product of two vectors a.b
        Args:
            rhs (Vec3): The right-hand side vector to dot product with.
        """
        return self.x * rhs.x + self.y * rhs.y + self.z * rhs.z

    def length(self):
        """
        length of vector
        Returns:
            float: The length of the vector.
        """
        return math.sqrt(self.x**2 + self.y**2 + self.z**2)

    def length_squared(self):
        """
        length of vector squared sometimes used to avoid the sqrt for performance
        Returns:
            float: The length of the vector squared
        """
        return self.x**2 + self.y**2 + self.z**2

    def inner(self, rhs):
        """
        inner product of two vectors a.b
        Args:
            rhs (Vec3): The right-hand side vector to inner product with.
        Returns:
            float: The inner product of the two vectors.
        """
        return (self.x * rhs.x) + (self.y * rhs.y) + (self.z * rhs.z)

    def null(self):
        """
        set the vector to zero
        """
        self.x = 0.0
        self.y = 0.0
        self.z = 0.0

    def cross(self, rhs):
        """
        cross product of two vectors a x b
        Args:
            rhs (Vec3): The right-hand side vector to cross product with.
        Returns:
            Vec3: A new vector that is the result of the cross product.
        """
        return Vec3(
            self.y * rhs.z - self.z * rhs.y,
            self.z * rhs.x - self.x * rhs.z,
            self.x * rhs.y - self.y * rhs.x,
        )

    def normalize(self):
        """
        normalize the vector to unit length
        Returns:
            Vec3: A new vector that is the result of normalizing this vector.
        Raises:
            ZeroDivisionError: If the length of the vector is zero.
        """
        vector_length = self.length()
        try:
            self.x /= vector_length
            self.y /= vector_length
            self.z /= vector_length
        except ZeroDivisionError:
            raise ZeroDivisionError(
                f"Vec3.normalize {vector_length} length is zero most likely calling normalize on a zero vector"
            )
        return self

    def reflect(self, n):
        """
        reflect a vector about a normal
        Args:
            n (Vec3): The normal to reflect about.
        Returns:
            Vec3: A new vector that is the result of reflecting this vector about the normal.
        """
        d = self.dot(n)
        #  I - 2.0 * dot(N, I) * N
        return Vec3(
            self.x - 2.0 * d * n.x, self.y - 2.0 * d * n.y, self.z - 2.0 * d * n.z
        )

    def clamp(self, low, high):
        """
        clamp the vector to a range
        Args:
            low (float): The low end of the range.
            high (float): The high end of the range.

        """
        self.x = clamp(self.x, low, high)
        self.y = clamp(self.y, low, high)
        self.z = clamp(self.z, low, high)

    def __repr__(self):
        "object representation for debugging"
        return f"Vec3 [{self.x},{self.y},{self.z}]"

    def __str__(self):
        "object representation for debugging"
        return f"[{self.x},{self.y},{self.z}]"

    def outer(self, rhs):
        """
        outer product of two vectors a x b
        Args:
            rhs (Vec3): The right-hand side vector to outer product with.
        Returns:
            Mat3: A new 3x3 matrix that is the result of the outer product.
        """
        from ngl import Mat3

        return Mat3.from_list(
            [
                [self.x * rhs.x, self.x * rhs.y, self.x * rhs.z],
                [self.y * rhs.x, self.y * rhs.y, self.y * rhs.z],
                [self.z * rhs.x, self.z * rhs.y, self.z * rhs.z],
            ]
        )

    def __mul__(self, rhs):
        """
        piecewise scalar multiplication
        Args:
            rhs (float): The scalar to multiply by.
        Returns:
            Vec3: A new vector that is the result of multiplying this vector by the scalar.
        Raises:
            ValueError: If the right-hand side is not a float.
        """
        if isinstance(rhs, (float, int)):
            return Vec3(self.x * rhs, self.y * rhs, self.z * rhs)
        else:
            raise ValueError(
                f"can only do piecewise multiplication with a scalar {rhs=}"
            )

    def __rmul__(self, rhs):
        """
        piecewise scalar multiplication
        Args:
            rhs (float): The scalar to multiply by.
        Returns:
            Vec3: A new vector that is the result of multiplying this vector by the scalar.
        Raises:
            ValueError: If the right-hand side is not a float.
        """
        return self * rhs

    def __matmul__(self, rhs):
        """
        "Vec3 @ Mat3 matrix multiplication"
        Args:
            rhs (Mat3): The matrix to multiply by.
        Returns:
            Vec3: A new vector that is the result of multiplying this vector by the matrix.
        """
        return Vec3(
            self.x * rhs.m[0][0] + self.y * rhs.m[1][0] + self.z * rhs.m[2][0],
            self.x * rhs.m[0][1] + self.y * rhs.m[1][1] + self.z * rhs.m[2][1],
            self.x * rhs.m[0][2] + self.y * rhs.m[1][2] + self.z * rhs.m[2][2],
        )

    def to_list(self):
        return [self.x, self.y, self.z]

    def to_numpy(self):
        return np.array([self.x, self.y, self.z])


# Helper function to create properties
def _create_property(attr_name):
    def getter(self):
        return getattr(self, f"_{attr_name}")

    def setter(self, value):
        self._validate_and_set(value, f"_{attr_name}")

    return property(getter, setter)


# Dynamically add properties for x, y, z
for attr in ["x", "y", "z"]:
    setattr(Vec3, attr, _create_property(attr))
