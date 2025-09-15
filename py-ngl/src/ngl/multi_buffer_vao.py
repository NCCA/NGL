import numpy as np
from OpenGL.GL import *

from .abstract_vao import AbstractVAO, VertexData


class MultiBufferVAO(AbstractVAO):
    def __init__(self, mode=GL_TRIANGLES):
        super().__init__(mode)
        self.m_vbo_ids = []

    def draw(self):
        if self.m_bound and self.m_allocated:
            glDrawArrays(self.m_mode, 0, self.m_indicesCount)

    def set_data(self, data, index=None):
        if not isinstance(data, VertexData):
            raise TypeError("data must be of type VertexData")
        if index is None:
            index = len(self.m_vbo_ids)

        if index >= len(self.m_vbo_ids):
            new_buffers = index - len(self.m_vbo_ids) + 1
            new_ids = glGenBuffers(new_buffers)
            if isinstance(new_ids, np.ndarray):
                self.m_vbo_ids.extend(new_ids)
            else:
                self.m_vbo_ids.append(new_ids)

        glBindBuffer(GL_ARRAY_BUFFER, self.m_vbo_ids[index])
        glBufferData(GL_ARRAY_BUFFER, data.data.nbytes, data.data, data.mode)
        self.m_allocated = True
        if index == 0:  # Assume first buffer determines the number of indices
            self.m_indicesCount = data.size

    def remove_vao(self):
        glDeleteBuffers(len(self.m_vbo_ids), self.m_vbo_ids)
        glDeleteVertexArrays(1, [self.m_id])

    def get_buffer_id(self, index=0):
        return self.m_vbo_ids[index]

    def map_buffer(self, index=0, access_mode=GL_READ_WRITE):
        glBindBuffer(GL_ARRAY_BUFFER, self.m_vbo_ids[index])
        return glMapBuffer(GL_ARRAY_BUFFER, access_mode)
