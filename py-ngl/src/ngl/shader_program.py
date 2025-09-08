from OpenGL.GL import *

from .shader import Shader


class ShaderProgram:
    """This class contains a single ShaderProgram."""

    def __init__(self, name: str) -> None:
        self._name = name
        self._program_id = 0
        self._shaders: list[Shader] = []
        self._linked = False

    @property
    def name(self) -> str:
        return self._name

    @property
    def program_id(self) -> int:
        return self._program_id

    @property
    def is_linked(self) -> bool:
        return self._linked

    def attach_shader(self, shader: Shader) -> None:
        self._shaders.append(shader)

    def link(self) -> bool:
        self._program_id = glCreateProgram()
        for shader in self._shaders:
            if not shader.is_compiled:
                if not shader.compile():
                    return False
            glAttachShader(self._program_id, shader.shader_handle)

        glLinkProgram(self._program_id)
        if glGetProgramiv(self._program_id, GL_LINK_STATUS) != GL_TRUE:
            info_log = glGetProgramInfoLog(self._program_id)
            print(f"Error linking program {self._name}:\n{info_log}")
            return False
        self._linked = True
        return True

    def use(self) -> None:
        if self._linked:
            glUseProgram(self._program_id)

    def get_uniform_location(self, name: str) -> int:
        return glGetUniformLocation(self._program_id, name)

    def set_uniform(self, name: str, value) -> None:
        loc = self.get_uniform_location(name)
        if loc != -1:
            # This is a simplified version. A complete implementation would handle different types.
            if isinstance(value, float):
                glUniform1f(loc, value)
            elif isinstance(value, int):
                glUniform1i(loc, value)
