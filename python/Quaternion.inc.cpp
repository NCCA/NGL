namespace ngl
{

//ngl::Matrix (Quaternion::*getMatrix)() const = &Quaternion::asMatrix;
bool Quaternion::equals( const ngl::Quaternion& _x, const ngl::Quaternion& _y ) const
{
  return _x==_y;
}

void Quaternion::negate( )
{
  -(*this);
}

ngl::Real Quaternion::getItem(int _index)
{
  int value=0;
  if(_index<0 && _index >4)
  {
    PyErr_SetString(PyExc_IndexError, "Index out of range.");
    boost::python::throw_error_already_set();
  }

   else
   {
    switch (_index)
    {
      case 0 : value=m_s; break;
      case 1 : value=m_x; break;
      case 2 : value=m_y; break;
      case 3 : value=m_z; break;
    }
  }
return value;
}

void Quaternion::setItem(int _index, ngl::Real _value)
{
  if(_index<0 && _index >4)
  {
    PyErr_SetString(PyExc_IndexError, "Index out of range.");
    boost::python::throw_error_already_set();
  }

   else
  {
       switch (_index)
       {
         case 0 : m_s=_value; break;
         case 1 : m_x=_value; break;
         case 2 : m_y=_value; break;
         case 3 : m_z=_value; break;
       }
   }
}

std::string Quaternion::pyPrint()
{
  boost::format fmtr("%f,[%fi,%fj,%fk]");
  fmtr % m_s % m_x % m_y % m_z;
  return fmtr.str();
}

boost::python::tuple Quaternion::getOpenGL()
{
    return boost::python::make_tuple(m_s,m_x,m_y,m_z);
}



boost::python::tuple Quaternion::toAxisAngleT()
{
  ngl::Vec3 axis;
  float angle;
  toAxisAngle( axis, angle );
  return boost::python::make_tuple(axis.openGL(),angle);
}

} // end namespace
