import ctypes

import OpenGL.GL as gl

from .mat2 import Mat2
from .mat3 import Mat3
from .mat4 import Mat4
from .shader import Shader
from .vec2 import Vec2
from .vec3 import Vec3
from .vec4 import Vec4


class ShaderProgram:
    def __init__(self, name: str, exit_on_error: bool = True):
        self._name = name
        self._exit_on_error = exit_on_error
        self._id = gl.glCreateProgram()
        self._shaders = []
        self._uniforms = {}

    def attach_shader(self, shader: Shader):
        gl.glAttachShader(self._id, shader._id)
        self._shaders.append(shader)

    def link(self) -> bool:
        gl.glLinkProgram(self._id)
        if gl.glGetProgramiv(self._id, gl.GL_LINK_STATUS) != gl.GL_TRUE:
            info = gl.glGetProgramInfoLog(self._id)
            print(f"Error linking program {self._name}: {info}")
            if self._exit_on_error:
                exit()
            return False
        return True

    def use(self):
        gl.glUseProgram(self._id)

    def get_id(self) -> int:
        return self._id

    def get_uniform_location(self, name: str) -> int:
        if name not in self._uniforms:
            self._uniforms[name] = gl.glGetUniformLocation(self._id, name)
        return self._uniforms[name]

    def set_uniform(self, name: str, *value):
        loc = self.get_uniform_location(name)
        if loc == -1:
            return
        if len(value) == 1:
            val = value[0]
            if isinstance(val, int):
                gl.glUniform1i(loc, val)
            elif isinstance(val, float):
                gl.glUniform1f(loc, val)
            elif isinstance(val, Mat2):
                gl.glUniformMatrix2fv(loc, 1, gl.GL_FALSE, (ctypes.c_float * 4)(*val.get_matrix()))
            elif isinstance(val, Mat3):
                gl.glUniformMatrix3fv(loc, 1, gl.GL_FALSE, (ctypes.c_float * 9)(*val.get_matrix()))
            elif isinstance(val, Mat4):
                gl.glUniformMatrix4fv(loc, 1, gl.GL_FALSE, (ctypes.c_float * 16)(*val.get_matrix()))
            elif isinstance(val, Vec2):
                gl.glUniform2f(loc, *val)
            elif isinstance(val, Vec3):
                gl.glUniform3f(loc, *val)
            elif isinstance(val, Vec4):
                gl.glUniform4f(loc, *val)
            else:
                try:
                    val = list(value[0])
                    if len(val) == 4:
                        gl.glUniformMatrix2fv(loc, 1, gl.GL_FALSE, (ctypes.c_float * 4)(*val))
                    elif len(val) == 9:
                        gl.glUniformMatrix3fv(loc, 1, gl.GL_FALSE, (ctypes.c_float * 9)(*val))
                    elif len(val) == 16:
                        print("setting matrix4fv")
                        gl.glUniformMatrix4fv(loc, 1, gl.GL_FALSE, (ctypes.c_float * 16)(*val))
                except TypeError:
                    print(f"Warning: uniform '{name}' has unknown type: {type(val)}")
                    pass

        elif len(value) == 2:
            gl.glUniform2f(loc, *value)
        elif len(value) == 3:
            gl.glUniform3f(loc, *value)
        elif len(value) == 4:
            gl.glUniform4f(loc, *value)

    def get_uniform_1f(self, name: str) -> float:
        loc = self.get_uniform_location(name)
        if loc != -1:
            result = (ctypes.c_float * 1)()
            gl.glGetUniformfv(self._id, loc, result)
            return result[0]
        return 0.0

    def get_uniform_2f(self, name: str) -> list[float]:
        loc = self.get_uniform_location(name)
        if loc != -1:
            result = (ctypes.c_float * 2)()
            gl.glGetUniformfv(self._id, loc, result)
            return list(result)
        return [0.0, 0.0]

    def get_uniform_3f(self, name: str) -> list[float]:
        loc = self.get_uniform_location(name)
        if loc != -1:
            result = (ctypes.c_float * 3)()
            gl.glGetUniformfv(self._id, loc, result)
            return list(result)
        return [0.0, 0.0, 0.0]

    def get_uniform_4f(self, name: str) -> list[float]:
        loc = self.get_uniform_location(name)
        if loc != -1:
            result = (ctypes.c_float * 4)()
            gl.glGetUniformfv(self._id, loc, result)
            return list(result)
        return [0.0, 0.0, 0.0, 0.0]

    def get_uniform_mat2(self, name: str) -> list[float]:
        loc = self.get_uniform_location(name)
        if loc != -1:
            result = (ctypes.c_float * 4)()
            gl.glGetUniformfv(self._id, loc, result)
            return list(result)
        return [0.0] * 4

    def get_uniform_mat3(self, name: str) -> list[float]:
        loc = self.get_uniform_location(name)
        if loc != -1:
            result = (ctypes.c_float * 9)()
            gl.glGetUniformfv(self._id, loc, result)
            return list(result)
        return [0.0] * 9

    def get_uniform_mat4(self, name: str) -> list[float]:
        loc = self.get_uniform_location(name)
        if loc != -1:
            result = (ctypes.c_float * 16)()
            gl.glGetUniformfv(self._id, loc, result)
            return list(result)
        return [0.0] * 16
