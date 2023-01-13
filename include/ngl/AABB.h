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
#ifndef AABB_H_
#define AABB_H_

/// @file AABB.h
/// @brief an Axis Aligned Bounding Box

// must include types.h first for Real and GLEW if required
#include "Types.h"
#include "Vec4.h"
#include "BBox.h"


/// @file AABB.h
/// @brief Axis Aligned Bounding Box can be calculated stand alone
/// or from the BBox class (which is object alined at present)
/// @author Jonathan Macey
/// @version 1.0
/// @date 21/3/11 Initial version




namespace ngl
{

class NGL_DLLEXPORT AABB
{
friend class BBox;
public :
	
	/// @brief ctor
	/// @param[in] _corner the corner extent of the AABB
	/// @param[in] _x the x extent
	/// @param[in] _y the y extent
	/// @param[in] _z the z extent
	
	AABB(const Vec4 &_corner,Real _x,Real _y,	Real _z) noexcept;

	
	/// @brief default ctor
	
	AABB() noexcept;
	
	/// @brief dtor (not used)
	
	~AABB()=default;
	
	/// @brief set the AABB values
	/// @param[in] _corner the corner extent of the AABB
	/// @param[in] _x the x extent
	/// @param[in] _y the y extent
	/// @param[in] _z the z extent
		
	void set(const Vec4 &_corner,Real _x,	Real _y,	Real _z) noexcept;


	// for use in frustum computations
		Vec3 getVertexP(const Vec3 &_normal) const noexcept;
		Vec3 getVertexN(const Vec3 &_normal) const noexcept;
private :
	
	Vec4 m_corner;
	
	Real m_x=1.0f;
	Real m_y=1.0f;
	Real m_z=1.0f;
};


} //end of NGL namespace
#endif




