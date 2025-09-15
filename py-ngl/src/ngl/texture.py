from __future__ import annotations

import OpenGL.GL as gl

from .image import Image


class Texture:
    """A texture class to load and create OpenGL textures."""

    def __init__(self, filename: str = None) -> None:
        self._image = Image(filename)
        self._texture_id = 0
        self._multi_texture_id = 0

    @property
    def width(self) -> int:
        return self._image.width

    @property
    def height(self) -> int:
        return self._image.height

    @property
    def format(self) -> int:
        if self._image.mode:
            if self._image.mode.value == "RGB":
                return gl.GL_RGB
            elif self._image.mode.value == "RGBA":
                return gl.GL_RGBA
        return 0

    def load_image(self, filename: str) -> bool:
        return self._image.load(filename)

    def get_pixels(self) -> bytes:
        return self._image.get_pixels().tobytes()

    def set_texture_gl(self) -> int:
        if self._image.width > 0 and self._image.height > 0:
            self._texture_id = gl.glGenTextures(1)
            gl.glActiveTexture(gl.GL_TEXTURE0 + self._multi_texture_id)
            gl.glBindTexture(gl.GL_TEXTURE_2D, self._texture_id)
            gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MAG_FILTER, gl.GL_LINEAR)
            gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MIN_FILTER, gl.GL_LINEAR)
            gl.glTexImage2D(
                gl.GL_TEXTURE_2D,
                0,
                self.format,
                self.width,
                self.height,
                0,
                self.format,
                gl.GL_UNSIGNED_BYTE,
                self.get_pixels(),
            )
            gl.glGenerateMipmap(gl.GL_TEXTURE_2D)
            return self._texture_id
        return 0

    def set_multi_texture(self, id: int) -> None:
        self._multi_texture_id = id
