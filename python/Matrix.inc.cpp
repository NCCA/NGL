namespace ngl
{

bool Mat4::inversePossible()
{
#warning refactor this for new code
  //Mat4 m=*this;
  //return m.inverse();
}

ngl::Mat4 Mat4::getInverse()
{
 Mat4 m=*this;
 m.inverse();
 return m;
}



ngl::Real Mat4::getItem(int _index)
{
  if(_index<0 && _index >15)
  {
    PyErr_SetString(PyExc_IndexError, "Index out of range.");
    boost::python::throw_error_already_set();
  }
  return m_openGL[_index];
}

void Mat4::setItem(int _index, ngl::Real _value)
{
  if(_index<0 && _index >15)
  {
    PyErr_SetString(PyExc_IndexError, "Index out of range.");
    boost::python::throw_error_already_set();
  }

    m_openGL[_index]=_value;
}

std::string Mat4::pyPrint()
{
  boost::format fmtr("[%f,%f,%f,%f] \n[%f,%f,%f,%f] \n[%f,%f,%f,%f] \n[%f,%f,%f,%f] \n");
  fmtr %
  m_00 % m_01 % m_02 % m_03 %
  m_10 % m_11 % m_12 % m_13 %
  m_20 % m_21 % m_22 % m_23 %
  m_30 % m_31 % m_32 % m_33;
  return fmtr.str();
}

boost::python::tuple Mat4::getOpenGL()
{
  return boost::python::make_tuple(
                                    boost::python::make_tuple(m_00,m_01,m_02,m_03),
                                    boost::python::make_tuple(m_10,m_11,m_12,m_13),
                                    boost::python::make_tuple(m_20,m_21,m_22,m_23),
                                    boost::python::make_tuple(m_30,m_31,m_32,m_33));
}

}; // end namespace
