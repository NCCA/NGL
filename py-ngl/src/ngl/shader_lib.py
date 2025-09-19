from __future__ import annotations

import enum
from pathlib import Path

import OpenGL.GL as gl

from .log import logger
from .shader import Shader, ShaderType
from .shader_program import ShaderProgram


class DefaultShader(enum.Enum):
    COLOUR = "nglColourShader"
    TEXT = "nglTextShader"
    DIFFUSE = ("nglDiffuseShader",)
    CHECKER = "nglCheckerShader"


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
            logger.error(f"Failed to compile vertex shader for {name}")
            return False

        frag_shader = Shader(
            f"{name}Fragment", ShaderType.FRAGMENT.value, exit_on_error
        )
        frag_shader.load(frag)
        if not frag_shader.compile():
            logger.error(f"Failed to compile fragment shader for {name}")
            return False

        program.attach_shader(vert_shader)
        program.attach_shader(frag_shader)

        if geo:
            geo_shader = Shader(
                f"{name}Geometry", ShaderType.GEOMETRY.value, exit_on_error
            )
            geo_shader.load(geo)
            if not geo_shader.compile():
                logger.error(f"Failed to compile geometry shader for {name}")
                return False
            program.attach_shader(geo_shader)

        if not program.link():
            logger.error(f"Failed to link shader program for {name}")
            return False

        self._shader_programs[name] = program
        logger.info(f"Shader program '{name}' created")
        return True

    def use(self, name: str):
        # lazy load default shaders on request
        if not self._default_shaders_loaded and name not in self._shader_programs:
            logger.warning("Default shaders not loaded loading now")
            self._load_default_shaders()

        if name in self._shader_programs:
            self._shader_programs[name].use()
            self._current_shader = name
        else:
            logger.error(f"Shader '{name}' not found")
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
            logger.error(f"Error: shader {name} not found")

    def compile_shader(self, name: str) -> bool:
        if name in self._shaders:
            return self._shaders[name].compile()
        else:
            logger.error(f"Error: shader {name} not found")
            return False

    def attach_shader_to_program(self, program_name: str, shader_name: str):
        if program_name in self._shader_programs and shader_name in self._shaders:
            self._shader_programs[program_name].attach_shader(
                self._shaders[shader_name]
            )
        else:
            logger.error(
                f"Error: program {program_name} or shader {shader_name} not found"
            )

    def link_program_object(self, name: str) -> bool:
        if name in self._shader_programs:
            return self._shader_programs[name].link()
        else:
            logger.error(f"Error: program {name} not found")
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

        to_load = {
            DefaultShader.COLOUR: {
                "vertex": shader_folder / "colour_vertex.glsl",
                "fragment": shader_folder / "colour_fragment.glsl",
            },
            DefaultShader.TEXT: {
                "vertex": shader_folder / "text_vertex.glsl",
                "fragment": shader_folder / "text_fragment.glsl",
            },
            DefaultShader.DIFFUSE: {
                "vertex": shader_folder / "diffuse_vertex.glsl",
                "fragment": shader_folder / "diffuse_fragment.glsl",
            },
            DefaultShader.CHECKER: {
                "vertex": shader_folder / "checker_vertex.glsl",
                "fragment": shader_folder / "checker_fragment.glsl",
            },
        }

        for shader_name, shader_data in to_load.items():
            if self.load_shader(
                shader_name, shader_data["vertex"], shader_data["fragment"]
            ):
                logger.info(f"{shader_name} shader loaded successfully")

        self._default_shaders_loaded = True

    def print_registered_uniforms(self, shader_name: str = None):
        if shader_name is None:
            shader_name = self._current_shader

        if shader_name in self._shader_programs:
            self._shader_programs[shader_name].print_registered_uniforms()
        else:
            logger.error(f"Shader '{shader_name}' not found")

    def print_properties(self):
        if self._current_shader in self._shader_programs:
            logger.info(
                "_______________________________________________________________________________________________________________________"
            )
            logger.info(
                f"Printing Properties for ShaderProgram {self._current_shader} "
            )
            logger.info(
                "_______________________________________________________________________________________________________________________"
            )
            self._shader_programs[self._current_shader].print_properties()
            logger.info(
                "_______________________________________________________________________________________________________________________"
            )
        else:
            logger.warning(
                f"Warning no currently active shader to print properties for {self._current_shader} "
            )


ShaderLib = _ShaderLib()
