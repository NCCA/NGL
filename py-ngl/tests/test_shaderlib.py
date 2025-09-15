import glfw
import numpy as np
import OpenGL.GL as gl
import pytest

from ngl import Mat2, Mat3, Mat4, ShaderLib, ShaderType


@pytest.fixture(scope="session")
def opengl_context():
    if not glfw.init():
        pytest.skip("Failed to initialize GLFW")

    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 4)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 1)
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)
    glfw.window_hint(glfw.OPENGL_FORWARD_COMPAT, gl.GL_TRUE)
    glfw.window_hint(glfw.VISIBLE, glfw.FALSE)
    print("Initializing OpenGL context...")
    window = glfw.create_window(100, 100, "Test", None, None)

    if not window:
        glfw.terminate()
        pytest.skip("Failed to create GLFW window")

    glfw.make_context_current(window)
    print("OpenGL context initialized.")

    yield

    glfw.terminate()
    print("finished")


sourcedir = "tests/files/"


def test_load_shader(opengl_context):
    assert ShaderLib.load_shader(
        "Test",
        sourcedir + "vert.glsl",
        sourcedir + "frag.glsl",
    )


def test_use(opengl_context):
    ShaderLib.use("Test")
    assert ShaderLib.get_current_shader_name() == "Test"


def test_use_null(opengl_context):
    ShaderLib.use("unknown")
    assert ShaderLib.get_current_shader_name() is None


def test_load_error_shader(opengl_context):
    assert not ShaderLib.load_shader(
        "Test",
        sourcedir + "vertErr.glsl",
        sourcedir + "fragErr.glsl",
        exit_on_error=False,
    )


def test_load_parts(opengl_context):
    shader_name = "Test2"
    ShaderLib.create_shader_program(shader_name)
    vertex = "Test2Vert"
    ShaderLib.attach_shader(vertex, ShaderType.VERTEX)
    ShaderLib.load_shader_source(vertex, sourcedir + "vert.glsl")
    assert ShaderLib.compile_shader(vertex)

    fragment = "Test2Frag"
    ShaderLib.attach_shader(fragment, ShaderType.FRAGMENT)
    ShaderLib.load_shader_source(fragment, sourcedir + "frag.glsl")
    assert ShaderLib.compile_shader(fragment)

    ShaderLib.attach_shader_to_program(shader_name, vertex)
    ShaderLib.attach_shader_to_program(shader_name, fragment)

    assert ShaderLib.link_program_object(shader_name)
    ShaderLib.use(shader_name)
    assert ShaderLib.get_current_shader_name() == shader_name


def test_load_parts_fail_vertex(opengl_context):
    shader_name = "Test3"
    ShaderLib.create_shader_program(shader_name, exit_on_error=False)
    vertex = "Test3Vert"
    ShaderLib.attach_shader(vertex, ShaderType.VERTEX, exit_on_error=False)
    ShaderLib.load_shader_source(vertex, sourcedir + "vertErr.glsl")
    assert not ShaderLib.compile_shader(vertex)


def test_load_parts_fail_fragment(opengl_context):
    shader_name = "Test4"
    ShaderLib.create_shader_program(shader_name, exit_on_error=False)
    fragment = "Test4Frag"
    ShaderLib.attach_shader(fragment, ShaderType.FRAGMENT, exit_on_error=False)
    ShaderLib.load_shader_source(fragment, sourcedir + "fragErr.glsl")
    assert not ShaderLib.compile_shader(fragment)


def test_fail_link(opengl_context):
    shader_name = "Test5"
    ShaderLib.create_shader_program(shader_name, exit_on_error=False)
    vertex = "Test5Vert"
    ShaderLib.attach_shader(vertex, ShaderType.VERTEX, exit_on_error=False)
    ShaderLib.load_shader_source(vertex, sourcedir + "vertLinkErr.glsl")
    assert ShaderLib.compile_shader(vertex)
    fragment = "Test5Frag"
    ShaderLib.attach_shader(fragment, ShaderType.FRAGMENT, exit_on_error=False)
    ShaderLib.load_shader_source(fragment, sourcedir + "fragLinkErr.glsl")
    assert ShaderLib.compile_shader(fragment)
    ShaderLib.attach_shader_to_program(shader_name, vertex)
    ShaderLib.attach_shader_to_program(shader_name, fragment)
    assert not ShaderLib.link_program_object(shader_name)


def test_default_shader(opengl_context):
    ShaderLib.use("nglColourShader")


def test_set_uniform(opengl_context):
    shader_name = "TestUniform"
    assert ShaderLib.load_shader(
        shader_name,
        sourcedir + "testUniformVertex.glsl",
        sourcedir + "testUniformFragment.glsl",
        exit_on_error=False,
    )
    ShaderLib.use(shader_name)
    ShaderLib.set_uniform("testFloat", 2.25)
    result = ShaderLib.get_uniform_1f("testFloat")
    assert result == pytest.approx(2.25)

    ShaderLib.set_uniform("testVec2", 0.5, 2.0)
    result = ShaderLib.get_uniform_2f("testVec2")
    assert result[0] == pytest.approx(0.5)
    assert result[1] == pytest.approx(2.0)

    ShaderLib.set_uniform("testVec3", 0.5, 2.0, -22.2)
    result = ShaderLib.get_uniform_3f("testVec3")
    assert result[0] == pytest.approx(0.5)
    assert result[1] == pytest.approx(2.0)
    assert result[2] == pytest.approx(-22.2)

    ShaderLib.set_uniform("testVec4", 0.5, 2.0, -22.2, 1230.4)
    result = ShaderLib.get_uniform_4f("testVec4")
    assert result[0] == pytest.approx(0.5)
    assert result[1] == pytest.approx(2.0)
    assert result[2] == pytest.approx(-22.2)
    assert result[3] == pytest.approx(1230.4)

    mat = Mat2()
    ShaderLib.set_uniform("testMat2", mat.to_list())
    result = ShaderLib.get_uniform_mat2("testMat2")
    assert np.array_equal(result, mat.to_list())

    mat = Mat3()
    ShaderLib.set_uniform("testMat3", mat.to_list())
    result = ShaderLib.get_uniform_mat3("testMat3")
    print(result)
    print(mat)
    assert np.array_equal(result, mat.get_numpy())

    mat = Mat4()
    ShaderLib.set_uniform("testMat4", mat.to_list())
    result = ShaderLib.get_uniform_mat4("testMat4")
    assert np.array_equal(result, mat.to_list())


def test_edit_shader(opengl_context):
    shader_name = "Edit"
    ShaderLib.create_shader_program(shader_name, exit_on_error=False)
    vertex = "EditVert"
    ShaderLib.attach_shader(vertex, ShaderType.VERTEX, exit_on_error=False)
    ShaderLib.load_shader_source(vertex, sourcedir + "EditVert.glsl")
    assert ShaderLib.edit_shader(vertex, "@breakMe", "1.0")
    assert ShaderLib.edit_shader(vertex, "@numLights", "2")
    assert ShaderLib.compile_shader(vertex)
    fragment = "EditFrag"
    ShaderLib.attach_shader(fragment, ShaderType.FRAGMENT, exit_on_error=False)
    ShaderLib.load_shader_source(fragment, sourcedir + "EditFrag.glsl")
    assert ShaderLib.edit_shader(fragment, "@numLights", "2")
    assert ShaderLib.compile_shader(fragment)
    ShaderLib.attach_shader_to_program(shader_name, vertex)
    ShaderLib.attach_shader_to_program(shader_name, fragment)
    assert ShaderLib.link_program_object(shader_name)
    ShaderLib.use(shader_name)
    assert ShaderLib.get_current_shader_name() == shader_name
    # Now re-edit
    ShaderLib.reset_edits(vertex)
    ShaderLib.reset_edits(fragment)
    assert ShaderLib.edit_shader(vertex, "@numLights", "5")
    assert ShaderLib.edit_shader(vertex, "@breakMe", "1.0")
    assert ShaderLib.edit_shader(fragment, "@numLights", "5")
    assert ShaderLib.compile_shader(vertex)
    assert ShaderLib.compile_shader(fragment)
    assert ShaderLib.link_program_object(shader_name)
