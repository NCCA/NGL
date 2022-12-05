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
#ifndef BEZIER_CURVE_H_
#define BEZIER_CURVE_H_
/// @file BezierCurve.h
/// @brief basic BezierCurve using CoxDeBoor algorithm
// must include types.h first for Real and GLEW if required
#include "Types.h"
#include "Vec3.h"
#include <vector>
#include "VAOFactory.h"
#include "SimpleVAO.h"

namespace ngl
{

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

class NGL_DLLEXPORT BezierCurve
{
public :
	
	/// @brief default ctor sets initial values for Curve to be used with AddPoint , AddKnot etc
	BezierCurve() =default;
	/// @brief Ctor passing in an Array of CP's and and Array of knots
	///  @param[in] _p an array of Vector objects which are the control
	///  @param[in] _k and array of knot values
  BezierCurve(const std::vector<Vec3> &_p,const std::vector<Real>  &_k) noexcept;
  /// @brief ctor passing in an array of points, note the knot vector will be automatically
  /// calculated as an open vector using a call to create knots
  /// @param[in] _p the array of CP values expressed as groups of Vec3
  BezierCurve(const std::vector<ngl::Vec3>  &_p) noexcept;
  /// @brief don't allow copies
  BezierCurve(const BezierCurve &_c) =delete;
  /// @brief destructor
  ~BezierCurve() noexcept;
  /// @brief Draw method to draw the curve Note this will be slow as it calls the CoxDeBoor function to calculate each time
  void draw() const noexcept;  
  /// @brief draw the control points
  void drawControlPoints() const noexcept;  
  /// @brief Draw the control hull
  void drawHull() const noexcept;
  /// @brief get a point on the curve in the range of 0 - 1 based on the control points
  /// @param[in] _value the point to evaluate between 0 and 1
  /// @returns the value of the point at t
  Vec3 getPointOnCurve(Real _value) const noexcept;	 
	/// @brief add a control point to the Curve
	/// @param[in] &_p the point to add
	void addPoint(const Vec3 &_p) noexcept;
	/// @brief add a point to the curve using x,y,z values
	/// @param[in] _x x value of point
	/// @param[in] _y y value of point
	/// @param[in] _z z value of point
	void addPoint(Real _x, Real _y, Real _z) noexcept;
	/// @brief add a knot value to the curve
	/// @param[in] _k the value of the knot (note this is added to the end of the curve
	void addKnot(Real _k) noexcept;
	/// @brief create a knot vector array based as an Open Vector (half 0.0 half 1.0)
	void createKnots() noexcept;
	/// @brief implementation of the CoxDeBoor algorithm for Bezier Curves borrowed from Rob Bateman's example and
	/// modified to make it work with the class. NOTE, this is a recursive function
	/// @returns Real the evaluation of the weight at the current value
	/// @param[in] _u
	/// @param[in] _i
	/// @param[in] _k
	/// @param[in] _knots the array of knots for the curve
  Real coxDeBoor(Real _u,unsigned int _i,unsigned int _k,const std::vector <Real> &_knots) const noexcept;

  /// @brief set the Level of Detail for Drawing
  /// @note this will have no Effect if the createVAO has
  /// been called before
  /// @param[in] _lod the level of detail to use when creating the VAO for drawing the higher the number
  /// the finer the drawing
  void setLOD(int _lod) noexcept{m_lod=_lod;}
  /// @brief set the Level of Detail for Drawing
  void createVAO() noexcept;
  std::vector<Vec3> getControlPoints() const noexcept;
  std::vector<Real> getKnots() const noexcept;

protected :
  /// @brief The degree of the curve, Calculated from the Number of Control Points
  unsigned int m_degree=0;
  /// @brief  the control points for the curve
  std::vector <Vec3> m_cp;
  /// @brief  the knot vector for the curve
  std::vector <Real> m_knots;
  /// @brief The Order of the Curve = Degree +1
  unsigned int m_order=m_degree+1;
  /// @brief The level of detail used to calculate how much detail to draw
  unsigned int m_lod=20;
  /// @brief The amount of Control Points in the Curve
  unsigned int m_numCP=0;
  /// @brief The knot vector always has as many values as the numer of verts (cp) + the degree
  unsigned int m_numKnots=m_numCP+m_degree;
  /// @brief a vertex array object for our curve drawing
  std::unique_ptr<AbstractVAO> m_vaoCurve;
  /// @brief a vertex array object for our point drawing
  std::unique_ptr<AbstractVAO>  m_vaoPoints;
}; // end class BezierCurve
} // end NGL Lib namespace
#endif // end header file


