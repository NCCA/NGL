/*
  Copyright (C) 2011 Jon Macey

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
#include "AABB.h"
//-----------------------------------------------------------------------------
/// @file AABB.cpp
/// @brief implementation files for AABB class
//-----------------------------------------------------------------------------
namespace ngl
{

//-----------------------------------------------------------------------------
AABB::AABB()
{
	m_corner.set(0,0,0,1);

	m_x = 1.0f;
	m_y = 1.0f;
	m_z = 1.0f;
}
//-----------------------------------------------------------------------------
AABB::AABB(const Vec4 &_corner,  Real _x,  Real _y,  Real _z )
{
 set(_corner,_x,_y,_z);
}

//-----------------------------------------------------------------------------
AABB::~AABB()
{

}
//-----------------------------------------------------------------------------
void AABB::set(const Vec4 &_corner,Real _x,Real _y,	Real _z	)
{
	m_corner=_corner;

	if (_x < 0.0)
	{
		_x = -_x;
		m_corner.m_x -= _x;
	}
	if (_y < 0.0)
	{
		_y = -_y;
		m_corner.m_y -= _y;
	}
	if (_z < 0.0)
	{
		_z = -_z;
		m_corner.m_z -= _z;
	}
	m_x = _x;
	m_y = _y;
	m_z = _z;
}

Vec4 AABB::getVertexP(const Vec4 &_normal)
{
	Vec4 res = m_corner;

	if (_normal.m_x > 0)
	{
		res.m_x += m_x;
	}
	if (_normal.m_y > 0)
	{
		res.m_y += m_y;
	}

	if (_normal.m_z > 0)
	{
		res.m_z += m_z;
	}
	return res;
}

Vec4 AABB::getVertexN(const Vec4 &_normal)
{
	Vec4 res = m_corner;

	if (_normal.m_x < 0)
	{
		res.m_x += m_x;
	}
	if (_normal.m_y < 0)
	{
		res.m_y += m_y;
	}

	if (_normal.m_z < 0)
	{
		res.m_z += m_z;
	}
	return res;
}


} // end of ngl namespace
