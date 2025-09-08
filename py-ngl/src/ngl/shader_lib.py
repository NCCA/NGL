from OpenGL.GL import *

from .shader import Shader, ShaderType
from .shader_program import ShaderProgram

_shader_programs: dict[str, ShaderProgram] = {}
_current_shader: str = ""


def create_shader_program(name: str) -> None:
    _shader_programs[name] = ShaderProgram(name)


def load_shader(shader_name: str, vert: str, frag: str) -> bool:
    create_shader_program(shader_name)
    vert_shader = Shader(f"{shader_name}Vertex", ShaderType.VERTEX)
    vert_shader.load(vert)
    frag_shader = Shader(f"{shader_name}Fragment", ShaderType.FRAGMENT)
    frag_shader.load(frag)
    prog = _shader_programs[shader_name]
    prog.attach_shader(vert_shader)
    prog.attach_shader(frag_shader)
    return prog.link()


def use(name: str) -> None:
    global _current_shader
    if name in _shader_programs:
        _shader_programs[name].use()
        _current_shader = name
    else:
        # In a real scenario, you might want to log a warning or raise an error.
        glUseProgram(0)
        _current_shader = ""


def get_program(name: str) -> ShaderProgram | None:
    return _shader_programs.get(name)


def get_current_shader() -> str:
    return _current_shader


def set_uniform(name: str, value) -> None:
    if _current_shader and _current_shader in _shader_programs:
        _shader_programs[_current_shader].set_uniform(name, value)


def reset() -> None:
    global _shader_programs, _current_shader
    _shader_programs = {}
    _current_shader = ""
