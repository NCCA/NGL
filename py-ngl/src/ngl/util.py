"""Utility math module, contains various useful functions for 3D.

Most of these functions are based on functions found in other libraries such as GLM, NGL or GLU
"""

import math


def clamp(num, low, high):
    "clamp to range min and max will throw ValueError is low>=high"
    if low > high or low == high:
        raise ValueError
    return max(min(num, high), low)


def look_at(eye, look, up):
    """
    Calculate 4x4 matrix for camera lookAt
    """
    from .mat4 import Mat4

    n = look - eye
    v = n.cross(up)
    u = v.cross(n)
    n.normalize()
    v.normalize()
    u.normalize()
    result = Mat4.identity()
    result.m[0][0] = v.x
    result.m[1][0] = v.y
    result.m[2][0] = v.z
    result.m[0][1] = u.x
    result.m[1][1] = u.y
    result.m[2][1] = u.z
    result.m[0][2] = -n.x
    result.m[1][2] = -n.y
    result.m[2][2] = -n.z
    result.m[3][0] = -eye.dot(v)
    result.m[3][1] = -eye.dot(u)
    result.m[3][2] = eye.dot(n)
    return result


def perspective(fov, aspect, near, far):
    from .mat4 import Mat4

    m = Mat4.zero()  # as per glm
    _range = math.tan(math.radians(fov / 2.0)) * near
    left = -_range * aspect
    right = _range * aspect
    bottom = -_range
    top = _range
    m.m[0][0] = (2.0 * near) / (right - left)
    m.m[1][1] = (2.0 * near) / (top - bottom)
    m.m[2][2] = -(far + near) / (far - near)
    m.m[2][3] = -1.0
    m.m[3][2] = -(2.0 * far * near) / (far - near)
    return m


def lerp(a, b, t):
    return a + (b - a) * t
