"""
A container for ngl.Vec2 objects that mimics some of the behavior of a std::vector
"""

import numpy as np

from .vec2 import Vec2


class Vec2Array:
    """
    A class to hold a list of Vec2 objects and perform operations on them.
    """

    def __init__(self, values=None):
        """
        Initializes the Vec2Array.

        Args:
            values (iterable, optional): An iterable of Vec2 objects. Defaults to None.
        """
        self._data = []
        if values is not None:
            for v in values:
                if not isinstance(v, Vec2):
                    raise TypeError("All elements must be of type Vec2")
                self._data.append(v)

    def __getitem__(self, index):
        """
        Get the Vec2 at the specified index.

        Args:
            index (int): The index of the element.

        Returns:
            Vec2: The Vec2 object at the given index.
        """
        return self._data[index]

    def __len__(self):
        """
        Return the number of elements in the array.
        """
        return len(self._data)

    def __iter__(self):
        """
        Return an iterator for the array.
        """
        return iter(self._data)

    def append(self, value):
        """
        Append a Vec2 object to the array.

        Args:
            value (Vec2): The Vec2 object to append.
        """
        if not isinstance(value, Vec2):
            raise TypeError("Only Vec2 objects can be appended")
        self._data.append(value)

    def to_list(self):
        """
        Convert the array of Vec2 objects to a single flat list of floats.

        Returns:
            list: A list of x, y components concatenated.
        """
        return [comp for vec in self._data for comp in vec]

    def to_numpy(self):
        """
        Convert the array of Vec2 objects to a numpy array.

        Returns:
            numpy.ndarray: A numpy array of the vector data.
        """
        return np.array(self.to_list(), dtype=np.float32)

    def __repr__(self):
        return f"Vec2Array({self._data!r})"

    def __str__(self):
        return str(self._data)
