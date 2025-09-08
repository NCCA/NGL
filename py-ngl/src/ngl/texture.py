from __future__ import annotations

from OpenGL.GL import *

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
                return GL_RGB
            elif self._image.mode.value == "RGBA":
                return GL_RGBA
        return 0

    def load_image(self, filename: str) -> bool:
        return self._image.load(filename)

    def get_pixels(self) -> bytes:
        return self._image.get_pixels().tobytes()

    def set_texture_gl(self) -> int:
        if self._image.width > 0 and self._image.height > 0:
            self._texture_id = glGenTextures(1)
            glActiveTexture(GL_TEXTURE0 + self._multi_texture_id)
            glBindTexture(GL_TEXTURE_2D, self._texture_id)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                self.format,
                self.width,
                self.height,
                0,
                self.format,
                GL_UNSIGNED_BYTE,
                self.get_pixels(),
            )
            glGenerateMipmap(GL_TEXTURE_2D)
            return self._texture_id
        return 0

    def set_multi_texture(self, id: int) -> None:
        self._multi_texture_id = id
