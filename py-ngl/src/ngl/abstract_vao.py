import abc
import ctypes

import numpy as np
import OpenGL.GL as gl

from .log import logger


class VertexData:
    def __init__(self, data, size, mode=gl.GL_STATIC_DRAW):
        self.data = np.array(data, dtype=np.float32)
        self.size = size
        self.mode = mode


class AbstractVAO(abc.ABC):
    def __init__(self, mode=gl.GL_TRIANGLES):
        self.m_id = gl.glGenVertexArrays(1)
        self.m_mode = mode
        self.m_bound = False
        self.m_allocated = False
        self.m_indicesCount = 0

    def bind(self):
        gl.glBindVertexArray(self.m_id)
        self.m_bound = True

    def unbind(self):
        gl.glBindVertexArray(0)
        self.m_bound = False

    def __enter__(self):
        self.bind()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.unbind()

    @abc.abstractmethod
    def draw(self):
        pass

    @abc.abstractmethod
    def set_data(self, data):
        pass

    @abc.abstractmethod
    def remove_vao(self):
        pass

    def set_vertex_attribute_pointer(
        self, id, size, type, stride, offset, normalize=False
    ):
        if not self.m_bound:
            logger.error("VAO not bound in set_vertex_attribute_pointer")
        gl.glVertexAttribPointer(
            id, size, type, normalize, stride, ctypes.c_void_p(offset)
        )
        gl.glEnableVertexAttribArray(id)

    def set_num_indices(self, count):
        self.m_indicesCount = count

    def num_indices(self):
        return self.m_indicesCount

    def get_mode(self):
        return self.m_mode

    def set_mode(self, mode):
        self.m_mode = mode

    @abc.abstractmethod
    def get_buffer_id(self, index=0):
        pass

    @abc.abstractmethod
    def map_buffer(self, index=0, access_mode=gl.GL_READ_WRITE):
        pass

    def unmap_buffer(self):
        gl.glUnmapBuffer(gl.GL_ARRAY_BUFFER)

    def get_id(self):
        return self.m_id
