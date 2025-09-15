from .multi_buffer_vao import MultiBufferVAO
from .simple_index_vao import SimpleIndexVAO
from .simple_vao import SimpleVAO


class VAOFactory:
    _creators = {}

    @staticmethod
    def register_vao_creator(name, creator_func):
        VAOFactory._creators[name] = creator_func

    @staticmethod
    def create_vao(name, mode):
        creator = VAOFactory._creators.get(name)
        if not creator:
            raise ValueError(name)
        return creator(mode)


# pre-register the default VAO types
VAOFactory.register_vao_creator("simpleVAO", SimpleVAO)
VAOFactory.register_vao_creator("multiBufferVAO", MultiBufferVAO)
VAOFactory.register_vao_creator("simpleIndexVAO", SimpleIndexVAO)
