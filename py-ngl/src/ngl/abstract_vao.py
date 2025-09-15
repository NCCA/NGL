import abc

import numpy as np
from OpenGL.GL import *


class VertexData:
    def __init__(self, data, size, mode=GL_STATIC_DRAW):
        self.data = np.array(data, dtype=np.float32)
        self.size = size
        self.mode = mode


class AbstractVAO(abc.ABC):
    def __init__(self, mode=GL_TRIANGLES):
        self.m_id = glGenVertexArrays(1)
        self.m_mode = mode
        self.m_bound = False
        self.m_allocated = False
        self.m_indicesCount = 0

    def bind(self):
        glBindVertexArray(self.m_id)
        self.m_bound = True

    def unbind(self):
        glBindVertexArray(0)
        self.m_bound = False

    @abc.abstractmethod
    def draw(self):
        pass

    @abc.abstractmethod
    def set_data(self, data):
        pass

    @abc.abstractmethod
    def remove_vao(self):
        pass

    def set_vertex_attribute_pointer(self, id, size, type, stride, offset, normalize=False):
        glVertexAttribPointer(id, size, type, normalize, stride, ctypes.c_void_p(offset))
        glEnableVertexAttribArray(id)

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
    def map_buffer(self, index=0, access_mode=GL_READ_WRITE):
        pass

    def unmap_buffer(self):
        glUnmapBuffer(GL_ARRAY_BUFFER)

    def get_id(self):
        return self.m_id
