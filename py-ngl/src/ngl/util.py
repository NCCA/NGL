"""Utility math module, contains various useful functions for 3D.

Most of these functions are based on functions found in other libraries such as GLM, NGL or GLU
"""

import math

from .mat4 import Mat4


def clamp(num, low, high):
    "clamp to range min and max will throw ValueError is low>=high"
    if low > high or low == high:
        raise ValueError
    return max(min(num, high), low)


def look_at(eye, look, up):
    """
    Calculate 4x4 matrix for camera lookAt
    """

    n = look - eye
    u = up
    v = n.cross(u)
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


def ortho(left, right, bottom, top, near, far):
    """Create an orthographic projection matrix."""
    m = Mat4.identity()
    m.m[0][0] = 2.0 / (right - left)
    m.m[1][1] = 2.0 / (top - bottom)
    m.m[2][2] = -2.0 / (far - near)
    m.m[3][0] = -(right + left) / (right - left)
    m.m[3][1] = -(top + bottom) / (top - bottom)
    m.m[3][2] = -(far + near) / (far - near)
    return m


# Mat4 result(1.0f);
#   result.m_00= 2.0f / (_right - _left);
#   result.m_11= 2.0f / (_top - _bottom);
#   result.m_22= - 2.0f / (_zFar - _zNear);
#   result.m_30= - (_right + _left) / (_right - _left);
#   result.m_31= - (_top + _bottom) / (_top - _bottom);
#   result.m_32= - (_zFar + _zNear) / (_zFar - _zNear);
#   return result;


def frustum(left, right, bottom, top, near, far):
    """Create a frustum projection matrix."""
    m = Mat4.zero()
    m.m[0][0] = (2.0 * near) / (right - left)
    m.m[1][1] = (2.0 * near) / (top - bottom)
    m.m[2][0] = (right + left) / (right - left)
    m.m[2][1] = (top + bottom) / (top - bottom)
    m.m[2][2] = -(far + near) / (far - near)
    m.m[2][3] = -1.0
    m.m[3][2] = -(2.0 * far * near) / (far - near)
    return m


def lerp(a, b, t):
    return a + (b - a) * t


def calc_normal(p1, p2, p3):
    """
    Calculates the normal of a triangle defined by three points.

    This is a Python implementation of the NGL C++ Util::calcNormal function.
    It uses the vector cross product method for clarity and leverages the py-ngl library.
    The order of the cross product is chosen to match the output of the C++ version.

    Args:
        p1: The first vertex of the triangle.
        p2: The second vertex of the triangle.
        p3: The third vertex of the triangle.

    Returns:
        The normalized normal vector of the triangle.
    """
    # Two vectors on the plane of the triangle
    v1 = p3 - p1
    v2 = p2 - p1

    # The cross product gives the normal vector.
    # The order (v1 x v2) is used to match the C++ implementation's result.
    normal = v1.cross(v2)

    # Normalize the result to get a unit length normal
    normal.normalize()

    return normal
