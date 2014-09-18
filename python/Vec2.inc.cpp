namespace ngl
{

void (Vec2::*Vec2SetF)(const ngl::Real &,const ngl::Real &) = &Vec2::set;
void (Vec2::*Vec2SetC)(const ngl::Vec2 &) = &Vec2::set;


bool Vec2::equals( const ngl::Vec2& _x, const ngl::Vec2& _y ) const {return _x==_y;}


ngl::Real Vec2::getItem(int _index)
{
  if(_index<0 && _index >1)
  {
    PyErr_SetString(PyExc_IndexError, "Index out of range.");
    boost::python::throw_error_already_set();
  }
  return m_openGL[_index];
}

void Vec2::setItem(int _index, ngl::Real _value)
{
  if(_index<0 && _index >1)
  {
    PyErr_SetString(PyExc_IndexError, "Index out of range.");
    boost::python::throw_error_already_set();
  }

    m_openGL[_index]=_value;
}

std::string Vec2::pyPrint()
{
  boost::format fmtr("[%f,%f]");
  fmtr % m_x % m_y ;
  return fmtr.str();
}

boost::python::tuple Vec2::getOpenGL()
{
    return boost::python::make_tuple(m_x,m_y);
}

}; // end namespace
