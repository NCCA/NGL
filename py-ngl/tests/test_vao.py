"""
Note opengl_context created once in conftest.py
"""

import OpenGL.GL as gl
import pytest

from ngl import IndexVertexData, VAOFactory, VertexData


def test_vao_factory(opengl_context):
    for vao_type in ["simpleVAO", "multiBufferVAO", "simpleIndexVAO"]:
        vao = VAOFactory.create_vao(vao_type, gl.GL_TRIANGLES)
        assert vao is not None

    with pytest.raises(ValueError):
        VAOFactory.create_vao("nonExistentVAO", gl.GL_TRIANGLES)


def test_simple_vao(opengl_context):
    vertices = [-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0]
    vao = VAOFactory.create_vao("simpleVAO", gl.GL_TRIANGLES)
    vao.bind()
    data = VertexData(data=vertices, size=len(vertices) // 3)
    vao.set_data(data)
    vao.set_vertex_attribute_pointer(0, 3, gl.GL_FLOAT, 0, 0)
    vao.draw()
    vao.unbind()
    assert vao.get_id() != 0
    assert vao.get_buffer_id() != 0
    vao.remove_vao()


def test_multi_buffer_vao(opengl_context):
    verts = [-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0]
    colors = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
    vao = VAOFactory.create_vao("multiBufferVAO", gl.GL_TRIANGLES)
    vao.bind()
    vert_data = VertexData(data=verts, size=len(verts) // 3)
    vao.set_data(vert_data, 0)
    vao.set_vertex_attribute_pointer(0, 3, gl.GL_FLOAT, 0, 0)
    color_data = VertexData(data=colors, size=len(colors) // 3)
    vao.set_data(color_data, 1)
    vao.set_vertex_attribute_pointer(1, 3, gl.GL_FLOAT, 0, 0)
    vao.draw()
    vao.unbind()
    assert vao.get_buffer_id(0) != 0
    assert vao.get_buffer_id(1) != 0
    vao.remove_vao()


def test_simple_index_vao(opengl_context):
    vertices = [-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0]
    indices = [0, 1, 2]
    vao = VAOFactory.create_vao("simpleIndexVAO", gl.GL_TRIANGLES)
    vao.bind()
    data = IndexVertexData(
        data=vertices,
        size=len(vertices) // 3,
        indices=indices,
        index_type=gl.GL_UNSIGNED_INT,
    )
    vao.set_data(data)
    vao.set_vertex_attribute_pointer(0, 3, gl.GL_FLOAT, 0, 0)
    vao.draw()
    vao.unbind()
    assert vao.get_id() != 0
    assert vao.get_buffer_id() != 0
    vao.remove_vao()
