import glfw
import OpenGL.GL as gl
import pytest

from ngl import ShaderLib


@pytest.fixture(scope="session")
def opengl_context():
    if not glfw.init():
        pytest.skip("Failed to initialize GLFW")

    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 4)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 1)
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)
    glfw.window_hint(glfw.OPENGL_FORWARD_COMPAT, gl.GL_TRUE)
    glfw.window_hint(glfw.VISIBLE, glfw.FALSE)
    window = glfw.create_window(100, 100, "Test", None, None)

    if not window:
        glfw.terminate()
        pytest.skip("Failed to create GLFW window")

    glfw.make_context_current(window)
    yield

    glfw.terminate()


sourcedir = "tests/files/"


def test_load_shader_with_geo(opengl_context):
    assert ShaderLib.load_shader(
        "TestGeo",
        sourcedir + "vert.glsl",
        sourcedir + "frag.glsl",
        sourcedir + "geom.glsl",
    )


def test_get_program_id_non_existent(opengl_context):
    assert ShaderLib.get_program_id("nonExistent") is None


def test_load_shader_source_non_existent(opengl_context):
    ShaderLib.load_shader_source("nonExistent", "dummy.glsl")


def test_compile_shader_non_existent(opengl_context):
    assert not ShaderLib.compile_shader("nonExistent")


def test_attach_shader_to_program_non_existent(opengl_context):
    ShaderLib.attach_shader_to_program("nonExistentProgram", "nonExistentShader")


def test_link_program_object_non_existent(opengl_context):
    assert not ShaderLib.link_program_object("nonExistent")


def test_get_uniforms_no_current_shader(opengl_context):
    ShaderLib.use(None)
    assert ShaderLib.get_uniform_1f("test") == 0.0
    assert ShaderLib.get_uniform_2f("test") == [0.0, 0.0]
    assert ShaderLib.get_uniform_3f("test") == [0.0, 0.0, 0.0]
    assert ShaderLib.get_uniform_4f("test") == [0.0, 0.0, 0.0, 0.0]
    assert ShaderLib.get_uniform_mat2("test") == [0.0] * 4
    assert ShaderLib.get_uniform_mat3("test") == [0.0] * 9
    assert ShaderLib.get_uniform_mat4("test") == [0.0] * 16
