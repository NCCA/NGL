import copy
import functools
import operator
from .vec2 import Vec2

class Mat2Error(Exception):
    pass


_identity = [[1.0, 0.0], [0.0, 1.0]]


class Mat2:
    __slots__ = ["m"]

    def __init__(self, m=None):
        """
        Initialize a 2x2 matrix.

        Args:
            m (list): A 2D list representing the matrix.
                        If not provided, an identity matrix is created.
        """
        self.m = copy.deepcopy(_identity) if m is None else m

    def get_matrix(self) -> list[list[float]]:
        """
        Get the current matrix representation.

        Returns:
            list: A 2D list representing the matrix.
        """
        return functools.reduce(operator.concat, self.m)

    def get_numpy(self):
        """
        Convert the current matrix to a NumPy array.

        Returns:
            np.ndarray: The matrix as a NumPy array.
        """
        import numpy as np

        return np.array(self.get_matrix()).reshape([2, 2])

    @classmethod
    def identity(cls) -> "Mat2":
        """
        Create an identity matrix.

        Returns:
            Mat2: A new identity Mat2 object.
        """
        ret = cls()
        ret.m = copy.deepcopy(_identity)
        return ret

    def __matmul__(self, rhs):
        """
        Matrix multiplication or vector transformation with a 2D matrix.

        Args:
            rhs (Mat2 | Vec2): The right-hand side operand.
                                If Mat2, perform matrix multiplication.
                                If Vec2, transform the vector by the matrix.

        Returns:
            Mat2: Resulting matrix from matrix multiplication.
            Vec2: Transformed vector.

        Raises:
            ValueError: If rhs is neither a Mat2 nor Vec2 object.
        """
        if isinstance(rhs, Mat2):
            return self._mat_mul(rhs)
        elif isinstance(rhs, Vec2):
            return Vec2(
                rhs.x * self.m[0][0] + rhs.y * self.m[0][1],
                rhs.x * self.m[1][0] + rhs.y * self.m[1][1],
            )
        else:
            raise ValueError(f"Can only multiply by Mat2 or Vec2, not {type(rhs)}")

    def _mat_mul(self, other):
        """
        Internal method to perform matrix multiplication.

        Args:
            other (Mat2): The right-hand side matrix.

        Returns:
            Mat2: Result of matrix multiplication.
        """
        ret = Mat2()
        for i in range(2):
            for j in range(2):
                ret.m[i][j] = sum(self.m[i][k] * other.m[k][j] for k in range(2))
        return ret

    def __str__(self) -> str:
        """
        String representation of the matrix.

        Returns:
            str: The string representation.
        """
        return f"Mat2({self.m[0]}, {self.m[1]})"
