"""
This is a python implementation of the C++ Text class from NGL
"""

import freetype
import numpy as np
import OpenGL.GL as gl

from .log import logger
from .shader_lib import DefaultShader, ShaderLib
from .simple_vao import VertexData
from .util import ortho
from .vao_factory import VAOFactory, VAOType
from .vec3 import Vec3


class Character(object):
    """simple class to hold character data for rendering"""

    def __init__(self, texture_id, sizex, sizey, bearingx, bearingy, advance):
        self.texture_id = texture_id
        self.sizex = sizex
        self.sizey = sizey
        self.bearingx = bearingx
        self.bearingy = bearingy
        self.advance = advance


class Text(object):
    def __init__(self, font_name: str, size: int):
        """
        ctor, requires a font name and size
        """
        self.characters = {}
        face = freetype.Face(font_name)
        if not face:
            logger.error(f"Font '{font_name}' not found")
            raise ValueError(f"Font '{font_name}' not found")
        face.set_pixel_sizes(0, size)
        # disable byte-alignment restriction
        gl.glPixelStorei(gl.GL_UNPACK_ALIGNMENT, 1)
        for i in range(0, 128):
            face.load_char(chr(i), freetype.FT_LOAD_RENDER)
            # # now we create the OpenGL texture ID and bind to make it active
            # texture_id = gl.glGenTextures(1)
            # gl.glActiveTexture(gl.GL_TEXTURE0)

            # gl.glBindTexture(gl.GL_TEXTURE_2D, texture_id)
            # # set texture options
            # gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_WRAP_S, gl.GL_CLAMP_TO_EDGE)
            # gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_WRAP_T, gl.GL_CLAMP_TO_EDGE)
            # gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MIN_FILTER, gl.GL_LINEAR)
            # gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MAG_FILTER, gl.GL_LINEAR)

            # # fmt: off
            # gl.glTexImage2D(
            #     gl.GL_TEXTURE_2D,0,gl.GL_R8,
            #     face.glyph.bitmap.width,face.glyph.bitmap.rows, 0,
            #     gl.GL_RED, gl.GL_UNSIGNED_BYTE,bytes(face.glyph.bitmap.buffer))
            # fmt: on
            # generate and bind texture
            texture_id = gl.glGenTextures(1)
            gl.glBindTexture(gl.GL_TEXTURE_2D, texture_id)

            # upload glyph bitmap as single channel texture
            gl.glTexImage2D(
                gl.GL_TEXTURE_2D,
                0,
                gl.GL_RED,  # internal format (driver accepts it on macOS, though not spec-legal)
                face.glyph.bitmap.width,
                face.glyph.bitmap.rows,
                0,
                gl.GL_RED,  # external format (matches buffer)
                gl.GL_UNSIGNED_BYTE,
                face.glyph.bitmap.buffer,  # FreeType buffer is already bytes-like
            )

            # set texture options
            gl.glTexParameteri(
                gl.GL_TEXTURE_2D, gl.GL_TEXTURE_WRAP_S, gl.GL_CLAMP_TO_EDGE
            )
            gl.glTexParameteri(
                gl.GL_TEXTURE_2D, gl.GL_TEXTURE_WRAP_T, gl.GL_CLAMP_TO_EDGE
            )
            gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MIN_FILTER, gl.GL_LINEAR)
            gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MAG_FILTER, gl.GL_LINEAR)
            char = Character(
                texture_id,
                face.glyph.bitmap.width,
                face.glyph.bitmap.rows,
                face.glyph.bitmap_left,
                face.glyph.bitmap_top,
                face.glyph.advance.x,
            )
            self.characters[chr(i)] = char

        gl.glPixelStorei(gl.GL_UNPACK_ALIGNMENT, 4)
        self.set_colour(0.0, 0.0, 0.0)
        self.vao = VAOFactory.create_vao(VAOType.SIMPLE, gl.GL_TRIANGLES)
        ShaderLib.use(DefaultShader.TEXT)
        ShaderLib.set_uniform("text", 0)

    def __del__(self):
        for _, font in self.characters.items():
            gl.glDeleteTextures(1, font.texture_id)

    def render_text(self, x: float, y: float, text: str):
        """
        renders the text string at screen coordinates x,y
        """
        ShaderLib.use(DefaultShader.TEXT)

        gl.glActiveTexture(gl.GL_TEXTURE0)
        gl.glEnable(gl.GL_BLEND)
        gl.glDisable(gl.GL_DEPTH_TEST)
        gl.glBlendFunc(gl.GL_SRC_ALPHA, gl.GL_ONE_MINUS_SRC_ALPHA)
        gl.glEnable(gl.GL_CULL_FACE)
        scale = 1.0
        try:
            with self.vao:
                for char in text:
                    fc = self.characters[char]
                    xpos = x + fc.bearingx * scale
                    ypos = y - (fc.sizey - fc.bearingy) * scale
                    w = fc.sizex * scale
                    h = fc.sizey * scale
                    # fmt: off
                    vertices = np.array(
                    [
                        xpos, ypos + h, 0.0, 0.0,
                        xpos, ypos, 0.0, 1.0,
                        xpos + w, ypos, 1.0, 1.0,
                        xpos, ypos + h, 0.0, 0.0,
                        xpos + w, ypos, 1.0, 1.0,
                        xpos + w, ypos + h, 1.0, 0.0,
                    ], dtype=np.float32)
                    # fmt: on
                    gl.glActiveTexture(gl.GL_TEXTURE0)
                    gl.glBindTexture(gl.GL_TEXTURE_2D, fc.texture_id)
                    data = VertexData(
                        data=vertices,
                        size=len(vertices) // 4,
                        mode=gl.GL_DYNAMIC_DRAW,
                    )
                    self.vao.set_data(data)
                    self.vao.set_vertex_attribute_pointer(0, 4, gl.GL_FLOAT, 0, 0)
                    self.vao.set_num_indices(6)
                    self.vao.draw()
                    x += (fc.advance >> 6) * scale
        except Exception as e:
            print(f"Error rendering text: {e}")
        gl.glDisable(gl.GL_BLEND)
        gl.glEnable(gl.GL_DEPTH_TEST)
        gl.glDisable(gl.GL_CULL_FACE)

    def set_screen_size(self, w: int, h: int):
        """
        sets the screen size for the projection matrix
        """
        ShaderLib.use(DefaultShader.TEXT)
        ortho_proj = ortho(0, w, 0, h, 0.1, 100.0)
        print(f"{ortho_proj=}")
        ShaderLib.set_uniform("projection", ortho_proj)

    def set_colour(self, r, g, b):
        """
        sets the colour of the text
        """
        ShaderLib.use(DefaultShader.TEXT)
        ShaderLib.set_uniform("textColour", r, g, b)

    def set_colour_vec3(self, c: Vec3):
        """
        sets the colour of the text from a Vec3
        """
        ShaderLib.use(DefaultShader.TEXT)
        ShaderLib.set_uniform("textColour", c.x, c.y, c.z)
