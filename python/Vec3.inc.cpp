namespace ngl
{

void (Vec3::*Vec3SetF)(Real , Real , Real) = &Vec3::set;
void (Vec3::*Vec3SetC)(const ngl::Vec3 &) = &Vec3::set;
void (Vec3::*Vec3SetC4)(const ngl::Vec4 &) = &Vec3::set;
void (Vec3::*Vec3SetP)(const ngl::Vec3 *) = &Vec3::set;

void (Vec3::*vec3cross2)(const ngl::Vec3 &, const ngl::Vec3 &) = &Vec3::cross;
ngl::Vec3 (Vec3::*vec3cross)(const ngl::Vec3 &)const =&Vec3::cross;


bool Vec3::equals( const ngl::Vec3& _x, const ngl::Vec3& _y ) const {return _x==_y;}


ngl::Real Vec3::getItem(int _index)
{
  if(_index<0 && _index >2)
  {
    PyErr_SetString(PyExc_IndexError, "Index out of range.");
    boost::python::throw_error_already_set();
  }
  return m_openGL[_index];
}

void Vec3::setItem(int _index, ngl::Real _value)
{
  if(_index<0 && _index >2)
  {
    PyErr_SetString(PyExc_IndexError, "Index out of range.");
    boost::python::throw_error_already_set();
  }

    m_openGL[_index]=_value;
}

std::string Vec3::pyPrint()
{
  boost::format fmtr("[%f,%f,%f]");
  fmtr % m_x % m_y % m_z ;
  return fmtr.str();
}

boost::python::tuple Vec3::getOpenGL()
{
    return boost::python::make_tuple(m_x,m_y,m_z);
}

}; // end namespace
