import OpenGL.GL as gl

from .abstract_vao import AbstractVAO, VertexData
from .log import logger


class SimpleVAO(AbstractVAO):
    def __init__(self, mode=gl.GL_TRIANGLES):
        super().__init__(mode)
        self.m_buffer = gl.glGenBuffers(1)

    def draw(self):
        if self.m_bound and self.m_allocated:
            gl.glDrawArrays(self.m_mode, 0, self.m_indicesCount)
        else:
            logger.error("SimpleVAO not bound or not allocated")

    def set_data(self, data):
        if not isinstance(data, VertexData):
            logger.error("SimpleVAO: Invalid data type")
            raise TypeError("data must be of type VertexData")
        if not self.m_bound:
            logger.error("SimpleVAO not bound")
            raise RuntimeError("SimpleVAO not bound")
        gl.glBindBuffer(gl.GL_ARRAY_BUFFER, self.m_buffer)
        gl.glBufferData(gl.GL_ARRAY_BUFFER, data.data.nbytes, data.data, data.mode)
        self.m_allocated = True
        self.m_indicesCount = data.size

    def remove_vao(self):
        gl.glDeleteBuffers(1, [self.m_buffer])
        gl.glDeleteVertexArrays(1, [self.m_id])

    def get_buffer_id(self, index=0):
        return self.m_buffer

    def map_buffer(self, index=0, access_mode=gl.GL_READ_WRITE):
        gl.glBindBuffer(gl.GL_ARRAY_BUFFER, self.m_buffer)
        return gl.glMapBuffer(gl.GL_ARRAY_BUFFER, access_mode)
