import math
from typing import Self

import numpy as np

from .mat4 import Mat4
from .vec3 import Vec3
from .vec4 import Vec4


class Quaternion:
    """A quaternion class.

    This class represents a quaternion and provides various quaternion operations.
    The components are stored as (s, x, y, z).
    """

    __slots__ = ["_m"]
    _m: np.ndarray

    def __init__(
        self, s: float = 1.0, x: float = 0.0, y: float = 0.0, z: float = 0.0
    ) -> None:
        """Initializes a new Quaternion instance."""
        self._m = np.array([s, x, y, z], dtype=np.float32)

    @property
    def s(self) -> float:
        return self._m[0]

    @s.setter
    def s(self, value: float) -> None:
        self._m[0] = value

    @property
    def x(self) -> float:
        return self._m[1]

    @x.setter
    def x(self, value: float) -> None:
        self._m[1] = value

    @property
    def y(self) -> float:
        return self._m[2]

    @y.setter
    def y(self, value: float) -> None:
        self._m[2] = value

    @property
    def z(self) -> float:
        return self._m[3]

    @z.setter
    def z(self, value: float) -> None:
        self._m[3] = value

    def __repr__(self) -> str:
        return f"Quaternion({self.s}, {self.x}, {self.y}, {self.z})"

    def __eq__(self, other: Self) -> bool:
        return np.allclose(self._m, other._m)

    def __ne__(self, other: Self) -> bool:
        return not self.__eq__(other)

    def __add__(self, other: Self) -> Self:
        return Quaternion(*(self._m + other._m))

    def __iadd__(self, other: Self) -> Self:
        self._m += other._m
        return self

    def __sub__(self, other: Self) -> Self:
        return Quaternion(*(self._m - other._m))

    def __isub__(self, other: Self) -> Self:
        self._m -= other._m
        return self

    def __mul__(self, other: float | Self | Vec4) -> Self | Vec4:
        if isinstance(other, (int, float, np.floating)):
            return Quaternion(*(self._m * other))
        elif isinstance(other, Quaternion):
            s = self.s * other.s - np.dot(self._m[1:], other._m[1:])
            v = (
                self.s * other._m[1:]
                + other.s * self._m[1:]
                + np.cross(self._m[1:], other._m[1:])
            )
            return Quaternion(s, *v)
        elif isinstance(other, Vec4):
            q_vec = self._m[1:]
            uv = np.cross(q_vec, other._m[:3])
            uuv = np.cross(q_vec, uv)
            return Vec4(*(other._m[:3] + ((uv * self.s) + uuv) * 2.0), other.w)
        else:
            raise TypeError(
                f"Unsupported operand type(s) for *: 'Quaternion' and '{type(other)}'"
            )

    def __imul__(self, other: float | Self) -> Self:
        if isinstance(other, (int, float, np.floating)):
            self._m *= other
        elif isinstance(other, Quaternion):
            s = self.s * other.s - np.dot(self._m[1:], other._m[1:])
            v = (
                self.s * other._m[1:]
                + other.s * self._m[1:]
                + np.cross(self._m[1:], other._m[1:])
            )
            self._m[0] = s
            self._m[1:] = v
        else:
            raise TypeError(
                f"Unsupported operand type(s) for *=: 'Quaternion' and '{type(other)}'"
            )
        return self

    def magnitude(self) -> float:
        return np.linalg.norm(self._m)

    def normalize(self) -> None:
        norm = self.magnitude()
        if norm > 0:
            self._m /= norm

    def conjugate(self) -> Self:
        return Quaternion(self.s, -self.x, -self.y, -self.z)

    def inverse(self) -> Self:
        return self.conjugate() * (1.0 / self.magnitude() ** 2)

    def to_mat4(self) -> Mat4:
        xx = self.x * self.x
        xy = self.x * self.y
        xz = self.x * self.z
        xs = self.x * self.s
        yy = self.y * self.y
        yz = self.y * self.z
        ys = self.y * self.s
        zz = self.z * self.z
        zs = self.z * self.s

        return Mat4(
            1.0 - 2.0 * (yy + zz),
            2.0 * (xy + zs),
            2.0 * (xz - ys),
            0.0,
            2.0 * (xy - zs),
            1.0 - 2.0 * (xx + zz),
            2.0 * (yz + xs),
            0.0,
            2.0 * (xz + ys),
            2.0 * (yz - xs),
            1.0 - 2.0 * (xx + yy),
            0.0,
            0.0,
            0.0,
            0.0,
            1.0,
        )

    @staticmethod
    def from_axis_angle(axis: Vec3, angle: float) -> Self:
        rad = math.radians(angle) / 2.0
        s = math.cos(rad)
        c = math.sin(rad)
        axis.normalize()
        return Quaternion(s, axis.x * c, axis.y * c, axis.z * c)

    def to_axis_angle(self) -> tuple[Vec3, float]:
        angle = math.degrees(math.acos(self.s) * 2.0)
        s = math.sqrt(1.0 - self.s * self.s)
        if s < 0.001:
            return Vec3(self.x, self.y, self.z), angle
        else:
            return Vec3(self.x / s, self.y / s, self.z / s), angle

    @staticmethod
    def slerp(q1: Self, q2: Self, t: float) -> Self:
        dot = np.dot(q1._m, q2._m)

        if dot < 0.0:
            q2 = q2 * -1.0
            dot = -dot

        if dot > 0.9995:
            result = q1 + t * (q2 - q1)
            result.normalize()
            return result

        theta_0 = math.acos(dot)
        theta = theta_0 * t
        sin_theta = math.sin(theta)
        sin_theta_0 = math.sin(theta_0)

        s1 = math.cos(theta) - dot * sin_theta / sin_theta_0
        s2 = sin_theta / sin_theta_0

        return (q1 * s1) + (q2 * s2)
