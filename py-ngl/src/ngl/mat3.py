import numpy as np


class Mat3:
    def __init__(self):
        self.m = np.identity(3).flatten().tolist()

    def to_list(self):
        return self.m
