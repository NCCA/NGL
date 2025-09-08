import glfw
import pytest
from OpenGL.GL import *

from ngl import Image, ImageModes, Texture


@pytest.fixture(scope="session")
def opengl_context():
    if not glfw.init():
        pytest.skip("Failed to initialize GLFW")

    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 4)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 1)
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)
    glfw.window_hint(glfw.OPENGL_FORWARD_COMPAT, GL_FALSE)
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
    print(filename)
    t = Texture(str(filename))
    assert t.width == size
    assert t.height == size
    assert t.format == GL_RGB

    tex_id = t.set_texture_gl()
    assert tex_id != 0
    glDeleteTextures(1, [tex_id])


def test_load_rgba(opengl_context, tmp_path):
    size = 4
    img = Image(width=size, height=size, mode=ImageModes.RGBA)
    filename = tmp_path / "simpleRGBA.png"
    img.save(str(filename))

    t = Texture(str(filename))
    assert t.width == size
    assert t.height == size
    assert t.format == GL_RGBA

    tex_id = t.set_texture_gl()
    assert tex_id != 0
    glDeleteTextures(1, [tex_id])


def test_multi_texture(opengl_context, tmp_path):
    size = 4
    img = Image(width=size, height=size, mode=ImageModes.RGBA)
    filename = tmp_path / "simpleRGBA.png"
    img.save(str(filename))

    t = Texture(str(filename))
    t.set_multi_texture(1)
    tex_id = t.set_texture_gl()
    assert tex_id != 0
    active_texture = glGetIntegerv(GL_ACTIVE_TEXTURE)
    assert active_texture == GL_TEXTURE1
    glDeleteTextures(1, [tex_id])
