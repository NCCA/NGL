namespace ngl
{

void (Vec4::*Vec4SetF)( ngl::Real ,ngl::Real , ngl::Real ,ngl::Real ) = &Vec4::set;
void (Vec4::*Vec4SetC)(const ngl::Vec4 &) = &Vec4::set;

void (Vec4::*cross2)(const ngl::Vec4 &, const ngl::Vec4 &) = &Vec4::cross;
ngl::Vec4 (Vec4::*cross)(const ngl::Vec4 &)const =&Vec4::cross;


bool Vec4::equals( const ngl::Vec4& _x, const ngl::Vec4& _y ) const {return _x==_y;}


ngl::Real Vec4::getItem(int _index)
{
  if(_index<0 && _index >3)
  {
    PyErr_SetString(PyExc_IndexError, "Index out of range.");
    boost::python::throw_error_already_set();
  }
  return m_openGL[_index];
}

void Vec4::setItem(int _index, ngl::Real _value)
{
  if(_index<0 && _index >3)
  {
    PyErr_SetString(PyExc_IndexError, "Index out of range.");
    boost::python::throw_error_already_set();
  }

    m_openGL[_index]=_value;
}

std::string Vec4::pyPrint()
{
  boost::format fmtr("[%f,%f,%f,%f]");
  fmtr % m_x % m_y % m_z % m_w;
  return fmtr.str();
}

boost::python::tuple Vec4::getOpenGL()
{
    return boost::python::make_tuple(m_x,m_y,m_z,m_w);
}

}; // end namespace
