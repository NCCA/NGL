import enum

from .multi_buffer_vao import MultiBufferVAO
from .simple_index_vao import SimpleIndexVAO
from .simple_vao import SimpleVAO
from .log import logger


class VAOType(enum.Enum):
    SIMPLE = "simpleVAO"
    MULTI_BUFFER = "multiBufferVAO"
    SIMPLE_INDEX = "simpleIndexVAO"


class VAOFactory:
    _creators = {}

    @staticmethod
    def register_vao_creator(name, creator_func):
        VAOFactory._creators[name] = creator_func

    @staticmethod
    def create_vao(name, mode):
        creator = VAOFactory._creators.get(name)
        if not creator:
            logger.warning(f"VAO type '{name}' not found.")
            raise ValueError(name)
        return creator(mode)


# pre-register the default VAO types
VAOFactory.register_vao_creator(VAOType.SIMPLE, SimpleVAO)
VAOFactory.register_vao_creator(VAOType.MULTI_BUFFER, MultiBufferVAO)
VAOFactory.register_vao_creator(VAOType.SIMPLE_INDEX, SimpleIndexVAO)
