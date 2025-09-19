from dataclasses import dataclass

import numpy as np
import OpenGL.GL as gl

from . import vao_factory
from .abstract_vao import VertexData
from .bbox import BBox
from .log import logger


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
        self.vao = None
        self.bbox = None
        self.min_x = 0.0
        self.max_x = 0.0
        self.min_y = 0.0
        self.max_y = 0.0
        self.min_z = 0.0
        self.max_z = 0.0
        self.texture_id = 0
        self.texture = False

    def is_triangular(self):
        return all(len(f.vertex) == 3 for f in self.faces)

    def create_vao(self, reset_vao=False):
        if reset_vao:
            if self.vao is not None:
                logger.warning("VAO exist so returning")
                return
        else:
            if self.vao is not None:
                logger.warning("Creating new VAO")

        data_pack_type = 0
        if self.is_triangular():
            data_pack_type = gl.GL_TRIANGLES
        if data_pack_type == 0:
            logger.error("Can only create VBO from all Triangle data at present")
            raise RuntimeError("Can only create VBO from all Triangle data at present")

        @dataclass
        class VertData:
            x: float = 0.0
            y: float = 0.0
            z: float = 0.0
            nx: float = 0.0
            ny: float = 0.0
            nz: float = 0.0
            u: float = 0.0
            v: float = 0.0

            def as_array(self) -> np.ndarray:
                return np.array(
                    [self.x, self.y, self.z, self.nx, self.ny, self.nz, self.u, self.v],
                    dtype=np.float32,
                )

        vbo_mesh = []
        for face in self.faces:
            for i in range(3):
                d = VertData()
                d.x = self.vertex[face.vertex[i]].x
                d.y = self.vertex[face.vertex[i]].y
                d.z = self.vertex[face.vertex[i]].z
                if self.normals and self.uv:
                    d.nx = self.normals[face.normal[i]].x
                    d.ny = self.normals[face.normal[i]].y
                    d.nz = self.normals[face.normal[i]].z
                    d.u = self.uv[face.uv[i]].x
                    d.v = 1 - self.uv[face.uv[i]].y

                elif self.normals and not self.uv:
                    d.nx = self.normals[face.normal[i]].x
                    d.ny = self.normals[face.normal[i]].y
                    d.nz = self.normals[face.normal[i]].z
                elif not self.normals and self.uv:
                    d.u = self.uv[face.uv[i]].x
                    d.v = 1 - self.uv[face.uv[i]].y
                vbo_mesh.append(d)

        mesh_data = np.concatenate([v.as_array() for v in vbo_mesh]).astype(np.float32)
        self.vao = vao_factory.VAOFactory.create_vao(
            vao_factory.VAOType.SIMPLE, data_pack_type
        )
        with self.vao as vao:
            mesh_size = len(mesh_data) // 8
            vao.set_data(VertexData(mesh_data, mesh_size))
            # vertex
            vao.set_vertex_attribute_pointer(0, 3, gl.GL_FLOAT, 8 * 4, 0)
            # normals
            vao.set_vertex_attribute_pointer(1, 3, gl.GL_FLOAT, 8 * 4, 3 * 4)
            # uvs
            vao.set_vertex_attribute_pointer(2, 2, gl.GL_FLOAT, 8 * 4, 6 * 4)
            vao.set_num_indices(mesh_size)
        self.calc_dimensions()
        self.bbox = BBox.from_extents(
            self.min_x, self.max_x, self.min_y, self.max_y, self.min_z, self.max_z
        )

    def calc_dimensions(self):
        if not self.vertex:
            return
        self.min_x = self.max_x = self.vertex[0].x
        self.min_y = self.max_y = self.vertex[0].y
        self.min_z = self.max_z = self.vertex[0].z
        for v in self.vertex:
            self.min_x = min(self.min_x, v.x)
            self.max_x = max(self.max_x, v.x)
            self.min_y = min(self.min_y, v.y)
            self.max_y = max(self.max_y, v.y)
            self.min_z = min(self.min_z, v.z)
            self.max_z = max(self.max_z, v.z)

    def draw(self):
        if self.vao:
            if self.texture_id:
                gl.glBindTexture(gl.GL_TEXTURE_2D, self.texture_id)
            with self.vao as vao:
                vao.draw()
