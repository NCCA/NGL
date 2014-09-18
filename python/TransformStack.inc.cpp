namespace ngl
{
  void (TransformStack::*setCurrentT)(const ngl::Transformation &) = &TransformStack::setCurrent;
  void (TransformStack::*setCurrentM)(const ngl::Mat4 &) = &TransformStack::setCurrent;


std::string TransformStack::pyPrint()
{
  boost::format fmtr("%s\n%s\n");
  fmtr % m_current.getMatrix() % m_current.getTransposeMatrix();
  return fmtr.str();

}



}; // end namespace
