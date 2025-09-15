from __future__ import annotations

from pathlib import Path

import OpenGL.GL as gl

from .shader import Shader, ShaderProgram, ShaderType


class _ShaderLib:
    def __init__(self):
        self._shader_programs = {}
        self._shaders = {}
        self._current_shader = None
        self._default_shaders_loaded = False

    def load_shader(
        self,
        name: str,
        vert: str,
        frag: str,
        geo: str = None,
        exit_on_error: bool = True,
    ) -> bool:
        program = ShaderProgram(name, exit_on_error)

        vert_shader = Shader(f"{name}Vertex", ShaderType.VERTEX.value, exit_on_error)
        vert_shader.load(vert)
        if not vert_shader.compile():
            return False

        frag_shader = Shader(f"{name}Fragment", ShaderType.FRAGMENT.value, exit_on_error)
        frag_shader.load(frag)
        if not frag_shader.compile():
            return False

        program.attach_shader(vert_shader)
        program.attach_shader(frag_shader)

        if geo:
            geo_shader = Shader(f"{name}Geometry", ShaderType.GEOMETRY.value, exit_on_error)
            geo_shader.load(geo)
            if not geo_shader.compile():
                return False
            program.attach_shader(geo_shader)

        if not program.link():
            return False

        self._shader_programs[name] = program
        return True

    def use(self, name: str):
        if not self._default_shaders_loaded:
            self._load_default_shaders()
        if name in self._shader_programs:
            self._shader_programs[name].use()
            self._current_shader = name
        else:
            print(f"Shader '{name}' not found")
            gl.glUseProgram(0)
            self._current_shader = None

    def get_current_shader_name(self) -> str | None:
        return self._current_shader

    def get_program_id(self, name: str) -> int | None:
        if name in self._shader_programs:
            return self._shader_programs[name].get_id()
        return None

    def create_shader_program(self, name: str, exit_on_error: bool = True):
        self._shader_programs[name] = ShaderProgram(name, exit_on_error)

    def attach_shader(self, name: str, type: ShaderType, exit_on_error: bool = True):
        self._shaders[name] = Shader(name, type.value, exit_on_error)

    def load_shader_source(self, name: str, source_file: str):
        if name in self._shaders:
            self._shaders[name].load(source_file)
        else:
            print(f"Error: shader {name} not found")

    def compile_shader(self, name: str) -> bool:
        if name in self._shaders:
            return self._shaders[name].compile()
        else:
            print(f"Error: shader {name} not found")
            return False

    def attach_shader_to_program(self, program_name: str, shader_name: str):
        if program_name in self._shader_programs and shader_name in self._shaders:
            self._shader_programs[program_name].attach_shader(self._shaders[shader_name])
        else:
            print(f"Error: program {program_name} or shader {shader_name} not found")

    def link_program_object(self, name: str) -> bool:
        if name in self._shader_programs:
            return self._shader_programs[name].link()
        else:
            print(f"Error: program {name} not found")
            return False

    def set_uniform(self, name: str, *value):
        if self._current_shader:
            self._shader_programs[self._current_shader].set_uniform(name, *value)

    def get_uniform_1f(self, name: str) -> float:
        if self._current_shader:
            return self._shader_programs[self._current_shader].get_uniform_1f(name)
        return 0.0

    def get_uniform_2f(self, name: str) -> list[float]:
        if self._current_shader:
            return self._shader_programs[self._current_shader].get_uniform_2f(name)
        return [0.0, 0.0]

    def get_uniform_3f(self, name: str) -> list[float]:
        if self._current_shader:
            return self._shader_programs[self._current_shader].get_uniform_3f(name)
        return [0.0, 0.0, 0.0]

    def get_uniform_4f(self, name: str) -> list[float]:
        if self._current_shader:
            return self._shader_programs[self._current_shader].get_uniform_4f(name)
        return [0.0, 0.0, 0.0, 0.0]

    def get_uniform_mat2(self, name: str) -> list[float]:
        if self._current_shader:
            return self._shader_programs[self._current_shader].get_uniform_mat2(name)
        return [0.0] * 4

    def get_uniform_mat3(self, name: str) -> list[float]:
        if self._current_shader:
            return self._shader_programs[self._current_shader].get_uniform_mat3(name)
        return [0.0] * 9

    def get_uniform_mat4(self, name: str) -> list[float]:
        if self._current_shader:
            print(self._shader_programs[self._current_shader].get_uniform_mat4(name))
            return self._shader_programs[self._current_shader].get_uniform_mat4(name)
        return [0.0] * 16

    def edit_shader(self, shader_name: str, to_find: str, replace_with: str) -> bool:
        if shader_name in self._shaders:
            return self._shaders[shader_name].edit_shader(to_find, replace_with)
        return False

    def reset_edits(self, shader_name: str):
        if shader_name in self._shaders:
            self._shaders[shader_name].reset_edits()

    def _load_default_shaders(self):
        shader_folder = Path(__file__).parent / "shaders"

        self.load_shader(
            "nglColourShader", shader_folder / "colour_vertex.glsl", shader_folder / "colour_fragment.glsl"
        )

    def _load_shader_source_from_string(self, shader_name: str, shader_source: str):
        self._shaders[shader_name].load_shader_source_from_string(shader_source)


# linkProgramObject("nglDiffuseShader");
# use("nglDiffuseShader");
# autoRegisterUniforms("nglDiffuseShader");
# use("NULL");


ShaderLib = _ShaderLib()
