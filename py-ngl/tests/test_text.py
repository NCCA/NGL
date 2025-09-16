"""
Note opengl_context created once in conftest.py
"""

from ngl.text import Text


def test_text_constructor(opengl_context):
    text = Text("tests/files/Arial.ttf", 20)
    assert text is not None
    text.set_screen_size(800, 600)
    assert text
