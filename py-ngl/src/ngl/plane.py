from .vec3 import Vec3


class Plane:
    """A mathematical plane."""

    def __init__(self, p1: Vec3 = None, p2: Vec3 = None, p3: Vec3 = None) -> None:
        self._normal = Vec3(0.0, 1.0, 0.0)
        self._point = Vec3()
        self._d = 0.0
        if p1 and p2 and p3:
            self.set_points(p1, p2, p3)

    @property
    def normal(self) -> Vec3:
        return self._normal

    @property
    def point(self) -> Vec3:
        return self._point

    @property
    def d(self) -> float:
        return self._d

    def set_points(self, p1: Vec3, p2: Vec3, p3: Vec3) -> None:
        aux1 = p1 - p2
        aux2 = p3 - p2
        self._normal = aux2.cross(aux1)
        self._normal.normalize()
        self._point = p2
        self._d = -(self._normal.inner(self._point))

    def set_normal_point(self, normal: Vec3, point: Vec3) -> None:
        self._normal = normal
        self._normal.normalize()
        self._point = point
        self._d = -(self._normal.inner(self._point))

    def set_floats(self, a: float, b: float, c: float, d: float) -> None:
        self._normal.set(a, b, c)
        length = self._normal.length()
        self._normal.normalize()
        self._d = d / length

    def distance(self, p: Vec3) -> float:
        return self._d + self._normal.inner(p)
