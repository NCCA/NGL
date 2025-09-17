from __future__ import annotations

from enum import Enum

import OpenGL.GL as gl
from .log import logger


class ShaderType(Enum):
    VERTEX = gl.GL_VERTEX_SHADER
    FRAGMENT = gl.GL_FRAGMENT_SHADER
    GEOMETRY = gl.GL_GEOMETRY_SHADER
    TESSCONTROL = gl.GL_TESS_CONTROL_SHADER
    TESSEVAL = gl.GL_TESS_EVALUATION_SHADER
    COMPUTE = gl.GL_COMPUTE_SHADER
    NONE = -1


class MatrixTranspose(Enum):
    TransposeOn = gl.GL_TRUE
    TransposeOff = gl.GL_TRUE


class Shader:
    def __init__(self, name: str, type: int, exit_on_error: bool = True):
        self._name = name
        self._type = type
        self._exit_on_error = exit_on_error
        self._id = gl.glCreateShader(type)
        self._source = ""

    def load(self, source_file: str):
        with open(source_file, "r") as f:
            self._source = f.read()
        gl.glShaderSource(self._id, self._source)

    def compile(self) -> bool:
        gl.glCompileShader(self._id)
        if gl.glGetShaderiv(self._id, gl.GL_COMPILE_STATUS) != gl.GL_TRUE:
            info = gl.glGetShaderInfoLog(self._id)
            logger.error(f"Error compiling shader {self._name=}: {info=}")
            if self._exit_on_error:
                exit()
            return False
        return True

    def edit_shader(self, to_find: str, replace_with: str) -> bool:
        if self._source:
            self._source = self._source.replace(to_find, replace_with)
            gl.glShaderSource(self._id, self._source)
            return True
        return False

    def reset_edits(self):
        if self._source:
            gl.glShaderSource(self._id, self._source)

    def load_shader_source_from_string(self, shader_source: str):
        self._source = shader_source


# class ShaderProgram:
#     def __init__(self, name: str, exit_on_error: bool = True):
#         self._name = name
#         self._exit_on_error = exit_on_error
#         self._id = gl.glCreateProgram()
#         self._shaders = []
#         self._uniforms = {}

#     def attach_shader(self, shader: Shader):
#         gl.glAttachShader(self._id, shader._id)
#         self._shaders.append(shader)

#     def link(self) -> bool:
#         gl.glLinkProgram(self._id)
#         if gl.glGetProgramiv(self._id, gl.GL_LINK_STATUS) != gl.GL_TRUE:
#             info = gl.glGetProgramInfoLog(self._id)
#             print(f"Error linking program {self._name}: {info}")
#             if self._exit_on_error:
#                 exit()
#             return False
#         return True

#     def use(self):
#         gl.glUseProgram(self._id)

#     def get_id(self) -> int:
#         return self._id

#     def get_uniform_location(self, name: str) -> int:
#         if name not in self._uniforms:
#             self._uniforms[name] = gl.glGetUniformLocation(self._id, name)
#         return self._uniforms[name]

#     def set_uniform(self, name: str, *value):
#         loc = self.get_uniform_location(name)
#         if loc != -1:
#             if len(value) == 1:
#                 if isinstance(value[0], int):
#                     gl.glUniform1i(loc, value[0])
#                 elif isinstance(value[0], float):
#                     gl.glUniform1f(loc, value[0])
#                 else:
#                     try:
#                         val = list(value[0])
#                         if len(val) == 4:
#                             gl.glUniformMatrix2fv(loc, 1, gl.GL_TRUE, (ctypes.c_float * 4)(*val))
#                         elif len(val) == 9:
#                             gl.glUniformMatrix3fv(loc, 1, gl.GL_TRUE, (ctypes.c_float * 9)(*val))
#                         elif len(val) == 16:
#                             gl.glUniformMatrix4fv(loc, 1, gl.GL_TRUE, (ctypes.c_float * 16)(*val))
#                     except TypeError:
#                         pass
#             elif len(value) == 2:
#                 gl.glUniform2f(loc, *value)
#             elif len(value) == 3:
#                 gl.glUniform3f(loc, *value)
#             elif len(value) == 4:
#                 gl.glUniform4f(loc, *value)

#     def get_uniform_1f(self, name: str) -> float:
#         loc = self.get_uniform_location(name)
#         if loc != -1:
#             result = (ctypes.c_float * 1)()
#             gl.glGetUniformfv(self._id, loc, result)
#             return result[0]
#         return 0.0

#     def get_uniform_2f(self, name: str) -> list[float]:
#         loc = self.get_uniform_location(name)
#         if loc != -1:
#             result = (ctypes.c_float * 2)()
#             gl.glGetUniformfv(self._id, loc, result)
#             return list(result)
#         return [0.0, 0.0]

#     def get_uniform_3f(self, name: str) -> list[float]:
#         loc = self.get_uniform_location(name)
#         if loc != -1:
#             result = (ctypes.c_float * 3)()
#             gl.glGetUniformfv(self._id, loc, result)
#             return list(result)
#         return [0.0, 0.0, 0.0]

#     def get_uniform_4f(self, name: str) -> list[float]:
#         loc = self.get_uniform_location(name)
#         if loc != -1:
#             result = (ctypes.c_float * 4)()
#             gl.glGetUniformfv(self._id, loc, result)
#             return list(result)
#         return [0.0, 0.0, 0.0, 0.0]

#     def get_uniform_mat2(self, name: str) -> list[float]:
#         loc = self.get_uniform_location(name)
#         if loc != -1:
#             result = (ctypes.c_float * 4)()
#             gl.glGetUniformfv(self._id, loc, result)
#             return list(result)
#         return [0.0] * 4

#     def get_uniform_mat3(self, name: str) -> list[float]:
#         loc = self.get_uniform_location(name)
#         if loc != -1:
#             result = (ctypes.c_float * 9)()
#             gl.glGetUniformfv(self._id, loc, result)
#             return list(result)
#         return [0.0] * 9

#     def get_uniform_mat4(self, name: str) -> list[float]:
#         loc = self.get_uniform_location(name)
#         if loc != -1:
#             result = (ctypes.c_float * 16)()
#             gl.glGetUniformfv(self._id, loc, result)
#             return list(result)
#         return [0.0] * 16
