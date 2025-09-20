"""
OpenGL primitive generation and drawing functions
In this class we can generate a pipeline for drawing our data for the most part it will be
x,y,z nx,ny,nz and u,v data in a flat numpy array.
We need to create the data first which is stored in a map as part of the class, we can then call draw
which will generate a pipeline for this object and draw into the current context.
"""

import enum
from pathlib import Path

import numpy as np
import OpenGL.GL as gl

from .simple_vao import VertexData
from .vao_factory import VAOFactory, VAOType  # noqa


class Prims(enum.Enum):
    BUDDAH = "buddah"
    BUNNY = "bunny"
    CUBE = "cube"
    DODECAHEDRON = "dodecahedron"
    DRAGON = "dragon"
    FOOTBALL = "football"
    ICOSAHEDRON = "icosahedron"
    OCTAHEDRON = "octahedron"
    TEAPOT = "teapot"
    TETRAHEDRON = "tetrahedron"
    TROLL = "troll"


def _circle_table(n):
    # Determine the angle between samples
    angle = 2.0 * np.pi / (n if n != 0 else 1)

    # Allocate list for n samples, plus duplicate of first entry at the end
    cs = np.zeros((n + 1, 2), dtype=np.float32)

    # Compute cos and sin around the circle
    cs[0, 0] = 1.0  # cost
    cs[0, 1] = 0.0  # sint

    for i in range(1, n):
        cs[i, 1] = np.sin(angle * i)  # sint
        cs[i, 0] = np.cos(angle * i)  # cost

    # Last sample is duplicate of the first
    cs[n, 1] = cs[0, 1]  # sint
    cs[n, 0] = cs[0, 0]  # cost

    return cs


class _primitive:
    def __init__(self, prim_data):
        self.vao = VAOFactory.create_vao(VAOType.SIMPLE, gl.GL_TRIANGLES)
        with self.vao:
            data = VertexData(data=prim_data.data, size=prim_data.size)
            self.vao.set_data(data)
            vert_data_size = 8 * 4  # 4 is sizeof float and 8 is x,y,z,nx,ny,nz,uv
            print(vert_data_size)
            self.vao.set_vertex_attribute_pointer(0, 3, gl.GL_FLOAT, vert_data_size, 0)
            self.vao.set_vertex_attribute_pointer(1, 3, gl.GL_FLOAT, vert_data_size, 3 * 4)
            self.vao.set_vertex_attribute_pointer(2, 2, gl.GL_FLOAT, vert_data_size, 6 * 4)
            self.vao.set_num_indices(prim_data.size // 8)


class Primitives:
    # this is effectively a static class so we can use it to store data
    # and generate pipelines for drawing
    _primitives = {}
    _loaded = False

    @classmethod
    def load_default_primitives(cls):
        print("Loading default primitives...")
        if not cls._loaded:
            prim_folder = Path(__file__).parent / "PrimData"
            print("Loading default primitives...")
            prims = np.load(prim_folder / "Primitives.npz")
            for p in prims.items():
                prim_data = p[1]
                print(f"Loading {p[0]}...")
                prim = _primitive(prim_data)
                cls._primitives[p[0]] = prim
            cls._loaded = True

    @classmethod
    def create_line_grid(cls, name, width, depth, steps):
        # Calculate the step size for each grid value
        wstep = width / steps
        ws2 = width / 2.0
        v1 = -ws2

        dstep = depth / steps
        ds2 = depth / 2.0
        v2 = -ds2

        # Create a list to store the vertex data
        data = []

        for i in range(steps + 1):
            # Vertex 1 x, y, z
            data.append([-ws2, 0.0, v1])
            # Vertex 2 x, y, z
            data.append([ws2, 0.0, v1])

            # Vertex 1 x, y, z
            data.append([v2, 0.0, ds2])
            # Vertex 2 x, y, z
            data.append([v2, 0.0, -ds2])

            # Now change our step value
            v1 += wstep
            v2 += dstep

        # Convert the list to a NumPy array
        data_array = np.array(data, dtype=np.float32)
        prim = _primitive(data_array)
        cls._primitives[name] = prim

    @classmethod
    def create_triangle_plane(cls, name, width, depth, w_p, d_p, v_n):
        w2 = width / 2.0
        d2 = depth / 2.0
        w_step = width / w_p
        d_step = depth / d_p

        du = 0.9 / w_p
        dv = 0.9 / d_p

        data = []
        v = 0.0
        d = -d2
        for _ in range(d_p):
            u = 0.0
            w = -w2
            for _ in range(w_p):
                # tri 1
                # vert 1
                data.extend([w, 0.0, d + d_step, v_n.x, v_n.y, v_n.z, u, v + dv])
                # vert 2
                data.extend([w + w_step, 0.0, d + d_step, v_n.x, v_n.y, v_n.z, u + du, v + dv])
                # vert 3
                data.extend([w, 0.0, d, v_n.x, v_n.y, v_n.z, u, v])

                # tri 2
                # vert 1
                data.extend([w + w_step, 0.0, d + d_step, v_n.x, v_n.y, v_n.z, u + du, v + dv])
                # vert 2
                data.extend([w + w_step, 0.0, d, v_n.x, v_n.y, v_n.z, u + du, v])
                # vert 3
                data.extend([w, 0.0, d, v_n.x, v_n.y, v_n.z, u, v])
                u += du
                w += w_step
            v += dv
            d += d_step

        data_array = np.array(data, dtype=np.float32)
        prim = _primitive(data_array)
        cls._primitives[name] = prim

    @classmethod
    def draw(cls, name):
        key = name.value if isinstance(name, Prims) else name
        try:
            prim = cls._primitives[key]
            with prim.vao:
                prim.vao.draw()
        except KeyError:
            print(f"Primitive {key} not found")
            return

    @classmethod
    def create_sphere(cls, name, radius, precision):
        # Sphere code based on a function Written by Paul Bourke.
        # http://astronomy.swin.edu.au/~pbourke/opengl/sphere/
        # the next part of the code calculates the P,N,UV of the sphere for triangles

        # Disallow a negative number for radius.
        if radius < 0.0:
            radius = -radius

        # Disallow a negative number for precision.
        if precision < 4:
            precision = 4

        # Create a numpy array to store our verts
        data = []

        for i in range(precision // 2):
            theta1 = i * 2.0 * np.pi / precision - np.pi / 2.0
            theta2 = (i + 1) * 2.0 * np.pi / precision - np.pi / 2.0

            for j in range(precision):
                theta3 = j * 2.0 * np.pi / precision
                theta4 = (j + 1) * 2.0 * np.pi / precision

                # First triangle
                nx1 = np.cos(theta2) * np.cos(theta3)
                ny1 = np.sin(theta2)
                nz1 = np.cos(theta2) * np.sin(theta3)
                x1 = radius * nx1
                y1 = radius * ny1
                z1 = radius * nz1
                u1 = j / precision
                v1 = 2.0 * (i + 1) / precision
                data.append([x1, y1, z1, nx1, ny1, nz1, u1, v1])

                nx2 = np.cos(theta1) * np.cos(theta3)
                ny2 = np.sin(theta1)
                nz2 = np.cos(theta1) * np.sin(theta3)
                x2 = radius * nx2
                y2 = radius * ny2
                z2 = radius * nz2
                u2 = j / precision
                v2 = 2.0 * i / precision
                data.append([x2, y2, z2, nx2, ny2, nz2, u2, v2])

                nx3 = np.cos(theta1) * np.cos(theta4)
                ny3 = np.sin(theta1)
                nz3 = np.cos(theta1) * np.sin(theta4)
                x3 = radius * nx3
                y3 = radius * ny3
                z3 = radius * nz3
                u3 = (j + 1) / precision
                v3 = 2.0 * i / precision
                data.append([x3, y3, z3, nx3, ny3, nz3, u3, v3])

                # Second triangle
                nx4 = np.cos(theta2) * np.cos(theta4)
                ny4 = np.sin(theta2)
                nz4 = np.cos(theta2) * np.sin(theta4)
                x4 = radius * nx4
                y4 = radius * ny4
                z4 = radius * nz4
                u4 = (j + 1) / precision
                v4 = 2.0 * (i + 1) / precision
                data.append([x4, y4, z4, nx4, ny4, nz4, u4, v4])

                data.append([x1, y1, z1, nx1, ny1, nz1, u1, v1])
                data.append([x3, y3, z3, nx3, ny3, nz3, u3, v3])

        data_array = np.array(data, dtype=np.float32)
        prim = _primitive(data_array)
        cls._primitives[name] = prim

    @classmethod
    def create_cone(cls, name, base, height, slices, stacks):
        z_step = height / (stacks if stacks > 0 else 1)
        r_step = base / (stacks if stacks > 0 else 1)

        cosn = height / np.sqrt(height * height + base * base)
        sinn = base / np.sqrt(height * height + base * base)

        cs = _circle_table(slices)

        z0 = 0.0
        z1 = z_step

        r0 = base
        r1 = r0 - r_step

        du = 1.0 / stacks
        dv = 1.0 / slices

        u = 1.0
        v = 1.0

        data = []

        for i in range(stacks):
            for j in range(slices):
                # theta1 = j * 2.0 * np.pi / slices
                # theta2 = (j + 1) * 2.0 * np.pi / slices

                # First triangle
                d1 = [0] * 8
                d1[6] = u
                d1[7] = v
                d1[3] = cs[j, 0] * cosn  # nx
                d1[4] = cs[j, 1] * sinn  # ny
                d1[5] = sinn  # nz
                d1[0] = cs[j, 0] * r0  # x
                d1[1] = cs[j, 1] * r0  # y
                d1[2] = z0  # z
                data.append(d1)

                d2 = [0] * 8
                d2[6] = u
                d2[7] = v - dv
                d2[3] = cs[j, 0] * cosn  # nx
                d2[4] = cs[j, 1] * sinn  # ny
                d2[5] = sinn  # nz
                d2[0] = cs[j, 0] * r1  # x
                d2[1] = cs[j, 1] * r1  # y
                d2[2] = z1  # z
                data.append(d2)

                d3 = [0] * 8
                d3[6] = u - du
                d3[7] = v - dv
                d3[3] = cs[j + 1, 0] * cosn  # nx
                d3[4] = cs[j + 1, 1] * sinn  # ny
                d3[5] = sinn  # nz
                d3[0] = cs[j + 1, 0] * r1  # x
                d3[1] = cs[j + 1, 1] * r1  # y
                d3[2] = z1  # z
                data.append(d3)

                # Second triangle
                d4 = [0] * 8
                d4[6] = u
                d4[7] = v
                d4[3] = cs[j, 0] * cosn  # nx
                d4[4] = cs[j, 1] * sinn  # ny
                d4[5] = sinn  # nz
                d4[0] = cs[j, 0] * r0  # x
                d4[1] = cs[j, 1] * r0  # y
                d4[2] = z0  # z
                data.append(d4)

                d5 = [0] * 8
                d5[6] = u - du
                d5[7] = v - dv
                d5[3] = cs[j + 1, 0] * cosn  # nx
                d5[4] = cs[j + 1, 1] * sinn  # ny
                d5[5] = sinn  # nz
                d5[0] = cs[j + 1, 0] * r1  # x
                d5[1] = cs[j + 1, 1] * r1  # y
                d5[2] = z1  # z
                data.append(d5)

                d6 = [0] * 8
                d6[6] = u - du
                d6[7] = v
                d6[3] = cs[j + 1, 0] * cosn  # nx
                d6[4] = cs[j + 1, 1] * sinn  # ny
                d6[5] = sinn  # nz
                d6[0] = cs[j + 1, 0] * r0  # x
                d6[1] = cs[j + 1, 1] * r0  # y
                d6[2] = z0  # z
                data.append(d6)

                u -= du

            v -= dv
            u = 1.0
            z0 = z1
            z1 += z_step
            r0 = r1
            r1 -= r_step

        data_array = np.array(data, dtype=np.float32)

        data_array = np.array(data, dtype=np.float32)
        prim = _primitive(data_array)
        cls._primitives[name] = prim

    @classmethod
    def create_capsule(cls, name, radius, height, precision):
        """
        Creates a capsule primitive.
        The capsule is aligned along the y-axis.
        It is composed of a cylinder and two hemispherical caps.
        based on code from here https://code.google.com/p/rgine/source/browse/trunk/RGine/opengl/src/RGLShapes.cpp
        and adapted
        """
        if radius <= 0.0:
            raise ValueError("Radius must be positive")
        if height < 0.0:
            raise ValueError("Height must be non-negative")
        if precision < 4:
            precision = 4

        data = []
        h = height / 2.0
        ang = np.pi / precision

        for i in range(2 * precision):
            c = radius * np.cos(ang * i)
            c1 = radius * np.cos(ang * (i + 1))
            s = radius * np.sin(ang * i)
            s1 = radius * np.sin(ang * (i + 1))

            # normals for cylinder sides
            nc = np.cos(ang * i)
            ns = np.sin(ang * i)
            nc1 = np.cos(ang * (i + 1))
            ns1 = np.sin(ang * (i + 1))

            # side top
            # Vert 1
            data.extend([c1, h, s1, nc1, 0.0, ns1, 0.0, 0.0])
            # Vert 2
            data.extend([c, h, s, nc, 0.0, ns, 0.0, 0.0])
            # Vert 3
            data.extend([c, -h, s, nc, 0.0, ns, 0.0, 0.0])

            # side bot
            # Vert 1
            data.extend([c, -h, s, nc, 0.0, ns, 0.0, 0.0])
            # Vert 2
            data.extend([c1, -h, s1, nc1, 0.0, ns1, 0.0, 0.0])
            # Vert 3
            data.extend([c1, h, s1, nc1, 0.0, ns1, 0.0, 0.0])

        for i in range(2 * precision):
            # longitude
            s = -np.sin(ang * i)
            s1 = -np.sin(ang * (i + 1))
            c = np.cos(ang * i)
            c1 = np.cos(ang * (i + 1))

            for j in range(precision + 1):
                if j < precision / 2:
                    o = h
                else:
                    o = -h

                # latitude
                sb = radius * np.sin(ang * j)
                sb1 = radius * np.sin(ang * (j + 1))
                cb = radius * np.cos(ang * j)
                cb1 = radius * np.cos(ang * (j + 1))

                if j != precision - 1:
                    # Vert 1
                    nx = sb * c
                    ny = cb
                    nz = sb * s
                    data.extend([nx, ny + o, nz, nx, ny, nz, 0.0, 0.0])
                    # Vert 2
                    nx = sb1 * c
                    ny = cb1
                    nz = sb1 * s
                    data.extend([nx, ny + o, nz, nx, ny, nz, 0.0, 0.0])
                    # Vert 3
                    nx = sb1 * c1
                    ny = cb1
                    nz = sb1 * s1
                    data.extend([nx, ny + o, nz, nx, ny, nz, 0.0, 0.0])

                if j != 0:
                    # Vert 1
                    nx = sb * c
                    ny = cb
                    nz = sb * s
                    data.extend([nx, ny + o, nz, nx, ny, nz, 0.0, 0.0])
                    # Vert 2
                    nx = sb1 * c1
                    ny = cb1
                    nz = sb1 * s1
                    data.extend([nx, ny + o, nz, nx, ny, nz, 0.0, 0.0])
                    # Vert 3
                    nx = sb * c1
                    ny = cb
                    nz = sb * s1
                    data.extend([nx, ny + o, nz, nx, ny, nz, 0.0, 0.0])

        data_array = np.array(data, dtype=np.float32)
        prim = _primitive(data_array)
        cls._primitives[name] = prim

    @classmethod
    def create_cylinder(cls, name, radius, height, slices, stacks):
        """
        Creates a cylinder primitive.
        The cylinder is aligned along the y-axis.
        This method generates the cylinder walls, but not the top and bottom caps.
        """
        if radius <= 0.0:
            raise ValueError("Radius must be positive")
        if height < 0.0:
            raise ValueError("Height must be non-negative")
        if slices < 3:
            slices = 3
        if stacks < 1:
            stacks = 1

        data = []
        h2 = height / 2.0
        y_step = height / stacks

        cs = _circle_table(slices)

        du = 1.0 / slices
        dv = 1.0 / stacks

        for i in range(stacks):
            y0 = -h2 + i * y_step
            y1 = -h2 + (i + 1) * y_step
            v = i * dv
            for j in range(slices):
                u = j * du

                nx1 = cs[j, 0]  # cos
                nz1 = cs[j, 1]  # sin
                x1 = radius * nx1
                z1 = radius * nz1

                nx2 = cs[j + 1, 0]
                nz2 = cs[j + 1, 1]
                x2 = radius * nx2
                z2 = radius * nz2

                p_bl = [x1, y0, z1, nx1, 0, nz1, u, v]
                p_br = [x2, y0, z2, nx2, 0, nz2, u + du, v]
                p_tl = [x1, y1, z1, nx1, 0, nz1, u, v + dv]
                p_tr = [x2, y1, z2, nx2, 0, nz2, u + du, v + dv]

        data_array = np.array(data, dtype=np.float32)
        prim = _primitive(data_array)
        cls._primitives[name] = prim

    @classmethod
    def create_disk(cls, name, radius, slices):
        if radius <= 0.0:
            raise ValueError("Radius must be positive")
        if slices < 3:
            slices = 3

        data = []
        cs = _circle_table(slices)

        center = [0, 0, 0, 0, 1, 0, 0.5, 0.5]

        for i in range(slices):
            p1 = [
                radius * cs[i, 0],
                0,
                radius * cs[i, 1],
                0,
                1,
                0,
                cs[i, 0] * 0.5 + 0.5,
                cs[i, 1] * 0.5 + 0.5,
            ]
            p2 = [
                radius * cs[i + 1, 0],
                0,
                radius * cs[i + 1, 1],
                0,
                1,
                0,
                cs[i + 1, 0] * 0.5 + 0.5,
                cs[i + 1, 1] * 0.5 + 0.5,
            ]

            data.extend(center)
            data.extend(p2)
            data.extend(p1)

        data_array = np.array(data, dtype=np.float32)
        prim = _primitive(data_array)
        cls._primitives[name] = prim

    @classmethod
    def create_torus(cls, name, minor_radius, major_radius, sides, rings):
        if minor_radius <= 0 or major_radius <= 0:
            raise ValueError("Radii must be positive")
        if sides < 3 or rings < 3:
            raise ValueError("Sides and rings must be at least 3")

        d_psi = 2.0 * np.pi / rings
        d_phi = -2.0 * np.pi / sides

        psi = 0.0

        vertices = []
        normals = []
        uvs = []

        for j in range(rings + 1):
            c_psi = np.cos(psi)
            s_psi = np.sin(psi)
            phi = 0.0
            for i in range(sides + 1):
                c_phi = np.cos(phi)
                s_phi = np.sin(phi)

                x = c_psi * (major_radius + c_phi * minor_radius)
                z = s_psi * (major_radius + c_phi * minor_radius)
                y = s_phi * minor_radius
                vertices.append([x, y, z])

                nx = c_psi * c_phi
                nz = s_psi * c_phi
                ny = s_phi
                normals.append([nx, ny, nz])

                u = i / sides
                v = j / rings
                uvs.append([u, v])

                phi += d_phi
            psi += d_psi

        data = []
        for j in range(rings):
            for i in range(sides):
                idx1 = j * (sides + 1) + i
                idx2 = j * (sides + 1) + (i + 1)
                idx3 = (j + 1) * (sides + 1) + i
                idx4 = (j + 1) * (sides + 1) + (i + 1)

                p1 = vertices[idx1] + normals[idx1] + uvs[idx1]
                p2 = vertices[idx2] + normals[idx2] + uvs[idx2]
                p3 = vertices[idx3] + normals[idx3] + uvs[idx3]
                p4 = vertices[idx4] + normals[idx4] + uvs[idx4]

                data.extend(p1)
                data.extend(p3)
                data.extend(p2)

                data.extend(p2)
                data.extend(p3)
                data.extend(p4)

        data_array = np.array(data, dtype=np.float32)
        prim = _primitive(data_array)
        cls._primitives[name] = prim

    @classmethod
    def create_cylinder(cls, name, radius, height, slices, stacks):
        """
        Creates a cylinder primitive.
        The cylinder is aligned along the y-axis.
        This method generates the cylinder walls, but not the top and bottom caps.
        """
        if radius <= 0.0:
            raise ValueError("Radius must be positive")
        if height < 0.0:
            raise ValueError("Height must be non-negative")
        if slices < 3:
            slices = 3
        if stacks < 1:
            stacks = 1

        data = []
        h2 = height / 2.0
        y_step = height / stacks

        cs = _circle_table(slices)

        du = 1.0 / slices
        dv = 1.0 / stacks

        for i in range(stacks):
            y0 = -h2 + i * y_step
            y1 = -h2 + (i + 1) * y_step
            v = i * dv
            for j in range(slices):
                u = j * du

                nx1 = cs[j, 0]  # cos
                nz1 = cs[j, 1]  # sin
                x1 = radius * nx1
                z1 = radius * nz1

                nx2 = cs[j + 1, 0]
                nz2 = cs[j + 1, 1]
                x2 = radius * nx2
                z2 = radius * nz2

                p_bl = [x1, y0, z1, nx1, 0, nz1, u, v]
                p_br = [x2, y0, z2, nx2, 0, nz2, u + du, v]
                p_tl = [x1, y1, z1, nx1, 0, nz1, u, v + dv]
                p_tr = [x2, y1, z2, nx2, 0, nz2, u + du, v + dv]

                # Triangle 1
                data.extend(p_bl)
                data.extend(p_tl)
                data.extend(p_br)
                # Triangle 2
                data.extend(p_br)
                data.extend(p_tl)
                data.extend(p_tr)

        data_array = np.array(data, dtype=np.float32)
        prim = _primitive(data_array)
        cls._primitives[name] = prim

    @classmethod
    def create_disk(cls, name, radius, slices):
        if radius <= 0.0:
            raise ValueError("Radius must be positive")
        if slices < 3:
            slices = 3

        data = []
        cs = _circle_table(slices)

        center = [0, 0, 0, 0, 1, 0, 0.5, 0.5]

        for i in range(slices):
            p1 = [
                radius * cs[i, 0],
                0,
                radius * cs[i, 1],
                0,
                1,
                0,
                cs[i, 0] * 0.5 + 0.5,
                cs[i, 1] * 0.5 + 0.5,
            ]
            p2 = [
                radius * cs[i + 1, 0],
                0,
                radius * cs[i + 1, 1],
                0,
                1,
                0,
                cs[i + 1, 0] * 0.5 + 0.5,
                cs[i + 1, 1] * 0.5 + 0.5,
            ]

            data.extend(center)
            data.extend(p2)
            data.extend(p1)

        data_array = np.array(data, dtype=np.float32)
        prim = _primitive(data_array)
        cls._primitives[name] = prim

    @classmethod
    def create_torus(cls, name, minor_radius, major_radius, sides, rings):
        if minor_radius <= 0 or major_radius <= 0:
            raise ValueError("Radii must be positive")
        if sides < 3 or rings < 3:
            raise ValueError("Sides and rings must be at least 3")

        d_psi = 2.0 * np.pi / rings
        d_phi = -2.0 * np.pi / sides

        psi = 0.0

        vertices = []
        normals = []
        uvs = []

        for j in range(rings + 1):
            c_psi = np.cos(psi)
            s_psi = np.sin(psi)
            phi = 0.0
            for i in range(sides + 1):
                c_phi = np.cos(phi)
                s_phi = np.sin(phi)

                x = c_psi * (major_radius + c_phi * minor_radius)
                z = s_psi * (major_radius + c_phi * minor_radius)
                y = s_phi * minor_radius
                vertices.append([x, y, z])

                nx = c_psi * c_phi
                nz = s_psi * c_phi
                ny = s_phi
                normals.append([nx, ny, nz])

                u = i / sides
                v = j / rings
                uvs.append([u, v])

                phi += d_phi
            psi += d_psi

        data = []
        for j in range(rings):
            for i in range(sides):
                idx1 = j * (sides + 1) + i
                idx2 = j * (sides + 1) + (i + 1)
                idx3 = (j + 1) * (sides + 1) + i
                idx4 = (j + 1) * (sides + 1) + (i + 1)

                p1 = vertices[idx1] + normals[idx1] + uvs[idx1]
                p2 = vertices[idx2] + normals[idx2] + uvs[idx2]
                p3 = vertices[idx3] + normals[idx3] + uvs[idx3]
                p4 = vertices[idx4] + normals[idx4] + uvs[idx4]

                data.extend(p1)
                data.extend(p3)
                data.extend(p2)

                data.extend(p2)
                data.extend(p3)
                data.extend(p4)

        data_array = np.array(data, dtype=np.float32)
        prim = _primitive(data_array)
        cls._primitives[name] = prim
