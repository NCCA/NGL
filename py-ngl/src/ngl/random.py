"""
A module to replicate the functionality of the NGL C++ Random class.
"""

import random
import time

from ngl.vec2 import Vec2
from ngl.vec3 import Vec3
from ngl.vec4 import Vec4


class Random:
    _float_generators = {
        "RandomFloat": lambda: random.uniform(-1.0, 1.0),
        "RandomPositiveFloat": lambda: random.uniform(0.0, 1.0),
    }

    _int_generators = {}

    @staticmethod
    def set_seed():
        """set the seed using std::time(NULL)"""
        random.seed(int(time.time()))

    @staticmethod
    def set_seed_value(value: int):
        """set the seed using a param value
        Args:
            value (int): the seed value
        """
        random.seed(value)

    @staticmethod
    def get_float_from_generator_name(name: str) -> float:
        """gets a pre-generated float value for a genetator
        Args:
            name (str): the name of the generator to use for the number
        Returns:
            a random number created by the generator or 0 if the generator is not found
        """
        if name in Random._float_generators:
            return Random._float_generators[name]()
        return 0.0

    @staticmethod
    def get_int_from_generator_name(name: str) -> int:
        """gets a pre-generated int value for a genetator
        Args:
            name (str): the name of the generator to use for the number
        Returns:
            a random number created by the generator or 0 if the generator is not found
        """
        if name in Random._int_generators:
            return Random._int_generators[name]()
        return 0

    @staticmethod
    def add_int_generator(name: str, generator):
        """add a generator to the int generators
        Args:
            name (str): the name of the generator to use for the number
            generator : the generator to add should be a callable function
        """
        Random._int_generators[name] = generator

    @staticmethod
    def add_float_generator(name: str, generator):
        """add a generator to the float generators
        Args:
            name (str): the name of the generator to use for the number
            generator : the generator to add should be a callable function
        """
        Random._float_generators[name] = generator

    @staticmethod
    def get_random_vec4() -> Vec4:
        """get a random vector with componets ranged from +/- 1"""
        gen = Random._float_generators["RandomFloat"]
        return Vec4(gen(), gen(), gen(), 0.0)

    @staticmethod
    def get_random_colour4() -> Vec4:
        """get a random colour with components ranged from 0-1"""
        gen = Random._float_generators["RandomPositiveFloat"]
        return Vec4(gen(), gen(), gen(), 1.0)

    @staticmethod
    def get_random_colour3() -> Vec3:
        """get a random colour with components ranged from 0-1"""
        gen = Random._float_generators["RandomPositiveFloat"]
        return Vec3(gen(), gen(), gen())

    @staticmethod
    def get_random_normalized_vec4() -> Vec4:
        """get a random vector with componets ranged from +/- 1 and Normalized"""
        gen = Random._float_generators["RandomFloat"]
        v = Vec4(gen(), gen(), gen(), 0.0)
        v.normalize()
        return v

    @staticmethod
    def get_random_vec3() -> Vec3:
        """get a random vector with componets ranged from +/- 1"""
        gen = Random._float_generators["RandomFloat"]
        return Vec3(gen(), gen(), gen())

    @staticmethod
    def get_random_normalized_vec3() -> Vec3:
        """get a random vector with componets ranged from +/- 1 and Normalized"""
        gen = Random._float_generators["RandomFloat"]
        v = Vec3(gen(), gen(), gen())
        v.normalize()
        return v

    @staticmethod
    def get_random_vec2() -> Vec2:
        """get a random vector with componets ranged from +/- 1"""
        gen = Random._float_generators["RandomFloat"]
        return Vec2(gen(), gen())

    @staticmethod
    def get_random_normalized_vec2() -> Vec2:
        """get a random vector with componets ranged from +/- 1 and Normalized"""
        gen = Random._float_generators["RandomFloat"]
        v = Vec2(gen(), gen())
        v.normalize()
        return v

    @staticmethod
    def get_random_point(x_range: float = 1.0, y_range: float = 1.0, z_range: float = 1.0) -> Vec3:
        """get a random point in 3D space defaults to +/- 1 else user defined range
        Args:
            x_range (float): the +/-x range
            y_range (float): the +/-y range
            z_range (float): the +/-z range
        Returns:
            a random point
        """
        gen = Random._float_generators["RandomFloat"]
        return Vec3(gen() * x_range, gen() * y_range, gen() * z_range)

    @staticmethod
    def random_number(mult: float = 1.0) -> float:
        """a replacement for the old RandomNumber func
        this is basically a convinience function
        Args:
            mult (float): an optional multiplyer for the output
        Returns:
            (uniform_random(-1-0-+1) * mult)
        """
        gen = Random._float_generators["RandomFloat"]
        return gen() * mult

    @staticmethod
    def random_positive_number(mult: float = 1.0) -> float:
        """a replacement for the old ReandomPosNum
        this is basically a convinience function
        Args:
            mult (float): an optional multiplyer for the output
        Returns:
            (uniform_random(0-1) * mult)
        """
        gen = Random._float_generators["RandomPositiveFloat"]
        return gen() * mult
