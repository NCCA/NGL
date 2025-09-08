from __future__ import annotations

import ctypes
from enum import Enum

from OpenGL.GL import *


class ShaderType(Enum):
    VERTEX = GL_VERTEX_SHADER
    FRAGMENT = GL_FRAGMENT_SHADER
    GEOMETRY = GL_GEOMETRY_SHADER
    TESSCONTROL = GL_TESS_CONTROL_SHADER
    TESSEVAL = GL_TESS_EVALUATION_SHADER
    COMPUTE = GL_COMPUTE_SHADER
    NONE = -1


class MatrixTranspose(Enum):
    TransposeOn = GL_TRUE
    TransposeOff = GL_FALSE


class Shader:
    def __init__(self, name: str, type: int, exit_on_error: bool = True):
        self._name = name
        self._type = type
        self._exit_on_error = exit_on_error
        self._id = glCreateShader(type)
        self._source = ""

    def load(self, source_file: str):
        with open(source_file, "r") as f:
            self._source = f.read()
        glShaderSource(self._id, self._source)

    def compile(self) -> bool:
        glCompileShader(self._id)
        if glGetShaderiv(self._id, GL_COMPILE_STATUS) != GL_TRUE:
            info = glGetShaderInfoLog(self._id)
            print(f"Error compiling shader {self._name}: {info}")
            if self._exit_on_error:
                exit()
            return False
        return True

    def edit_shader(self, to_find: str, replace_with: str) -> bool:
        if self._source:
            self._source = self._source.replace(to_find, replace_with)
            glShaderSource(self._id, self._source)
            return True
        return False

    def reset_edits(self):
        if self._source:
            glShaderSource(self._id, self._source)


class ShaderProgram:
    def __init__(self, name: str, exit_on_error: bool = True):
        self._name = name
        self._exit_on_error = exit_on_error
        self._id = glCreateProgram()
        self._shaders = []
        self._uniforms = {}

    def attach_shader(self, shader: Shader):
        glAttachShader(self._id, shader._id)
        self._shaders.append(shader)

    def link(self) -> bool:
        glLinkProgram(self._id)
        if glGetProgramiv(self._id, GL_LINK_STATUS) != GL_TRUE:
            info = glGetProgramInfoLog(self._id)
            print(f"Error linking program {self._name}: {info}")
            if self._exit_on_error:
                exit()
            return False
        return True

    def use(self):
        glUseProgram(self._id)

    def get_id(self) -> int:
        return self._id

    def get_uniform_location(self, name: str) -> int:
        if name not in self._uniforms:
            self._uniforms[name] = glGetUniformLocation(self._id, name)
        return self._uniforms[name]

    def set_uniform(self, name: str, *value):
        loc = self.get_uniform_location(name)
        if loc != -1:
            if len(value) == 1:
                if isinstance(value[0], int):
                    glUniform1i(loc, value[0])
                elif isinstance(value[0], float):
                    glUniform1f(loc, value[0])
                elif isinstance(value[0], (list, tuple)):
                    if len(value[0]) == 4:
                        glUniformMatrix2fv(loc, 1, GL_FALSE, (ctypes.c_float * 4)(*value[0]))
                    elif len(value[0]) == 9:
                        glUniformMatrix3fv(loc, 1, GL_FALSE, (ctypes.c_float * 9)(*value[0]))
                    elif len(value[0]) == 16:
                        glUniformMatrix4fv(loc, 1, GL_FALSE, (ctypes.c_float * 16)(*value[0]))
            elif len(value) == 2:
                glUniform2f(loc, *value)
            elif len(value) == 3:
                glUniform3f(loc, *value)
            elif len(value) == 4:
                glUniform4f(loc, *value)

    def get_uniform_1f(self, name: str) -> float:
        loc = self.get_uniform_location(name)
        if loc != -1:
            result = (ctypes.c_float * 1)()
            glGetUniformfv(self._id, loc, result)
            return result[0]
        return 0.0

    def get_uniform_2f(self, name: str) -> list[float]:
        loc = self.get_uniform_location(name)
        if loc != -1:
            result = (ctypes.c_float * 2)()
            glGetUniformfv(self._id, loc, result)
            return list(result)
        return [0.0, 0.0]

    def get_uniform_3f(self, name: str) -> list[float]:
        loc = self.get_uniform_location(name)
        if loc != -1:
            result = (ctypes.c_float * 3)()
            glGetUniformfv(self._id, loc, result)
            return list(result)
        return [0.0, 0.0, 0.0]

    def get_uniform_4f(self, name: str) -> list[float]:
        loc = self.get_uniform_location(name)
        if loc != -1:
            result = (ctypes.c_float * 4)()
            glGetUniformfv(self._id, loc, result)
            return list(result)
        return [0.0, 0.0, 0.0, 0.0]

    def get_uniform_mat2(self, name: str) -> list[float]:
        loc = self.get_uniform_location(name)
        if loc != -1:
            result = (ctypes.c_float * 4)()
            glGetUniformfv(self._id, loc, result)
            return list(result)
        return [0.0] * 4

    def get_uniform_mat3(self, name: str) -> list[float]:
        loc = self.get_uniform_location(name)
        if loc != -1:
            result = (ctypes.c_float * 9)()
            glGetUniformfv(self._id, loc, result)
            return list(result)
        return [0.0] * 9

    def get_uniform_mat4(self, name: str) -> list[float]:
        if loc != -1:
            result = (ctypes.c_float * 16)()
            glGetUniformfv(self._id, loc, result)
            return list(result)
        return [0.0] * 16
