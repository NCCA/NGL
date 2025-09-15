import glfw
import pytest
from OpenGL.GL import *

from ngl import IndexVertexData, ShaderLib, VAOFactory, VertexData


@pytest.fixture(scope="session")
def opengl_context():
    if not glfw.init():
        pytest.skip("Failed to initialize GLFW")

    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 4)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 1)
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)
    glfw.window_hint(glfw.OPENGL_FORWARD_COMPAT, GL_FALSE)
    glfw.window_hint(glfw.VISIBLE, glfw.FALSE)
    window = glfw.create_window(100, 100, "Test", None, None)

    if not window:
        glfw.terminate()
        pytest.skip("Failed to create GLFW window")

    glfw.make_context_current(window)
    ShaderLib.load_shader("test", "tests/files/vert.glsl", "tests/files/frag.glsl")
    ShaderLib.use("test")
    yield

    glfw.terminate()


def test_vao_factory(opengl_context):
    for vao_type in ["simpleVAO", "multiBufferVAO", "simpleIndexVAO"]:
        vao = VAOFactory.create_vao(vao_type, GL_TRIANGLES)
        assert vao is not None

    with pytest.raises(ValueError):
        VAOFactory.create_vao("nonExistentVAO", GL_TRIANGLES)


def test_simple_vao(opengl_context):
    vertices = [-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0]
    vao = VAOFactory.create_vao("simpleVAO", GL_TRIANGLES)
    vao.bind()
    data = VertexData(data=vertices, size=len(vertices) // 3)
    vao.set_data(data)
    vao.set_vertex_attribute_pointer(0, 3, GL_FLOAT, 0, 0)
    vao.draw()
    vao.unbind()
    assert vao.get_id() != 0
    assert vao.get_buffer_id() != 0
    vao.remove_vao()


def test_multi_buffer_vao(opengl_context):
    verts = [-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0]
    colors = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
    vao = VAOFactory.create_vao("multiBufferVAO", GL_TRIANGLES)
    vao.bind()
    vert_data = VertexData(data=verts, size=len(verts) // 3)
    vao.set_data(vert_data, 0)
    vao.set_vertex_attribute_pointer(0, 3, GL_FLOAT, 0, 0)
    color_data = VertexData(data=colors, size=len(colors) // 3)
    vao.set_data(color_data, 1)
    vao.set_vertex_attribute_pointer(1, 3, GL_FLOAT, 0, 0)
    vao.draw()
    vao.unbind()
    assert vao.get_buffer_id(0) != 0
    assert vao.get_buffer_id(1) != 0
    vao.remove_vao()


def test_simple_index_vao(opengl_context):
    vertices = [-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0]
    indices = [0, 1, 2]
    vao = VAOFactory.create_vao("simpleIndexVAO", GL_TRIANGLES)
    vao.bind()
    data = IndexVertexData(data=vertices, size=len(vertices) // 3, indices=indices, index_type=GL_UNSIGNED_INT)
    vao.set_data(data)
    vao.set_vertex_attribute_pointer(0, 3, GL_FLOAT, 0, 0)
    vao.draw()
    vao.unbind()
    assert vao.get_id() != 0
    assert vao.get_buffer_id() != 0
    vao.remove_vao()
