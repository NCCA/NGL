/*
  Copyright (C) 2009 Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received m_a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Colour.h"
#include <boost/format.hpp>
//----------------------------------------------------------------------------------------------------------------------
/// @file Colour.cpp
/// @brief implementation files for Colour class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{


//----------------------------------------------------------------------------------------------------------------------
void Colour ::add(const Colour& _src,  const Colour& _refl ) noexcept
{ // add the product of source color and reflection coefficient
	m_r += _src.m_r * _refl.m_r;
	m_g += _src.m_g * _refl.m_g;
	m_b += _src.m_b * _refl.m_b;
	m_a += _src.m_a * _refl.m_a;
}

//----------------------------------------------------------------------------------------------------------------------
Colour Colour::operator +( const Colour &_c  ) const noexcept
{
	return Colour(  m_r + _c.m_r,
					m_g + _c.m_g,
					m_b + _c.m_b,
					m_a + _c.m_a );
}

//----------------------------------------------------------------------------------------------------------------------
Colour Colour::operator -( const Colour& _c  ) const noexcept
{
	return Colour(  m_r - _c.m_r,
					m_g - _c.m_g,
					m_b - _c.m_b,
					m_a - _c.m_a );
}

//----------------------------------------------------------------------------------------------------------------------
const Colour& Colour::operator +=( const Colour& _c    ) noexcept
{
	m_r+=_c.m_r;
	m_g+=_c.m_g;
	m_b+=_c.m_b;
	m_a+=_c.m_a;
	return *this;
}
//----------------------------------------------------------------------------------------------------------------------
Colour Colour::operator *( const Colour &_c ) const noexcept
{
	return Colour(
								m_r * _c.m_r,
								m_g * _c.m_g,
								m_b * _c.m_b,
								m_a * _c.m_a
							 );
}
//----------------------------------------------------------------------------------------------------------------------
Colour Colour::operator *(const Real _c   ) const noexcept
{
	return Colour(
								m_r * _c,
								m_g * _c,
								m_b * _c,
								m_a * _c
							 );
}
//----------------------------------------------------------------------------------------------------------------------
const Colour& Colour::operator *=( const Colour& _c ) noexcept
{
	m_r*=_c.m_r;
	m_g*=_c.m_g;
	m_b*=_c.m_b;
	m_a*=_c.m_a;
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
const Colour& Colour::operator *=(Real _c ) noexcept
{
	m_r*=_c;
	m_g*=_c;
	m_b*=_c;
	m_a*=_c;
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------

void Colour::clamp(Real _min, Real _max ) noexcept
{
  m_r<_min ? m_r = _min : m_r;
  m_r>_max ? m_r = _max : m_r;

  m_g<_min ? m_g = _min : m_g;
  m_g>_max ? m_g = _max : m_g;

  m_b<_min ? m_b = _min : m_b;
  m_b>_max ? m_b = _max : m_b;

  m_a<_min ? m_a = _min : m_a;
  m_a>_max ? m_a = _max : m_a;
}



} // end namespace ngl



