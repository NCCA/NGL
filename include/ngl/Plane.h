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

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef PLANE_H__
#define PLANE_H__
//----------------------------------------------------------------------------------------------------------------------
/// @file Plane.h
/// @brief a simple mathmatical representation of a plane
//----------------------------------------------------------------------------------------------------------------------
// part of the python bindings
#ifdef NO_PYTHON_LIB
  #include <boost/python.hpp>
  #include <boost/format.hpp>
#endif

// must include types.h first for Real and GLEW if required
#include "Types.h"
#include "Vec3.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file Plane.h
/// @brief encapsulates a simple plane
/// based on the tutorial here http://www.lighthouse3d.com/opengl/maths/index.php?planes
/// @author Jonathan Macey
/// @version 1.0
/// @date 21/3/11 Initial version

//----------------------------------------------------------------------------------------------------------------------


namespace ngl
{

class NGL_DLLEXPORT Plane
{
public :
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief ctor passing in 3 vectors for the plane
	/// @param[in] _v1 the first Point
	/// @param[in] _v2 the second Point
	/// @param[in] _v3 the third Point
	//----------------------------------------------------------------------------------------------------------------------
	Plane(	const Vec3 &_v1,const Vec3 &_v2,const Vec3 &_v3 ) noexcept;

	//----------------------------------------------------------------------------------------------------------------------
	/// @brief default ctor
	//----------------------------------------------------------------------------------------------------------------------
	Plane() noexcept;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief dtor (not used)
	//----------------------------------------------------------------------------------------------------------------------
	~Plane() noexcept;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief set the plane from 3 points
	/// @param[in] _v1 the first point
	/// @param[in] _v2 the second point
	/// @param[in] _v3 the third point
	//----------------------------------------------------------------------------------------------------------------------
	void setPoints(const Vec3 &_v1,const Vec3 &_v2,const Vec3 &_v3) noexcept;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief set the plane from a normal and a point
	/// @param[in] _normal the normal
	/// @param[in] _point the point
	//----------------------------------------------------------------------------------------------------------------------
	void setNormalPoint(const Vec3 &_normal,const Vec3 &_point) noexcept;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief set the plane from the co-efficients
	/// @param[in] _a the first co-efficient
	/// @param[in] _b the second co-efficient
	/// @param[in] _c the third co-efficient
	/// @param[in] _d the fourth co-efficient

	//----------------------------------------------------------------------------------------------------------------------
	void setFloats(	Real _a,	Real _b,	Real _c,	Real _d ) noexcept;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief get the distance from the point _p to the plane
	/// @param[in] _p the position to check agains
	/// @returns the distance from point to plane
	//----------------------------------------------------------------------------------------------------------------------
	Real distance(const Vec3 &_p) const noexcept;

	//----------------------------------------------------------------------------------------------------------------------
	/// @brief accesor to get the normal
	/// @returns the normal
	//----------------------------------------------------------------------------------------------------------------------
	inline Vec3 getNormal()const noexcept{return m_normal;}

	//----------------------------------------------------------------------------------------------------------------------
	/// @brief accesor to get the point
	/// @returns the point
	//----------------------------------------------------------------------------------------------------------------------
	inline Vec3 getPoint()const  noexcept{return m_point;}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief accesor to get D
	/// @returns the m_d
	//----------------------------------------------------------------------------------------------------------------------
	inline Real getD()const  noexcept{return m_d;}


private :
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the normal of the plane
	//----------------------------------------------------------------------------------------------------------------------
	Vec3 m_normal;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the point position of the normal /  plane
	//----------------------------------------------------------------------------------------------------------------------
	Vec3 m_point;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the co-efficient of the plane
	//----------------------------------------------------------------------------------------------------------------------
	Real m_d;

};


} //end of NGL namespace
#endif




