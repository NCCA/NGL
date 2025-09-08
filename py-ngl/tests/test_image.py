import numpy as np

from ngl import Image, ImageModes


def test_default_ctor():
    img = Image()
    assert img.width == 0
    assert img.height == 0


def test_create_simple_image_rgba(tmp_path):
    size = 4
    img = Image(width=size, height=size, mode=ImageModes.RGBA)
    for x in range(size):
        img.set_pixel(x, 0, 255, 0, 0, 255)
        img.set_pixel(x, 1, 0, 255, 0, 255)
        img.set_pixel(x, 2, 0, 0, 255, 255)
        img.set_pixel(x, 3, 255, 255, 255, 255)

    filename = tmp_path / "simpleRGBA.png"
    assert img.save(str(filename))

    loaded_img = Image(str(filename))
    assert loaded_img.width == size
    assert loaded_img.height == size
    assert loaded_img.mode == ImageModes.RGBA

    pixels = loaded_img.get_pixels()
    assert np.array_equal(pixels[0, 0], [255, 0, 0, 255])
    assert np.array_equal(pixels[1, 0], [0, 255, 0, 255])
    assert np.array_equal(pixels[2, 0], [0, 0, 255, 255])
    assert np.array_equal(pixels[3, 0], [255, 255, 255, 255])


def test_create_simple_image_rgb(tmp_path):
    size = 4
    img = Image(width=size, height=size, mode=ImageModes.RGB)
    for x in range(size):
        img.set_pixel(x, 0, 255, 0, 0)
        img.set_pixel(x, 1, 0, 255, 0)
        img.set_pixel(x, 2, 0, 0, 255)
        img.set_pixel(x, 3, 255, 255, 255)

    filename = tmp_path / "simpleRGB.png"
    assert img.save(str(filename))

    loaded_img = Image(str(filename))
    assert loaded_img.width == size
    assert loaded_img.height == size
    assert loaded_img.mode == ImageModes.RGB

    pixels = loaded_img.get_pixels()
    assert np.array_equal(pixels[0, 0], [255, 0, 0])
    assert np.array_equal(pixels[1, 0], [0, 255, 0])
    assert np.array_equal(pixels[2, 0], [0, 0, 255])
    assert np.array_equal(pixels[3, 0], [255, 255, 255])
