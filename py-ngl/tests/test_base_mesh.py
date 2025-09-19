import OpenGL.GL as gl
import pytest

from ngl import Image, ImageModes, Texture
from ngl.base_mesh import BaseMesh, Face
from ngl.shader_lib import ShaderLib
from ngl.vec2 import Vec2
from ngl.vec3 import Vec3


def test_is_triangular():
    mesh = BaseMesh()
    face1 = Face()
    face1.vertex = [1, 2, 3]
    face2 = Face()
    face2.vertex = [4, 5, 6]
    mesh.faces = [face1, face2]
    assert mesh.is_triangular() is True


def test_is_not_triangular():
    mesh = BaseMesh()
    face1 = Face()
    face1.vertex = [1, 2, 3]
    face2 = Face()
    face2.vertex = [4, 5, 6, 7]
    mesh.faces = [face1, face2]
    assert mesh.is_triangular() is False


def test_calc_dimensions():
    mesh = BaseMesh()
    mesh.vertex = [
        Vec3(-1.0, -2.0, -3.0),
        Vec3(1.0, 2.0, 3.0),
        Vec3(0.0, 0.0, 0.0),
    ]
    mesh.calc_dimensions()
    assert mesh.min_x == -1.0
    assert mesh.max_x == 1.0
    assert mesh.min_y == -2.0
    assert mesh.max_y == 2.0
    assert mesh.min_z == -3.0
    assert mesh.max_z == 3.0


def test_empty_mesh_dimensions():
    mesh = BaseMesh()
    mesh.calc_dimensions()
    assert mesh.min_x == 0.0
    assert mesh.max_x == 0.0
    assert mesh.min_y == 0.0
    assert mesh.max_y == 0.0
    assert mesh.min_z == 0.0
    assert mesh.max_z == 0.0


def test_init_defaults():
    mesh = BaseMesh()
    assert mesh.vertex == []
    assert mesh.normals == []
    assert mesh.uv == []
    assert mesh.faces == []
    assert mesh.vao is None
    assert mesh.bbox is None
    assert mesh.min_x == 0.0
    assert mesh.max_x == 0.0
    assert mesh.min_y == 0.0
    assert mesh.max_y == 0.0
    assert mesh.min_z == 0.0
    assert mesh.max_z == 0.0
    assert mesh.texture_id == 0
    assert mesh.texture is False


def test_create_vao_non_triangular(opengl_context):
    mesh = BaseMesh()
    face1 = Face()
    face1.vertex = [1, 2, 3, 4]
    mesh.faces = [face1]
    with pytest.raises(RuntimeError):
        mesh.create_vao()


def test_create_vao(opengl_context):
    ShaderLib.load_shader(
        "nglColourShader",
        "src/ngl/shaders/colour_vertex.glsl",
        "src/ngl/shaders/colour_fragment.glsl",
    )
    ShaderLib.use("nglColourShader")
    mesh = BaseMesh()
    mesh.vertex = [
        Vec3(0.0, 0.5, 0.0),
        Vec3(-0.5, -0.5, 0.0),
        Vec3(0.5, -0.5, 0.0),
    ]
    mesh.normals = [
        Vec3(0.0, 0.0, 1.0),
        Vec3(0.0, 0.0, 1.0),
        Vec3(0.0, 0.0, 1.0),
    ]
    mesh.uv = [
        Vec2(0.5, 1.0),
        Vec2(0.0, 0.0),
        Vec2(1.0, 0.0),
    ]
    face = Face()
    face.vertex = [0, 1, 2]
    face.normal = [0, 1, 2]
    face.uv = [0, 1, 2]
    mesh.faces = [face]
    mesh.create_vao()
    assert mesh.vao is not None
    assert mesh.bbox is not None
    mesh.draw()


def test_create_vao_no_normal_no_uv(opengl_context):
    ShaderLib.load_shader(
        "nglColourShader",
        "src/ngl/shaders/colour_vertex.glsl",
        "src/ngl/shaders/colour_fragment.glsl",
    )
    ShaderLib.use("nglColourShader")
    mesh = BaseMesh()
    mesh.vertex = [
        Vec3(0.0, 0.5, 0.0),
        Vec3(-0.5, -0.5, 0.0),
        Vec3(0.5, -0.5, 0.0),
    ]

    face = Face()
    face.vertex = [0, 1, 2]
    mesh.faces = [face]
    mesh.create_vao()
    assert mesh.vao is not None
    assert mesh.bbox is not None
    mesh.draw()


def test_create_vao_no_uv(opengl_context):
    ShaderLib.load_shader(
        "nglColourShader",
        "src/ngl/shaders/colour_vertex.glsl",
        "src/ngl/shaders/colour_fragment.glsl",
    )
    ShaderLib.use("nglColourShader")
    mesh = BaseMesh()
    mesh.vertex = [
        Vec3(0.0, 0.5, 0.0),
        Vec3(-0.5, -0.5, 0.0),
        Vec3(0.5, -0.5, 0.0),
    ]
    mesh.normals = [
        Vec3(0.0, 0.0, 1.0),
        Vec3(0.0, 0.0, 1.0),
        Vec3(0.0, 0.0, 1.0),
    ]

    face = Face()
    face.vertex = [0, 1, 2]
    face.normal = [0, 1, 2]
    mesh.faces = [face]
    mesh.create_vao()
    assert mesh.vao is not None
    assert mesh.bbox is not None
    mesh.draw()


def test_create_vao_no_normal(opengl_context):
    ShaderLib.load_shader(
        "nglColourShader",
        "src/ngl/shaders/colour_vertex.glsl",
        "src/ngl/shaders/colour_fragment.glsl",
    )
    ShaderLib.use("nglColourShader")
    mesh = BaseMesh()
    mesh.vertex = [
        Vec3(0.0, 0.5, 0.0),
        Vec3(-0.5, -0.5, 0.0),
        Vec3(0.5, -0.5, 0.0),
    ]
    mesh.uv = [
        Vec2(0.5, 1.0),
        Vec2(0.0, 0.0),
        Vec2(1.0, 0.0),
    ]
    face = Face()
    face.vertex = [0, 1, 2]
    face.uv = [0, 1, 2]
    mesh.faces = [face]
    mesh.create_vao()
    assert mesh.vao is not None
    assert mesh.bbox is not None
    mesh.draw()


def test_draw_no_vao(opengl_context):
    mesh = BaseMesh()
    mesh.draw()  # Should not raise


def test_create_vao_reset_vao(opengl_context):
    mesh = BaseMesh()
    mesh.vertex = [
        Vec3(0.0, 0.5, 0.0),
        Vec3(-0.5, -0.5, 0.0),
        Vec3(0.5, -0.5, 0.0),
    ]
    face = Face()
    face.vertex = [0, 1, 2]
    mesh.faces = [face]
    mesh.create_vao()
    assert mesh.vao is not None
    first_vao = mesh.vao
    mesh.create_vao(reset_vao=True)
    assert mesh.vao is first_vao
    mesh.create_vao(reset_vao=False)
    assert mesh.vao is not first_vao


def test_draw_with_texture(opengl_context, tmp_path):
    ShaderLib.load_shader(
        "nglColourShader",
        "src/ngl/shaders/colour_vertex.glsl",
        "src/ngl/shaders/colour_fragment.glsl",
    )
    ShaderLib.use("nglColourShader")
    mesh = BaseMesh()
    mesh.vertex = [
        Vec3(0.0, 0.5, 0.0),
        Vec3(-0.5, -0.5, 0.0),
        Vec3(0.5, -0.5, 0.0),
    ]
    face = Face()
    face.vertex = [0, 1, 2]
    mesh.faces = [face]
    mesh.create_vao()
    size = 2
    img = Image(width=size, height=size, mode=ImageModes.RGB)
    filename = tmp_path / "simpleRGB.png"
    img.save(str(filename))
    t = Texture(str(filename))
    mesh.texture_id = t.set_texture_gl()
    mesh.draw()
    gl.glDeleteTextures(1, [mesh.texture_id])
