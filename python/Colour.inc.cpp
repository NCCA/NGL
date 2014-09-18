namespace ngl
{
  // create pointers to our overloaded methods
  // as the python module can't differentiate
  void    (Colour::*setR)(ngl::Real)= &Colour::r;
  ngl::Real   (Colour::*getR)() const= &Colour::r;
  void    (Colour::*setG)(ngl::Real)= &Colour::g;
  ngl::Real   (Colour::*getG)() const= &Colour::g;
  void    (Colour::*setB)(ngl::Real)= &Colour::b;
  ngl::Real   (Colour::*getB)() const= &Colour::b;
  void    (Colour::*setA)(ngl::Real)= &Colour::a;
  ngl::Real   (Colour::*getA)() const= &Colour::a;

  void (Colour::*coloursetF)(ngl::Real,ngl::Real,ngl::Real,ngl::Real) = &Colour::set;
  void (Colour::*coloursetC)(const ngl::Colour &) = &Colour::set;

  ngl::Real Colour::getItem(int _index)
  {
    if(_index<0 && _index >3)
    {
      //PyErr_setString(PyExc_IndexError, "Index out of range.");
      boost::python::throw_error_already_set();
    }
    return m_openGL[_index];
  }

  void Colour::setItem(int _index, ngl::Real _value)
  {
    if(_index<0 && _index >3)
    {
      //PyErr_setString(PyExc_IndexError, "Index out of range.");
      boost::python::throw_error_already_set();
    }

      m_openGL[_index]=_value;
  }

  std::string Colour::pyPrint()
  {
    boost::format fmtr("[%f,%f,%f,%f]");
    fmtr % m_r % m_g % m_b % m_a;
    return fmtr.str();
  }

  boost::python::tuple Colour::getOpenGL()
  {
      return boost::python::make_tuple(m_r,m_g,m_b,m_a);
  }
}; // end namespace
