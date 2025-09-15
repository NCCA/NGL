import OpenGL.GL as gl

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
        self._program_id = gl.glCreateProgram()
        for shader in self._shaders:
            if not shader.is_compiled:
                if not shader.compile():
                    return False
            gl.glAttachShader(self._program_id, shader.shader_handle)

        gl.glLinkProgram(self._program_id)
        if gl.glGetProgramiv(self._program_id, gl.GL_LINK_STATUS) != gl.GL_TRUE:
            info_log = gl.glGetProgramInfoLog(self._program_id)
            print(f"Error linking program {self._name}:\n{info_log}")
            return False
        self._linked = True
        return True

    def use(self) -> None:
        if self._linked:
            gl.glUseProgram(self._program_id)

    def get_uniform_location(self, name: str) -> int:
        return gl.glGetUniformLocation(self._program_id, name)

    def set_uniform(self, name: str, value) -> None:
        loc = self.get_uniform_location(name)

        if loc != -1:
            if isinstance(value, float):
                gl.glUniform1f(loc, value)
            elif isinstance(value, int):
                gl.glUniform1i(loc, value)
            elif isinstance(value, tuple):
                if len(value) == 2:
                    gl.glUniform2f(loc, *value)
                elif len(value) == 3:
                    gl.glUniform3f(loc, *value)
                elif len(value) == 4:
                    gl.glUniform4f(loc, *value)
            elif isinstance(value, list):
                if len(value) == 2:
                    gl.glUniform2fv(loc, 1, value)
                elif len(value) == 3:
                    gl.glUniform3fv(loc, 1, value)
                elif len(value) == 4:
                    gl.glUniform4fv(loc, 1, value)
                elif len(value) == 9:  # mat3
                    gl.glUniformMatrix3fv(loc, 1, gl.GL_TRUE, value)
                elif len(value) == 16:  # mat4
                    gl.glUniformMatrix4fv(loc, 1, gl.GL_TRUE, value)
