import numpy as np
from OpenGL.GL import *

from .abstract_vao import AbstractVAO, VertexData


class IndexVertexData(VertexData):
    def __init__(self, data, size, indices, index_type, mode=GL_STATIC_DRAW):
        super().__init__(data, size, mode)
        gl_to_numpy_type = {
            GL_UNSIGNED_INT: np.uint32,
            GL_UNSIGNED_SHORT: np.uint16,
            GL_UNSIGNED_BYTE: np.uint8,
        }
        numpy_dtype = gl_to_numpy_type.get(index_type)
        if numpy_dtype is None:
            raise TypeError(f"Unsupported index type: {index_type}")

        self.indices = np.array(indices, dtype=numpy_dtype)
        self.index_type = index_type


class SimpleIndexVAO(AbstractVAO):
    def __init__(self, mode=GL_TRIANGLES):
        super().__init__(mode)
        self.m_buffer = glGenBuffers(1)
        self.m_idx_buffer = glGenBuffers(1)
        self.m_index_type = GL_UNSIGNED_INT

    def draw(self):
        if self.m_bound and self.m_allocated:
            glDrawElements(self.m_mode, self.m_indicesCount, self.m_index_type, None)

    def set_data(self, data):
        if not isinstance(data, IndexVertexData):
            raise TypeError("data must be of type IndexVertexData")

        glBindBuffer(GL_ARRAY_BUFFER, self.m_buffer)
        glBufferData(GL_ARRAY_BUFFER, data.data.nbytes, data.data, data.mode)

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.m_idx_buffer)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.nbytes, data.indices, data.mode)

        self.m_allocated = True
        self.m_indicesCount = len(data.indices)
        self.m_index_type = data.index_type

    def remove_vao(self):
        glDeleteBuffers(1, [self.m_buffer])
        glDeleteBuffers(1, [self.m_idx_buffer])
        glDeleteVertexArrays(1, [self.m_id])

    def get_buffer_id(self, index=0):
        return self.m_buffer

    def map_buffer(self, index=0, access_mode=GL_READ_WRITE):
        glBindBuffer(GL_ARRAY_BUFFER, self.m_buffer)
        return glMapBuffer(GL_ARRAY_BUFFER, access_mode)
