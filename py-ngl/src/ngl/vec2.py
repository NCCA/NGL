import numpy as np


class Vec2:
    def __init__(self, x=0.0, y=0.0):
        self.v = np.array([x, y], dtype=np.float32)

    @property
    def x(self):
        return self.v[0]

    @x.setter
    def x(self, value):
        self.v[0] = value

    @property
    def y(self):
        return self.v[1]

    @y.setter
    def y(self, value):
        self.v[1] = value

    def __eq__(self, other):
        return np.allclose(self.v, other.v)

    def __str__(self):
        return f"({self.x}, {self.y})"
