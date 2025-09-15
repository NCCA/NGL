class Face:
    vert: list
    uv: list
    normal: list

class BaseMesh:
    verts: list
    normals: list
    uv: list
    faces: list
    def __init__(self) -> None: ...
