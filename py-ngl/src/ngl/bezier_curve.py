from .vec3 import Vec3


class BezierCurve:
    """A Bezier curve class."""

    def __init__(
        self, control_points: list[Vec3] = None, knots: list[float] = None
    ) -> None:
        self._cp = control_points if control_points is not None else []
        self._knots = knots if knots is not None else []
        self._degree = 0
        self._order = 0
        self._num_cp = 0
        self._num_knots = 0
        if self._cp:
            self._num_cp = len(self._cp)
            self._degree = self._num_cp
            self._order = self._degree + 1
            if not self._knots:
                self.create_knots()
            self._num_knots = len(self._knots)

    @property
    def control_points(self) -> list[Vec3]:
        return self._cp

    @property
    def knots(self) -> list[float]:
        return self._knots

    def add_point(self, x: float | Vec3, y: float = None, z: float = None) -> None:
        if isinstance(x, Vec3):
            self._cp.append(x)
        else:
            self._cp.append(Vec3(x, y, z))
        self._num_cp += 1
        self._degree = self._num_cp
        self._order = self._degree + 1
        self.create_knots()

    def add_knot(self, k: float) -> None:
        self._knots.append(k)
        self._num_knots = len(self._knots)

    def create_knots(self) -> None:
        self._num_knots = self._num_cp + self._order
        self._knots = [0.0] * (self._num_knots // 2) + [1.0] * (
            self._num_knots - (self._num_knots // 2)
        )

    def get_point_on_curve(self, u: float) -> Vec3:
        p = Vec3()
        for i in range(self._num_cp):
            val = self.cox_de_boor(u, i, self._degree, self._knots)
            if val > 0.001:
                p += self._cp[i] * val
        return p

    def cox_de_boor(self, u: float, i: int, k: int, knots: list[float]) -> float:
        if k == 1:
            return 1.0 if knots[i] <= u <= knots[i + 1] else 0.0

        den1 = knots[i + k - 1] - knots[i]
        den2 = knots[i + k] - knots[i + 1]

        eq1 = 0.0
        if den1 > 0:
            eq1 = ((u - knots[i]) / den1) * self.cox_de_boor(u, i, k - 1, knots)

        eq2 = 0.0
        if den2 > 0:
            eq2 = ((knots[i + k] - u) / den2) * self.cox_de_boor(u, i + 1, k - 1, knots)

        return eq1 + eq2
