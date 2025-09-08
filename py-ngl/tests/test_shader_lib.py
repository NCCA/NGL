from ngl import shader_lib
from ngl.shader import ShaderType


def test_load_shader(tmp_path):
    vert_shader_source = "#version 410 core\nvoid main() { gl_Position = vec4(0.0); }"
    frag_shader_source = "#version 410 core\nout vec4 fragColor;\nvoid main() { fragColor = vec4(1.0); }"

    vert_file = tmp_path / "vert.glsl"
    frag_file = tmp_path / "frag.glsl"

    vert_file.write_text(vert_shader_source)
    frag_file.write_text(frag_shader_source)

    shader_lib.create_shader_program("Test")
    prog = shader_lib.get_program("Test")
    assert prog is not None
    assert prog.name == "Test"

    vert_shader = shader_lib.Shader("TestVertex", ShaderType.VERTEX)
    vert_shader.load(str(vert_file))
    prog.attach_shader(vert_shader)

    frag_shader = shader_lib.Shader("TestFragment", ShaderType.FRAGMENT)
    frag_shader.load(str(frag_file))
    prog.attach_shader(frag_shader)

    assert len(prog._shaders) == 2


def test_use():
    shader_lib.create_shader_program("TestUse")
    shader_lib.use("TestUse")
    assert shader_lib.get_current_shader() == "TestUse"
    shader_lib.use("NonExistent")
    assert shader_lib.get_current_shader() == ""


def test_reset():
    shader_lib.create_shader_program("TestReset")
    shader_lib.reset()
    assert shader_lib.get_program("TestReset") is None
