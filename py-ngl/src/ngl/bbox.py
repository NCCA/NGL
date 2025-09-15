from .vec3 import Vec3


class BBox:
    """A bounding box class."""

    def __init__(
        self,
        center: Vec3 = Vec3(),
        width: float = 2.0,
        height: float = 2.0,
        depth: float = 2.0,
    ) -> None:
        self._center = center
        self._width = width
        self._height = height
        self._depth = depth
        self._min_x = 0.0
        self._max_x = 0.0
        self._min_y = 0.0
        self._max_y = 0.0
        self._min_z = 0.0
        self._max_z = 0.0
        self._verts = [Vec3() for _ in range(8)]
        self._normals = [Vec3() for _ in range(6)]
        self.recalculate_from_center_dims()

    @classmethod
    def from_extents(
        cls,
        min_x: float,
        max_x: float,
        min_y: float,
        max_y: float,
        min_z: float,
        max_z: float,
    ) -> "BBox":
        bbox = cls()
        bbox.set_extents(min_x, max_x, min_y, max_y, min_z, max_z)
        return bbox

    @property
    def center(self) -> Vec3:
        return self._center

    @center.setter
    def center(self, value: Vec3) -> None:
        self._center = value
        self.recalculate_from_center_dims()

    @property
    def width(self) -> float:
        return self._width

    @width.setter
    def width(self, value: float) -> None:
        self._width = value
        self.recalculate_from_center_dims()

    @property
    def height(self) -> float:
        return self._height

    @height.setter
    def height(self, value: float) -> None:
        self._height = value
        self.recalculate_from_center_dims()

    @property
    def depth(self) -> float:
        return self._depth

    @depth.setter
    def depth(self, value: float) -> None:
        self._depth = value
        self.recalculate_from_center_dims()

    @property
    def min_x(self) -> float:
        return self._min_x

    @property
    def max_x(self) -> float:
        return self._max_x

    @property
    def min_y(self) -> float:
        return self._min_y

    @property
    def max_y(self) -> float:
        return self._max_y

    @property
    def min_z(self) -> float:
        return self._min_z

    @property
    def max_z(self) -> float:
        return self._max_z

    def get_vertex_array(self) -> list[Vec3]:
        return self._verts

    def get_normal_array(self) -> list[Vec3]:
        return self._normals

    def set_extents(
        self,
        min_x: float,
        max_x: float,
        min_y: float,
        max_y: float,
        min_z: float,
        max_z: float,
    ) -> None:
        self._min_x = min_x
        self._max_x = max_x
        self._min_y = min_y
        self._max_y = max_y
        self._min_z = min_z
        self._max_z = max_z
        self.recalculate_from_extents()

    def recalculate_from_center_dims(self) -> None:
        half_width = self._width / 2.0
        half_height = self._height / 2.0
        half_depth = self._depth / 2.0

        self._min_x = self._center.x - half_width
        self._max_x = self._center.x + half_width
        self._min_y = self._center.y - half_height
        self._max_y = self._center.y + half_height
        self._min_z = self._center.z - half_depth
        self._max_z = self._center.z + half_depth
        self._update_verts_and_normals()

    def recalculate_from_extents(self) -> None:
        self._width = self._max_x - self._min_x
        self._height = self._max_y - self._min_y
        self._depth = self._max_z - self._min_z
        self._center = Vec3(
            self._min_x + self._width / 2.0,
            self._min_y + self._height / 2.0,
            self._min_z + self._depth / 2.0,
        )
        self._update_verts_and_normals()

    def _update_verts_and_normals(self) -> None:
        self._verts[0].set(self._min_x, self._max_y, self._min_z)
        self._verts[1].set(self._max_x, self._max_y, self._min_z)
        self._verts[2].set(self._max_x, self._max_y, self._max_z)
        self._verts[3].set(self._min_x, self._max_y, self._max_z)
        self._verts[4].set(self._min_x, self._min_y, self._min_z)
        self._verts[5].set(self._max_x, self._min_y, self._min_z)
        self._verts[6].set(self._max_x, self._min_y, self._max_z)
        self._verts[7].set(self._min_x, self._min_y, self._max_z)

        self._normals[0].set(0.0, 1.0, 0.0)
        self._normals[1].set(0.0, -1.0, 0.0)
        self._normals[2].set(1.0, 0.0, 0.0)
        self._normals[3].set(-1.0, 0.0, 0.0)
        self._normals[4].set(0.0, 0.0, 1.0)
        self._normals[5].set(0.0, 0.0, -1.0)
