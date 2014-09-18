namespace ngl
{

  void (Transformation::*setScaleF)(const ngl::Real &,const ngl::Real &,const ngl::Real &) = &Transformation::setScale;
  void (Transformation::*setScaleV)(const ngl::Vec4 &) = &Transformation::setScale;

  void (Transformation::*setPositionF)(const ngl::Real &,const ngl::Real &,const ngl::Real &) = &Transformation::setPosition;
  void (Transformation::*setPositionV)(const ngl::Vec4 &) = &Transformation::setPosition;


  void (Transformation::*setRotationF)(const ngl::Real &,const ngl::Real &,const ngl::Real &) = &Transformation::setRotation;
  void (Transformation::*setRotationV)(const ngl::Vec4 &) = &Transformation::setRotation;


  void (Transformation::*addScaleF)(const ngl::Real &,const ngl::Real &,const ngl::Real &) = &Transformation::addScale;
  void (Transformation::*addScaleV)(const ngl::Vec4 &) = &Transformation::addScale;

  void (Transformation::*addPositionF)(const ngl::Real &,const ngl::Real &,const ngl::Real &) = &Transformation::addPosition;
  void (Transformation::*addPositionV)(const ngl::Vec4 &) = &Transformation::addPosition;


  void (Transformation::*addRotationF)(const ngl::Real &,const ngl::Real &,const ngl::Real &) = &Transformation::addRotation;
  void (Transformation::*addRotationV)(const ngl::Vec4 &) = &Transformation::addRotation;


/*

  const ngl::Matrix& (Transformation::*getMatrixC)() const = &Transformation::getMatrix;
  const ngl::Matrix& (Transformation::*getMatrixM)()  = &Transformation::getMatrix;



  const ngl::Matrix& (Transformation::*getTransposeMatrixC)() const = &Transformation::getTransposeMatrix;
  const ngl::Matrix& (Transformation::*getTransposeMatrixM)()  = &Transformation::getTransposeMatrix;

  const ngl::Matrix& (Transformation::*InverseMatrixC)() const = &Transformation::getInverseMatrix;
  const ngl::Matrix& (Transformation::*InverseMatrixM)()  = &Transformation::getInverseMatrix;
*/

} // end namespace
