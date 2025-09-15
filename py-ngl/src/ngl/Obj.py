from .vec3 import Vec3
from .BaseMesh import BaseMesh, Face


class ObjParseVertexError(Exception):
    pass


class ObjParseNormalError(Exception):
    pass


class ObjParseUVError(Exception):
    pass


class ObjParseFaceError(Exception):
    pass


class Obj(BaseMesh):
    def __init__(self):
        super().__init__()
        # as faces can use negative index values keep track of index
        self._current_vertex_offset = 0
        self._current_normal_offset = 0
        self._current_uv_offset = 0

    def _parse_vertex(self, tokens):
        try:
            self.vertex.append(
                Vec3(float(tokens[1]), float(tokens[2]), float(tokens[3]))
            )
            self._current_vertex_offset += 1
            if len(tokens) == 7:  # we have the non standard colour
                if not hasattr(self, "colour"):
                    self.colour = []
                self.colour.append(
                    Vec3(float(tokens[4]), float(tokens[5]), float(tokens[6]))
                )
        except ValueError:
            raise ObjParseVertexError

    def _parse_normal(self, tokens):
        try:
            self.normals.append(
                Vec3(float(tokens[1]), float(tokens[2]), float(tokens[3]))
            )
            self._current_normal_offset += 1
        except ValueError:
            raise ObjParseNormalError

    def _parse_uv(self, tokens):
        try:
            # some DCC's use vec3 for UV so may as well support
            z = 0.0
            if len(tokens) == 4:
                z = float(tokens[3])
            self.uv.append(Vec3(float(tokens[1]), float(tokens[2]), z))
            self._current_uv_offset += 1
        except ValueError:
            raise ObjParseUVError

    def _parse_face_vertex_normal_uv(self, tokens):
        """f v/vt/vn v/vt/vn v/vt/vn v/vt/vn"""
        f = Face()
        for token in tokens[1:]:  # skip f
            # each one of these should be v/vt/vn
            vn = token.split("/")
            try:
                # note we need to subtract one from the list as obj index from 1
                idx = int(vn[0]) - 1
                if idx < 0:  # negative index so grab the index
                    # note we index from 0 not 1 like obj so adjust
                    idx = self._current_vertex_offset + (idx + 1)
                f.vertex.append(idx)
                # same for UV
                idx = int(vn[1]) - 1
                if idx < 0:  # negative index so grab the index
                    # note we index from 0 not 1 like obj so adjust
                    idx = self._current_uv_offset + (idx + 1)
                f.uv.append(idx)
                # same for normals
                idx = int(vn[2]) - 1
                if idx < 0:  # negative index so grab the index
                    # note we index from 0 not 1 like obj so adjust
                    idx = self._current_normal_offset + (idx + 1)
                f.normal.append(idx)
            except ValueError:
                raise ObjParseFaceError
        self.faces.append(f)

    def _parse_face_vertex(self, tokens):
        """f v v v v"""
        f = Face()
        for token in tokens[1:]:  # skip f
            # each one of these should be v v
            try:
                # note we need to subtract one from the list as obj index from 1
                idx = int(token) - 1
                if idx < 0:  # negative index so grab the index
                    # note we index from 0 not 1 like obj so adjust
                    idx = self._current_vertex_offset + (idx + 1)
                f.vertex.append(idx)
            except ValueError:
                raise ObjParseFaceError
        self.faces.append(f)

    def _parse_face_vertex_normal(self, tokens):
        """f v//vn v//vn v//vn v//vn"""
        f = Face()
        for token in tokens[1:]:  # skip f
            # each one of these should be v/vt/vn
            vn = token.split("//")
            try:
                # note we need to subtract one from the list as obj index from 1
                idx = int(vn[0]) - 1
                if idx < 0:  # negative index so grab the index
                    # note we index from 0 not 1 like obj so adjust
                    idx = self._current_vertex_offset + (idx + 1)
                f.vertex.append(idx)
                # same for normals
                idx = int(vn[1]) - 1
                if idx < 0:  # negative index so grab the index
                    # note we index from 0 not 1 like obj so adjust
                    idx = self._current_normal_offset + (idx + 1)
                f.normal.append(idx)
            except ValueError:
                raise ObjParseFaceError
        self.faces.append(f)

    def _parse_face_vertex_uv(self, tokens):
        """f v/vt v/vt v/vt v/vt"""
        f = Face()
        for token in tokens[1:]:  # skip f
            # each one of these should be v/vt/vn
            vn = token.split("/")
            try:
                # note we need to subtract one from the list as obj index from 1
                idx = int(vn[0]) - 1
                if idx < 0:  # negative index so grab the index
                    # note we index from 0 not 1 like obj so adjust
                    idx = self._current_vertex_offset + (idx + 1)
                f.vertex.append(idx)
                # same for uv
                idx = int(vn[1]) - 1
                if idx < 0:  # negative index so grab the index
                    # note we index from 0 not 1 like obj so adjust
                    idx = self._current_uv_offset + (idx + 1)
                f.uv.append(idx)
            except ValueError:
                raise ObjParseFaceError
        self.faces.append(f)

    def _parse_face(self, tokens):
        """face parsing is complex we have different layouts.
        don't forget we can also have negative indices main combos are :-
        f v v v v
        f v//vn v//vn v//vn v//vn
        f v/vt v/vt v/vt v/vt
        f v/vt/vn v/vt/vn v/vt/vn v/vt/vn
        """
        # first let's find what sort of face we are dealing with I assume most likely case is all
        if tokens[1].count("/") == 2 and tokens[1].find("//") == -1:
            self._parse_face_vertex_normal_uv(tokens)
        elif tokens[1].find("/") == -1:
            self._parse_face_vertex(tokens)
        elif tokens[1].find("//") != -1:
            self._parse_face_vertex_normal(tokens)
        # if we have 1 / it is a VertUV format
        elif tokens[1].count("/") == 1:
            self._parse_face_vertex_uv(tokens)

    def load(self, file):
        with open(file, "r") as obj_file:
            lines = obj_file.readlines()
        for line in lines:
            line = line.strip()  # strip whitespace
            if len(line) > 0:  # skip empty lines
                tokens = line.split()
                if tokens[0] == "v":
                    self._parse_vertex(tokens)
                elif tokens[0] == "vn":
                    self._parse_normal(tokens)
                elif tokens[0] == "vt":
                    self._parse_uv(tokens)
                elif tokens[0] == "f":
                    self._parse_face(tokens)
        return True

    @classmethod
    def from_file(cls, fname):
        obj = Obj()
        obj.load(fname)
        return obj

    def add_vertex(self, vertex):
        self.vertex.append(vertex)

    def add_vertex_colour(self, vertex, colour):
        self.vertex.append(vertex)
        if not hasattr(self, "colour"):
            self.colour = []
        self.colour.append(colour)

    def add_normal(self, normal):
        self.normals.append(normal)

    def add_uv(self, uv):
        self.uv.append(uv)

    def add_face(self, face):
        self.faces.append(face)

    def save(self, filename):
        with open(filename, "w") as obj_file:
            obj_file.write("# This file was created by nccapy/Geo/Obj.py exporter\n")
            self._write_vertices(obj_file)
            self._write_uvs(obj_file)
            self._write_normals(obj_file)
            self._write_faces(obj_file)

    def _write_vertices(self, obj_file):
        for i, v in enumerate(self.vertex):
            obj_file.write(f"v {v.x} {v.y} {v.z} ")
            if hasattr(self, "colour"):  # write colour if present
                obj_file.write(
                    f"{self.colour[i].x} {self.colour[i].y} {self.colour[i].z} "
                )
            obj_file.write("\n")

    def _write_uvs(self, obj_file):
        for v in self.uv:
            obj_file.write(f"vt {v.x} {v.y} \n")

    def _write_normals(self, obj_file):
        for v in self.normals:
            obj_file.write(f"vn {v.x} {v.y} {v.z} \n")

    def _write_faces(self, obj_file):
        for face in self.faces:
            obj_file.write("f ")
            for i in range(len(face.vertex)):
                obj_file.write(f"{face.vertex[i] + 1}")  # vert first
                if len(face.uv) != 0:
                    obj_file.write(f"/{face.uv[i] + 1}")
                if len(face.normal) != 0:
                    obj_file.write("/")
                    # weird case where we do f 1//1
                    if len(face.uv) == 0:
                        obj_file.write("/")
                    obj_file.write(f"{face.normal[i] + 1} ")
                obj_file.write(" ")
            obj_file.write("\n")
