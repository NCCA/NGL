import numpy as np


class Mat2:
    def __init__(self):
        self.m = np.identity(2).flatten().tolist()

    def to_list(self):
        return self.m
