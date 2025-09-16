"""
A container for ngl.Vec3 objects that mimics some of the behavior of a std::vector
"""

import numpy as np

from .vec3 import Vec3


class Vec3Array:
    """
    A class to hold a list of Vec3 objects and perform operations on them.
    """

    def __init__(self, values=None):
        """
        Initializes the Vec3Array.

        Args:
            values (iterable, optional): An iterable of Vec3 objects. Defaults to None.
        """
        self._data = []
        if values is not None:
            for v in values:
                if not isinstance(v, Vec3):
                    raise TypeError("All elements must be of type Vec3")
                self._data.append(v)

    def __getitem__(self, index):
        """
        Get the Vec3 at the specified index.

        Args:
            index (int): The index of the element.

        Returns:
            Vec3: The Vec3 object at the given index.
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
        Append a Vec3 object to the array.

        Args:
            value (Vec3): The Vec3 object to append.
        """
        if not isinstance(value, Vec3):
            raise TypeError("Only Vec3 objects can be appended")
        self._data.append(value)

    def to_list(self):
        """
        Convert the array of Vec3 objects to a single flat list of floats.

        Returns:
            list: A list of x, y, z components concatenated.
        """
        return [comp for vec in self._data for comp in vec]

    def to_numpy(self):
        """
        Convert the array of Vec3 objects to a numpy array.

        Returns:
            numpy.ndarray: A numpy array of the vector data.
        """
        return np.array(self.to_list(), dtype=np.float32)

    def __repr__(self):
        return f"Vec3Array({self._data!r})"

    def __str__(self):
        return str(self._data)
