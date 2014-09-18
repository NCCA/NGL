namespace ngl
{

  void (BezierCurve::*addPointF)(const ngl::Real ,const ngl::Real ,const ngl::Real ) = &BezierCurve::addPoint;
  void (BezierCurve::*addPointV)(const ngl::Vec3 &) = &BezierCurve::addPoint;


}; // end namespace
