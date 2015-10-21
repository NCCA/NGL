/**
  Copyright (C) 2009 Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/
#ifndef COLOUR_H__
#define COLOUR_H__
/// @file Colour.h
/// @brief a simple colour class for RGBA colour

// part of the python bindings
#ifdef NO_PYTHON_LIB
  #include <boost/python.hpp>
  #include <boost/format.hpp>
#endif
// must include types.h first for Real and GLEW if required
#include "Types.h"

//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class Colour
/// @brief simple class to hold colour information and set the basic opengl colour
///  state. also has overloaded methods to do basic math on colour values.
/// @author Jonathan Macey
/// @version 5.0
/// @date 20/10/10 added python binding see Colour.inc.h
/// @date Last Revision 29/09/09 Updated to NCCA coding standard
/// @todo add code to use other colour spaces, could be done like Renderman with ctor "HSV" etc
//----------------------------------------------------------------------------------------------------------------------


class NGL_DLLEXPORT Colour
{
public :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief constructor passing in r g b components
  /// @param[in]  _r red component
  /// @param[in]  _g green component
  /// @param[in]  _b blue component
  /// @param[in]  _a the alpha component
  //----------------------------------------------------------------------------------------------------------------------
  inline Colour( Real _r=0.0, Real _g=0.0,  Real _b=0.0, Real _a=1.0 )  noexcept:
                 m_r(_r),
                 m_g(_g),
                 m_b(_b),
                 m_a(_a){;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy constructor passing in a Colour
  /// @param[in] _c the colour to use
  //----------------------------------------------------------------------------------------------------------------------
  inline Colour( const Colour  &_c )  noexcept:
                 m_r(_c.m_r),
                 m_g(_c.m_g),
                 m_b(_c.m_b),
                 m_a(_c.m_a){;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set method to change the current values of the colour
  /// as well as the transparency
  /// @param[in]  _r red component to be set
  /// @param[in]  _g green component to be set
  /// @param[in]  _b blue component to be set
  /// @param[in]  _a alpha transparency value
  //----------------------------------------------------------------------------------------------------------------------
  inline void set( Real _r,Real _g, Real _b, Real _a=1.0) noexcept
              {
                 m_r=_r;
                 m_g=_g;
                 m_b=_b;
                 m_a=_a;
              }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set method to set from another Colour
  /// @param[in] _c the colour
  //----------------------------------------------------------------------------------------------------------------------
  inline void set( const Colour& _c ) noexcept
              {
                m_r = _c.m_r;
                m_g = _c.m_g;
                m_b= _c.m_b;
                m_a=_c.m_a;
              }

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief + operator to add two colours
  /// @param[in] _c the Colour to add
  /// @returns this+_c
  //----------------------------------------------------------------------------------------------------------------------
  Colour operator +( const Colour &_c ) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief - operator to subtract colours
  /// @param[in] _c the Colour to add
  /// @return this-_c
  //----------------------------------------------------------------------------------------------------------------------
  Colour operator -( const Colour &_c ) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief - operator to add rhs to current colour
  /// @param[in] _c the Colour to add
  /// @return this+_c
  //----------------------------------------------------------------------------------------------------------------------
  const Colour& operator +=( const Colour &_c ) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief - operator to multiply colours
  /// @param[in] _c the Colour to mult
  /// @return this*_c
  //----------------------------------------------------------------------------------------------------------------------
  Colour operator *( const Colour &_c ) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief * operator to multiply by a scalar
  /// @param[in] _c the scalar to multiply colour by
  /// @return this*_c
  //----------------------------------------------------------------------------------------------------------------------
  Colour operator *( const Real _c ) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief * operator to multiply = by a colour
  /// @param[in] _c the scalar to multiply colour by
  /// @return this*=_c
  //----------------------------------------------------------------------------------------------------------------------
  const Colour& operator *=( const Colour &_c ) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief * operator to multiply by a scalar
  /// @param[in] _c the scalar to multiply colour by
  /// @return this*_c
  //----------------------------------------------------------------------------------------------------------------------
  const Colour& operator *=( Real _c  ) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// add the product of source color and reflection coefficient
  /// @param[in] _src the source colour
  /// @param[in] _refl the reflected colour
  //----------------------------------------------------------------------------------------------------------------------
  void add( const Colour& _src, const Colour& _refl ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor method to return a pointer to the colour array
  /// @returns m_openGL[0] the first element of the array
  //----------------------------------------------------------------------------------------------------------------------
  inline Real * openGL() noexcept{return &m_openGL[0];}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor method for the Red colour component
  /// @returns the red colour component
  //----------------------------------------------------------------------------------------------------------------------
  inline Real r() const  noexcept{return m_r;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the red colour component
  /// @param[in] _r the red colour value to set
  //----------------------------------------------------------------------------------------------------------------------
  void r(Real _r) noexcept{m_r=_r;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor method for the Green colour component
  /// @returns the green colour component
  //----------------------------------------------------------------------------------------------------------------------
  inline Real g() const  noexcept{return m_g;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the Green colour component
  /// @param[in] _g the green colour value to set
  //----------------------------------------------------------------------------------------------------------------------
  void g(Real _g) noexcept{m_g=_g;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor method for the blue colour component
  /// @returns the blue colour component
  //----------------------------------------------------------------------------------------------------------------------
  inline Real b() const  noexcept{return m_b;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the Blue colour component
  /// @param[in] _b the green colour value to set
  //----------------------------------------------------------------------------------------------------------------------
  void b(Real _b) noexcept{m_b=_b;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor method for the alpha  component
  /// @returns the alpha  component
  //----------------------------------------------------------------------------------------------------------------------
  inline Real a() const  noexcept{return m_a;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the alpha  component
  /// @param[in] _a the alpha  value to set
  //----------------------------------------------------------------------------------------------------------------------
  void a(Real _a) noexcept{m_a=_a;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief clamp the colour to the given range from Eduard Zell MSc 2010
  /// the input values >0 < 1.0 and _min <= _max
  /// @param _min[in] the minimum colour clamp value
  /// @param _max[in] the maximum colour clamp value
  //----------------------------------------------------------------------------------------------------------------------
  void clamp( Real _min, Real _max ) noexcept;

/// @note I've made this public as some compilers automatically make the
/// anonymous unions public whereas clang++ complains see this post
/// http://jonmacey.blogspot.com/2011/03/anonymous-union-struct-weirdness.html
public :
    friend class Material;
    //----------------------------------------------------------------------------------------------------------------------
    // note the BUILDING_DOCS define is set in the doxygen Doxyfile so that we get
    // nice documents for these member attributes is must not be set in C++ build
    //----------------------------------------------------------------------------------------------------------------------
    #ifndef BUILDING_DOCS
    union
    {
      struct
      {
    #endif
        //----------------------------------------------------------------------------------------------------------------------
        /// @brief red component of the colour tuple
        //----------------------------------------------------------------------------------------------------------------------
        Real m_r;
        //----------------------------------------------------------------------------------------------------------------------
        /// @brief green component of the colour tuple
        //----------------------------------------------------------------------------------------------------------------------
        Real m_g;
        //----------------------------------------------------------------------------------------------------------------------
        /// @brief blue component of the colour tuple
        //----------------------------------------------------------------------------------------------------------------------
        Real m_b;
        //----------------------------------------------------------------------------------------------------------------------
        /// @brief alpha the transparent element
        //----------------------------------------------------------------------------------------------------------------------
        Real m_a;
      #ifndef BUILDING_DOCS
      };
      #endif
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief The data as an array of 4 floats useful for passing to OpenGL fv data types
      /// this is mapped as a union to the following \n
      /// m_r == m_openGL[0] \n
      /// m_g == m_openGL[1] \n
      /// m_b == m_openGL[2] \n
      /// m_a == m_openGL[3] \n
      //----------------------------------------------------------------------------------------------------------------------
      Real m_openGL[4];
    #ifndef BUILDING_DOCS
    };
    #endif
    #ifdef NO_PYTHON_LIB
      public :
        std::string pyPrint();
        boost::python::tuple getOpenGL();
        Real getItem(int index);
        void setItem(int _index,Real _value);
    #endif


};

}
#endif // colour
//----------------------------------------------------------------------------------------------------------------------

