"""
Note opengl_context created once in conftest.py
"""

from ngl import ShaderLib

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
