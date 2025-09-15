from ngl import BezierCurve, Vec3


def test_default_ctor():
    test = BezierCurve()
    assert len(test.knots) == 0
    assert len(test.control_points) == 0


def test_create_from_cp():
    test = BezierCurve()
    test.add_point(Vec3(-5.0, 0.0, -5.0))
    test.add_point(Vec3(-2.0, 2.0, 1.0))
    test.add_point(Vec3(3.0, -3.0, -3.0))
    test.add_point(Vec3(2.0, -6.0, 2.0))
    assert len(test.knots) == 9
    assert len(test.control_points) == 4
    cp = test.control_points
    assert cp[0] == Vec3(-5.0, 0.0, -5.0)
    assert cp[1] == Vec3(-2.0, 2.0, 1.0)
    assert cp[2] == Vec3(3.0, -3.0, -3.0)
    assert cp[3] == Vec3(2.0, -6.0, 2.0)


def test_create_from_cp_xyz():
    test = BezierCurve()
    test.add_point(-5.0, 0.0, -5.0)
    test.add_point(-2.0, 2.0, 1.0)
    test.add_point(3.0, -3.0, -3.0)
    test.add_point(2.0, -6.0, 2.0)
    assert len(test.knots) == 9
    assert len(test.control_points) == 4
    cp = test.control_points
    assert cp[0] == Vec3(-5.0, 0.0, -5.0)
    assert cp[1] == Vec3(-2.0, 2.0, 1.0)
    assert cp[2] == Vec3(3.0, -3.0, -3.0)
    assert cp[3] == Vec3(2.0, -6.0, 2.0)


def test_get_point_on_curve():
    test = BezierCurve()
    test.add_point(Vec3(-5.0, 0.0, 0.0))
    test.add_point(Vec3(0.0, 2.0, 0.0))
    test.add_point(Vec3(5.0, 0.0, 0.0))
    assert len(test.knots) == 7
    assert len(test.control_points) == 3
    assert test.get_point_on_curve(0.0) == Vec3(-5.0, 0.0, 0.0)
    assert test.get_point_on_curve(1.0) == Vec3(5.0, 0.0, 0.0)


def test_from_vec3_and_knots():
    cp = [Vec3(-5.0, 0.0, 0.0), Vec3(0.0, 2.0, 0.0), Vec3(5.0, 0.0, 0.0)]
    knots = [0, 0, 0, 1, 1, 1, 1]
    test = BezierCurve(control_points=cp, knots=knots)
    assert len(test.knots) == 7
    assert len(test.control_points) == 3
    assert test.get_point_on_curve(0.0) == Vec3(-5.0, 0.0, 0.0)
    assert test.get_point_on_curve(1.0) == Vec3(5.0, 0.0, 0.0)


def test_from_vec3():
    cp = [Vec3(-5.0, 0.0, 0.0), Vec3(0.0, 2.0, 0.0), Vec3(5.0, 0.0, 0.0)]
    test = BezierCurve(control_points=cp)
    assert len(test.knots) == 7
    assert len(test.control_points) == 3
    assert test.get_point_on_curve(0.0) == Vec3(-5.0, 0.0, 0.0)
    assert test.get_point_on_curve(1.0) == Vec3(5.0, 0.0, 0.0)
    calculated_knots = test.knots
    knots = [0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0]
    assert calculated_knots == knots


def test_add_knot():
    test = BezierCurve()
    test.add_knot(0.5)
    assert len(test.knots) == 1
    test.add_knot(0.5)
    assert len(test.knots) == 2
