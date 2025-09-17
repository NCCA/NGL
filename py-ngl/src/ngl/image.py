from __future__ import annotations

import logging
from enum import Enum

import numpy as np
from PIL import Image as PILImage

logger = logging.getLogger(__name__)


class ImageModes(Enum):
    RGB = "RGB"
    RGBA = "RGBA"


class Image:
    def __init__(
        self,
        filename: str = None,
        width: int = 0,
        height: int = 0,
        mode: ImageModes = None,
    ):
        logger.debug(f"Creating Image from file {filename} or {width}x{height}")
        if filename:
            self.load(filename)
        else:
            self._width = width
            self._height = height
            self._mode = mode
            if mode:
                self._data = np.zeros((height, width, len(mode.value)), dtype=np.uint8)
            else:
                self._data = None

    def set_pixel(self, x, y, r, g, b, a=255):
        if x < 0 or x >= self._width or y < 0 or y >= self._height:
            raise ValueError("Pixel coordinates out of bounds")
        if self._mode == ImageModes.RGBA:
            self._data[y, x] = [r, g, b, a]
        else:
            self._data[y, x] = [r, g, b]

    def load(self, filename: str) -> bool:
        try:
            with PILImage.open(filename) as img:
                self._width = img.width
                self._height = img.height
                self._mode = ImageModes(img.mode)
                self._data = np.array(img)
            return True
        except Exception as e:
            logger.error(f"Error loading image {filename}: {e}")
            return False

    def save(self, filename: str) -> bool:
        try:
            img = PILImage.fromarray(self._data).convert(self._mode.value)
            img.save(filename)
            return True
        except Exception as e:
            logger.error(f"Error saving image {filename}: {e}")
            return False

    @property
    def width(self) -> int:
        return self._width

    @property
    def height(self) -> int:
        return self._height

    @property
    def mode(self) -> ImageModes:
        return self._mode

    def get_pixels(self) -> np.ndarray:
        return self._data
