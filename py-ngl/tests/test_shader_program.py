import glfw
import numpy as np
import OpenGL.GL as gl
import pytest

from ngl.shader_program import ShaderProgram


class MockShader:
    def __init__(self, source, type, compile_success=True):
        self.source = source
        self.type = type
        self.is_compiled = False
        self.shader_handle = gl.glCreateShader(type)
        self._compile_success = compile_success

    def compile(self):
        gl.glShaderSource(self.shader_handle, self.source)
        gl.glCompileShader(self.shader_handle)
        if gl.glGetShaderiv(self.shader_handle, gl.GL_COMPILE_STATUS) != gl.GL_TRUE:
            return False
        self.is_compiled = self._compile_success
        return self._compile_success


@pytest.fixture(scope="session")
def opengl_context():
    if not glfw.init():
        pytest.skip("Failed to initialize GLFW")

    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 4)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 1)
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)
    glfw.window_hint(glfw.OPENGL_FORWARD_COMPAT, gl.GL_FALSE)
    glfw.window_hint(glfw.VISIBLE, glfw.FALSE)
    window = glfw.create_window(100, 100, "Test", None, None)

    if not window:
        glfw.terminate()
        pytest.skip("Failed to create GLFW window")

    glfw.make_context_current(window)
    yield

    glfw.terminate()


VERTEX_SHADER = """
#version 410 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
"""

FRAGMENT_SHADER = """
#version 410 core
out vec4 FragColor;
uniform vec4 ourColor;
void main()
{
    FragColor = ourColor;
}
"""


def test_shader_program_creation(opengl_context):
    program = ShaderProgram("test_program")
    assert program.name == "test_program"
    assert program.program_id == 0
    assert not program.is_linked


def test_attach_and_link(opengl_context):
    program = ShaderProgram("test_program")
    vert_shader = MockShader(VERTEX_SHADER, gl.GL_VERTEX_SHADER)
    frag_shader = MockShader(FRAGMENT_SHADER, gl.GL_FRAGMENT_SHADER)
    program.attach_shader(vert_shader)
    program.attach_shader(frag_shader)
    assert program.link()
    assert program.is_linked
    assert program.program_id != 0


def test_link_failure(opengl_context):
    program = ShaderProgram("test_program")
    vert_shader = MockShader(VERTEX_SHADER, gl.GL_VERTEX_SHADER, compile_success=False)
    program.attach_shader(vert_shader)
    assert not program.link()
    assert not program.is_linked


def test_use_program(opengl_context):
    program = ShaderProgram("test_program")
    vert_shader = MockShader(VERTEX_SHADER, gl.GL_VERTEX_SHADER)
    frag_shader = MockShader(FRAGMENT_SHADER, gl.GL_FRAGMENT_SHADER)
    program.attach_shader(vert_shader)
    program.attach_shader(frag_shader)
    program.link()
    program.use()
    assert gl.glGetIntegerv(gl.GL_CURRENT_PROGRAM) == program.program_id


def test_uniforms(opengl_context):
    program = ShaderProgram("test_program")
    vert_shader = MockShader(VERTEX_SHADER, gl.GL_VERTEX_SHADER)
    frag_shader = MockShader(FRAGMENT_SHADER, gl.GL_FRAGMENT_SHADER)
    program.attach_shader(vert_shader)
    program.attach_shader(frag_shader)
    program.link()
    program.use()

    loc = program.get_uniform_location("ourColor")
    assert loc != -1

    program.set_uniform("ourColor", (0.5, 0.2, 0.8, 1.0))
    color = (gl.GLfloat * 4)()
    gl.glGetUniformfv(program.program_id, loc, color)
    assert np.allclose(list(color), [0.5, 0.2, 0.8, 1.0])
