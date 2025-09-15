"""
A simple Quaternion class for use in NCCA Python
Attributes:
    s (float): The scalar part of the quaternion.
    x (float): The x-coordinate of the vector part of the quaternion.
    y (float): The y-coordinate of the vector part of the quaternion.
    z (float): The z-coordinate of the vector part of the quaternion.
"""

import math

from ngl import Mat4


class Quaternion:
    __slots__ = ["s", "x", "y", "z"]  # fix the attributes to s x,y,z

    def __init__(self, s: float = 1.0, x: float = 0, y: float = 0, z: float = 0):
        """
        Initializes a new instance of the Quaternion class.

        Args:
            s (float): The scalar part of the quaternion.
            x (float): The x-coordinate of the vector part of the quaternion.
            y (float): The y-coordinate of the vector part of the quaternion.
            z (float): The z-coordinate of the vector part of the quaternion.

        """
        self.s = float(s)
        self.x = float(x)
        self.y = float(y)
        self.z = float(z)

    @staticmethod
    def from_mat4(mat: "Mat4") -> "Quaternion":
        """
        Creates a new Quaternion from a Mat4 rotation matrix.

        Args:
            mat (Mat4): The rotation matrix to convert.

        Returns:
            Quaternion: A new Quaternion representing the rotation matrix.

        """
        matrix = mat.get_matrix()
        T = 1.0 + matrix[0] + matrix[5] + matrix[10]
        if T > 0.00000001:  # to avoid large distortions!
            scale = math.sqrt(T) * 2.0
            x = (matrix[6] - matrix[9]) / scale
            y = (matrix[8] - matrix[2]) / scale
            z = (matrix[1] - matrix[4]) / scale
            s = 0.25 * scale
        elif matrix[0] > matrix[5] and matrix[0] > matrix[10]:
            scale = math.sqrt(1.0 + matrix[0] - matrix[5] - matrix[10]) * 2.0
            x = 0.25 * scale
            y = (matrix[4] + matrix[1]) / scale
            z = (matrix[2] + matrix[8]) / scale
            s = (matrix[6] - matrix[9]) / scale

        elif matrix[5] > matrix[10]:
            scale = math.sqrt(1.0 + matrix[5] - matrix[0] - matrix[10]) * 2.0
            x = (matrix[4] + matrix[1]) / scale
            y = 0.25 * scale
            z = (matrix[9] + matrix[6]) / scale
            s = (matrix[8] - matrix[2]) / scale

        else:
            scale = math.sqrt(1.0 + matrix[10] - matrix[0] - matrix[5]) * 2.0
            x = (matrix[8] + matrix[2]) / scale
            y = (matrix[9] + matrix[6]) / scale
            z = 0.25 * scale
            s = (matrix[1] - matrix[4]) / scale

        return Quaternion(s, x, y, z)

    def __add__(self, rhs):
        return Quaternion(
            self.s + rhs.s, self.x + rhs.x, self.y + rhs.y, self.z + rhs.z
        )

    def __iadd__(self, rhs):
        self.s += rhs.s
        self.x += rhs.x
        self.y += rhs.y
        self.z += rhs.z
        return self

    def __sub__(self, rhs):
        return Quaternion(
            self.s - rhs.s, self.x - rhs.x, self.y - rhs.y, self.z - rhs.z
        )

    def __isub__(self, rhs):
        return self.__sub__(rhs)

    def __mul__(self, rhs):
        return Quaternion(
            self.s * rhs.s - self.x * rhs.x - self.y * rhs.y - self.z * rhs.z,
            self.s * rhs.x + self.x * rhs.s + self.y * rhs.z - self.z * rhs.y,
            self.s * rhs.y - self.x * rhs.z + self.y * rhs.s + self.z * rhs.x,
            self.s * rhs.z + self.x * rhs.y - self.y * rhs.x + self.z * rhs.s,
        )

    def __str__(self) -> str:
        """
        Returns a string representation of the Quaternion.

        Returns:
            str: A string representation of the Quaternion.

        """
        return f"Quaternion({self.s}, [{self.x}, {self.y}, {self.z}])"

    def __repr__(self) -> str:
        return f"Quaternion({self.s}, [{self.x}, {self.y}, {self.z}])"
