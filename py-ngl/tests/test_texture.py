"""
Note opengl_context created once in conftest.py
"""

import OpenGL.GL as gl

from ngl import Image, ImageModes, Texture


def test_construct(opengl_context):
    t = Texture()
    assert t.width == 0
    assert t.height == 0
    assert t.format == 0


def test_load_rgb(opengl_context, tmp_path):
    size = 4
    img = Image(width=size, height=size, mode=ImageModes.RGB)
    filename = tmp_path / "simpleRGB.png"
    img.save(str(filename))
    t = Texture(str(filename))
    assert t.width == size
    assert t.height == size
    assert t.format == gl.GL_RGB

    tex_id = t.set_texture_gl()
    assert tex_id != 0
    gl.glDeleteTextures(1, [tex_id])


def test_load_rgba(opengl_context, tmp_path):
    size = 4
    img = Image(width=size, height=size, mode=ImageModes.RGBA)
    filename = tmp_path / "simpleRGBA.png"
    img.save(str(filename))

    t = Texture(str(filename))
    assert t.width == size
    assert t.height == size
    assert t.format == gl.GL_RGBA

    tex_id = t.set_texture_gl()
    assert tex_id != 0
    gl.glDeleteTextures(1, [tex_id])


def test_multi_texture(opengl_context, tmp_path):
    size = 4
    img = Image(width=size, height=size, mode=ImageModes.RGBA)
    filename = tmp_path / "simpleRGBA.png"
    img.save(str(filename))

    t = Texture(str(filename))
    t.set_multi_texture(1)
    tex_id = t.set_texture_gl()
    assert tex_id != 0
    active_texture = gl.glGetIntegerv(gl.GL_ACTIVE_TEXTURE)
    assert active_texture == gl.GL_TEXTURE1
    gl.glDeleteTextures(1, [tex_id])
