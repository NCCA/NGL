import pytest

from ngl import (
    Mat4,
    Vec3,
    calc_normal,
    clamp,
    frustum,
    lerp,
    look_at,
    ortho,
    perspective,
)


def test_clamp():
    assert clamp(2, 10, 20) == 10  # test  int up
    assert clamp(200, 10, 20) == 20  # test int down
    assert clamp(0.1, 0.01, 1.0) == 0.1
    assert clamp(2.1, 0.01, 1.2) == 1.2


def test_lerp():
    assert lerp(0, 1, 0.5) == 0.5
    assert lerp(0, 1, 0.1) == 0.1
    assert lerp(0, 1, 0.9) == 0.9


def test_clamp_error():
    with pytest.raises(ValueError):
        clamp(1, 100, 0.1)


def test_look_at():
    eye = Vec3(2, 2, 2)
    look = Vec3(0, 0, 0)
    up = Vec3(0, 1, 0)
    view = look_at(eye, look, up)
    # result from Julia function and same as GLM as well
    # fmt: off
    result=Mat4.from_list([0.7071067811865475, -0.4082482904638631, 0.5773502691896258 ,0.0, 0.0, 0.8164965809277261, 0.5773502691896258, 0.0, -0.7071067811865475, -0.4082482904638631, 0.5773502691896258 ,0.0, -0.0, -0.0, -3.4641016151377553, 1.0])
    # fmt: on
    assert view.to_list() == pytest.approx(result.to_list(), abs=1e-3)


def test_perspective():
    # (1.69749,0,0,0,0,2.41421,0,0,0,0,-1.00401,-1,0,0,-0.0400802,0)
    fov = 45.0
    near = 0.02
    far = 10.0
    aspect = 1024.0 / 720.0
    project = perspective(fov, aspect, near, far)
    # fmt: off
    result=Mat4.from_list([1.69749,0,0,0,0,2.41421,0,0,0,0,-1.00401,-1,0,0,-0.0400802,0])
    # fmt: on

    assert project.to_list() == pytest.approx(result.to_list(), abs=1e-3)


def test_ortho():
    project = ortho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0)
    m = [
        +1.000000,
        +0.000000,
        +0.000000,
        -0.000000,
        +0.000000,
        +1.000000,
        +0.000000,
        -0.000000,
        +0.000000,
        +0.000000,
        +1.000000,
        +0.000000,
        +0.000000,
        +0.000000,
        +0.000000,
        +1.000000,
    ]
    # fmt: off

    result=Mat4.from_list(m)

    # fmt: on

    assert project.to_list() == pytest.approx(result.to_list(), abs=1e-3)


def test_calc_normal():
    result = calc_normal(
        Vec3(-1.0, -1.0, 0.0), Vec3(0.0, 0.0, 0.0), Vec3(1.0, -1.0, 0.0)
    )
    assert result == pytest.approx(Vec3(0.0, 0.0, 1.0), abs=1e-3)


def test_frustum():
    f = frustum(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0)

    assert f.to_list() == pytest.approx(
        [
            1.0,
            0.0,
            0.0,
            0.0,
            0.0,
            1.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            -1.0,
            0.0,
            0.0,
            -1.0,
            0.0,
        ],
        abs=1e-3,
    )
