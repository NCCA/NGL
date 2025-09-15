from OpenGL.GL import *

from .abstract_vao import AbstractVAO, VertexData


class SimpleVAO(AbstractVAO):
    def __init__(self, mode=GL_TRIANGLES):
        super().__init__(mode)
        self.m_buffer = glGenBuffers(1)

    def draw(self):
        if self.m_bound and self.m_allocated:
            glDrawArrays(self.m_mode, 0, self.m_indicesCount)

    def set_data(self, data):
        if not isinstance(data, VertexData):
            raise TypeError("data must be of type VertexData")
        glBindBuffer(GL_ARRAY_BUFFER, self.m_buffer)
        glBufferData(GL_ARRAY_BUFFER, data.data.nbytes, data.data, data.mode)
        self.m_allocated = True
        self.m_indicesCount = data.size

    def remove_vao(self):
        glDeleteBuffers(1, [self.m_buffer])
        glDeleteVertexArrays(1, [self.m_id])

    def get_buffer_id(self, index=0):
        return self.m_buffer

    def map_buffer(self, index=0, access_mode=GL_READ_WRITE):
        glBindBuffer(GL_ARRAY_BUFFER, self.m_buffer)
        return glMapBuffer(GL_ARRAY_BUFFER, access_mode)
