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

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef BEZIER_CURVE_H__
#define BEZIER_CURVE_H__
/// @file BezierCurve.h
/// @brief basic BezierCurve using CoxDeBoor algorithm
// must include types.h first for Real and GLEW if required
#include "Types.h"
#include "Vec3.h"
#include <vector>
#include "VertexArrayObject.h"

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class BezierCurve  "include/BezierCurve.h"
/// @brief Generic Bezier Curve Class allowing the user to generate basic curves using a number of different
/// constriction methods, such as array of Vectors, array of numbers etc
/// The class can automatically generate knot vectors as well or the user can specify their own
/// @author Rob Bateman modified and augmented by Jonathan Macey
/// @version 3.0
/// @date Last Revision 27/09/09 Updated to NCCA Coding standard and V2.0
/// \nRevision History :
///  \n18/06/08 Initial class written
/// @todo update this class to run the CoxDeBoor algo once and then store the points in a dynamic
/// array based on the LOD value passed in. This will speed up the execution for static curves as at
/// present we calculate each time. Also this array can then be used to draw with VertexArrays and we
/// will not need to create the DisplayLists
//----------------------------------------------------------------------------------------------------------------------
class NGL_DLLEXPORT BezierCurve
{
public :
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief default ctor sets initial values for Curve to be used with AddPoint , AddKnot etc
	//----------------------------------------------------------------------------------------------------------------------
	BezierCurve() noexcept;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief Ctor passing in an Array of CP's and and Array of knots
	///  @param[in] _p an array of Vector objects which are the control
	///  @param[in] _nPoints the size of the Point Array
	///  @param[in] _k and array of knot values
	///  @param[in] _nKnots the size of the knot array
	//----------------------------------------------------------------------------------------------------------------------
	BezierCurve(const Vec3 *_p,int _nPoints,const Real  *_k,int _nKnots ) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor passing in an array of points, note the knot vector will be automatically
  /// calculated as an open vector using a call to create knots
  /// @param[in] _p the array of CP values expressed as groups of 3 float x,y,z values
  /// @param[in] _nPoints the size of the array *p (note this is the total size of the array)
  //----------------------------------------------------------------------------------------------------------------------
  BezierCurve(const Real  *_p,unsigned int _nPoints) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor
  /// @param _c the curve to copy
  //----------------------------------------------------------------------------------------------------------------------
  BezierCurve(const BezierCurve &_c) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief destructor
  //----------------------------------------------------------------------------------------------------------------------
  ~BezierCurve() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Draw method to draw the curve Note this will be slow as it calls the CoxDeBoor function to calculate each time
  /// it is much quicker to create a display list and use this.
  /// \todo Modify this to use faster method than display lists
  //----------------------------------------------------------------------------------------------------------------------
  void draw() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief draw the control points
  //----------------------------------------------------------------------------------------------------------------------
  void drawControlPoints() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Draw the control hull
  //----------------------------------------------------------------------------------------------------------------------
  void drawHull() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get a point on the curve in the range of 0 - 1 based on the control points
  /// @param[in] _value the point to evaluate between 0 and 1
  /// @returns the value of the point at t
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 getPointOnCurve(  Real _value) const noexcept;

	 //----------------------------------------------------------------------------------------------------------------------
	/// @brief add a control point to the Curve
	/// @param[in] &_p the point to add
	//----------------------------------------------------------------------------------------------------------------------
	void addPoint( const Vec3 &_p ) noexcept;

	//----------------------------------------------------------------------------------------------------------------------
	/// @brief add a point to the curve using x,y,z values
	/// @param[in] _x x value of point
	/// @param[in] _y y value of point
	/// @param[in] _z z value of point
	//----------------------------------------------------------------------------------------------------------------------
	void addPoint(Real _x, Real _y, Real _z ) noexcept;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief add a knot value to the curve
	/// @param[in] _k the value of the knot (note this is added to the end of the curve
	//----------------------------------------------------------------------------------------------------------------------
	void addKnot( Real _k	) noexcept;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief create a knot vector array based as an Open Vector (half 0.0 half 1.0)
	//----------------------------------------------------------------------------------------------------------------------
	void createKnots() noexcept;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief implementation of the CoxDeBoor algorithm for Bezier Curves borrowed from Rob Bateman's example and
	/// modified to make it work with the class. NOTE, this is a recursive function
	/// @returns Real the evaluation of the weight at the current value
	/// @param[in] _u
	/// @param[in] _i
	/// @param[in] _k
	/// @param[in] _knots the array of knots for the curve
	//----------------------------------------------------------------------------------------------------------------------
	Real coxDeBoor(Real _u,int _i,int _k,const std::vector <Real> &_knots) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the Level of Detail for Drawing
  /// @note this will have no Effect if the createVAO has
  /// been called before
  /// @param[in] _lod the level of detail to use when creating the display list for drawing the higher the number
  /// the finer the drawing
  //----------------------------------------------------------------------------------------------------------------------
  void inline setLOD(int _lod) noexcept{m_lod=_lod;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the Level of Detail for Drawing
  //----------------------------------------------------------------------------------------------------------------------
  void createVAO() noexcept;
protected :

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the display list index created from glCreateLists
  //----------------------------------------------------------------------------------------------------------------------
  GLuint m_listIndex;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief The Order of the Curve = Degree +1
  //----------------------------------------------------------------------------------------------------------------------
  unsigned int m_order;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief The level of detail used to calculate how much detail to draw
  //----------------------------------------------------------------------------------------------------------------------
  int m_lod;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief The ammount of Control Points in the Curve
  //----------------------------------------------------------------------------------------------------------------------
  int m_numCP;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief The degree of the curve, Calculated from the Number of Control Points
  //----------------------------------------------------------------------------------------------------------------------
  int m_degree;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief The knot vector always has as many values as the numer of verts (cp) + the degree
  //----------------------------------------------------------------------------------------------------------------------
  unsigned int m_numKnots;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  the contol points for the curve
  //----------------------------------------------------------------------------------------------------------------------
  std::vector <Vec3> m_cp;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  the knot vector for the curve
  //----------------------------------------------------------------------------------------------------------------------
  std::vector <Real> m_knots;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a vertex array object for our curve drawing
  //----------------------------------------------------------------------------------------------------------------------
  VertexArrayObject *m_vaoCurve;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a vertex array object for our point drawing
  //----------------------------------------------------------------------------------------------------------------------
  VertexArrayObject *m_vaoPoints;


}; // end class BezierCurve
} // end NGL Lib namespace
#endif // end header file

//----------------------------------------------------------------------------------------------------------------------
