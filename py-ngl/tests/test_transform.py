import pytest

from ngl import Transform, TransformRotationOrder, Vec3, Vec4

orders = ["xyz", "yzx", "zxy", "xzy", "yxz", "zyx"]


def test_ctor():
    tx = Transform()
    assert tx.position.x == pytest.approx(0.0)
    assert tx.position.y == pytest.approx(0.0)
    assert tx.position.z == pytest.approx(0.0)
    assert tx.scale.x == pytest.approx(1.0)
    assert tx.scale.y == pytest.approx(1.0)
    assert tx.scale.z == pytest.approx(1.0)
    assert tx.rotation.x == pytest.approx(0.0)
    assert tx.rotation.y == pytest.approx(0.0)
    assert tx.rotation.z == pytest.approx(0.0)
    assert tx.order == "xyz"


def test_set_position():
    tx = Transform()
    tx.set_position(2.0, 3.5, 4.2)
    assert tx.position.x == pytest.approx(2.0)
    assert tx.position.y == pytest.approx(3.5)
    assert tx.position.z == pytest.approx(4.2)

    tx.set_position(Vec3(2.0, 3.5, 4.2))
    assert tx.position.x == pytest.approx(2.0)
    assert tx.position.y == pytest.approx(3.5)
    assert tx.position.z == pytest.approx(4.2)

    tx.set_position(Vec4(2.0, 3.5, 4.2))
    assert tx.position.x == pytest.approx(2.0)
    assert tx.position.y == pytest.approx(3.5)
    assert tx.position.z == pytest.approx(4.2)

    tx.set_position((2.0, 3.5, 4.2))
    assert tx.position.x == pytest.approx(2.0)
    assert tx.position.y == pytest.approx(3.5)
    assert tx.position.z == pytest.approx(4.2)

    tx.set_position([2.0, 3.5, 4.2])
    assert tx.position.x == pytest.approx(2.0)
    assert tx.position.y == pytest.approx(3.5)
    assert tx.position.z == pytest.approx(4.2)

    with pytest.raises(ValueError):
        tx.set_position(23, 43, 5, 2)


def test_set_rotation():
    tx = Transform()
    tx.set_rotation(45.0, -20.0, 340)
    assert tx.rotation.x == pytest.approx(45.0)
    assert tx.rotation.y == pytest.approx(-20.0)
    assert tx.rotation.z == pytest.approx(340.0)

    tx.set_rotation(Vec3(45.0, -20.0, 340))
    assert tx.rotation.x == pytest.approx(45.0)
    assert tx.rotation.y == pytest.approx(-20.0)
    assert tx.rotation.z == pytest.approx(340.0)

    tx.set_rotation(Vec4(45.0, -20.0, 340))
    assert tx.rotation.x == pytest.approx(45.0)
    assert tx.rotation.y == pytest.approx(-20.0)
    assert tx.rotation.z == pytest.approx(340.0)

    with pytest.raises(ValueError):
        tx.set_rotation("hello", 43, 5)


def test_set_scale():
    tx = Transform()
    tx.set_scale(2.0, 5.0, 2.1)
    assert tx.scale.x == pytest.approx(2.0)
    assert tx.scale.y == pytest.approx(5.0)
    assert tx.scale.z == pytest.approx(2.1)

    tx.set_scale(Vec3(2.0, 5.0, 2.1))
    assert tx.scale.x == pytest.approx(2.0)
    assert tx.scale.y == pytest.approx(5.0)
    assert tx.scale.z == pytest.approx(2.1)

    tx.set_scale(Vec4(2.0, 5.0, 2.1))
    assert tx.scale.x == pytest.approx(2.0)
    assert tx.scale.y == pytest.approx(5.0)
    assert tx.scale.z == pytest.approx(2.1)

    with pytest.raises(ValueError):
        tx.set_scale("hello", 43, 5)


def test_get_matrix_default():
    for o in orders:
        tx = Transform()
        tx.set_order(o)
        matrix = tx.get_matrix()
        # fmt: off
        ident = [1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0]
        # fmt: on
        assert matrix.get_matrix() == ident


def test_set_rotation_order():
    tx = Transform()
    for o in orders:
        tx.set_order(o)
        assert tx.order == o
    with pytest.raises(TransformRotationOrder):
        tx.set_order("bogus")


def test_str():
    tx = Transform()
    assert str(tx) == "pos [0.0,0.0,0.0]\nrot [0.0,0.0,0.0]\nscale [1.0,1.0,1.0]"


def test_rotation_orders():
    tx = Transform()
    tx.set_rotation(45, 25, 35)
    tx.set_order("xyz")
    # fmt: off
    result=[0.742404,0.519837,-0.422618,0.0,-0.160787,0.750633,0.640856,0.0,0.650372,-0.407823,0.640856,0.0,0.0,0.0,0.0,1.0]
    # fmt: on
    assert tx.get_matrix().get_matrix() == pytest.approx(result, rel=1e-4)

    tx.set_order("yzx")
    # fmt: off
    result=[0.7424038052558899, 0.6664164066314697, 0.06874391436576843, 0.0, -0.5735765099525452, 0.5792279243469238, 0.5792279839515686, 0.0, 0.34618863463401794, -0.4694509208202362, 0.8122618198394775, 0.0, 0.0, 0.0, 0.0, 1.0]
    # fmt: on
    assert tx.get_matrix().get_matrix() == pytest.approx(result, rel=1e-4)

    tx.set_order("zxy")
    # fmt: off
    result=[0.9138092994689941, 0.4055798351764679, 0.02139154076576233, 0.0, -0.2750445008277893, 0.5792279243469238, 0.7673627138137817, 0.0, 0.29883626103401184, -0.7071068286895752, 0.6408563256263733, 0.0, 0.0, 0.0, 0.0, 1.0]
    # fmt: on
    assert tx.get_matrix().get_matrix() == pytest.approx(result, rel=1e-4)

    tx.set_order("xzy")
    # fmt: off
    result=[0.7424038052558899, 0.5735765099525452, -0.34618863463401794, 0.0, -0.06874385476112366, 0.5792279243469238, 0.8122618198394775, 0.0, 0.6664164066314697, -0.5792279839515686, 0.46945086121559143, 0.0, 0.0, 0.0, 0.0, 1.0]
    # fmt: on
    assert tx.get_matrix().get_matrix() == pytest.approx(result, rel=1e-4)

    tx.set_order("yxz")
    # fmt: off
    result=[0.5709983110427856, 0.7646291851997375, -0.29883626103401184, 0.0, -0.4055798351764679, 0.5792279243469238, 0.7071068286895752, 0.0, 0.7137688398361206, -0.28255486488342285, 0.6408563256263733, 0.0, 0.0, 0.0, 0.0, 1.0]
    # fmt: on
    assert tx.get_matrix().get_matrix() == pytest.approx(result, rel=1e-4)

    tx.set_order("zyx")
    # fmt: off
    result=[0.7424038052558899, 0.6503721475601196, 0.16078753769397736, 0.0, -0.5198368430137634, 0.4078224301338196, 0.7506334781646729, 0.0, 0.4226182997226715, -0.6408563852310181, 0.6408563256263733, 0.0, 0.0, 0.0, 0.0, 1.0]
    # fmt: on
    assert tx.get_matrix().get_matrix() == pytest.approx(result, rel=1e-4)
