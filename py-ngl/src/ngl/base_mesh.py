class Face:
    slots = ("vertex", "uv", "normal")

    def __init__(self):
        self.vertex = []
        self.uv = []
        self.normal = []


class BaseMesh:
    def __init__(self):
        self.vertex = []
        self.normals = []
        self.uv = []
        self.faces = []
