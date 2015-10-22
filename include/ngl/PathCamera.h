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
#ifndef PATHCAMERA_H__
#define PATHCAMERA_H__
//----------------------------------------------------------------------------------------------------------------------
/// @file PathCamera.h
/// @brief a simple camera attached to a path inherits from Camera
//----------------------------------------------------------------------------------------------------------------------
#include "BezierCurve.h"
#include "Camera.h"

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class PathCamera "include/PathCamera.h"
/// @brief Inherits from Camera and  adds a path for both eye and look using two Bezier Curves
/// @example PathCamera/CameraTest.cpp
//----------------------------------------------------------------------------------------------------------------------
class NGL_DLLEXPORT PathCamera : public Camera
{

public :


  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor using two curves
  /// @param [in] _up the up direction of the camera
  /// @param [in] _eyePath the BezierCurve for the eye path
  /// @param [in] _lookPath the BezierCurve for the look path
  /// @param [in] _step the amount of step for the update
  /// @param [in] _proj the type of projection for the camera to use
  //----------------------------------------------------------------------------------------------------------------------
  PathCamera( const Vec3 &_up, const BezierCurve &_eyePath, const BezierCurve &_lookPath, const Real _step ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor using two arrays of points for the eye and look values these will be converted
  /// into BezierCurves for the actual camera paths
  /// @param[in] _up an indication of the camera's up direction
  /// @param[in] _eyePoints a pointer to an array of points for the camera path
  /// @param[in] _nEyePoints the number of points in the _eyePoints array
  /// @param[in] _lookPoints a pointer to an array of points for the camera look path
  /// @param[in] _nLookPoints the number of points in the _lookPoints array
  /// @param[in] _step the amount of steps for the update
  //----------------------------------------------------------------------------------------------------------------------
  PathCamera( const Vec3 &_up,Vec3 const *_eyePoints, int _nEyePoints,Vec3 const  *_lookPoints, int _nLookPoints,Real _step) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor to load the camera data in from a file
  /// @param[in] _up an indication of the camera up direction
  /// @param[in] _fName the name of the file to load
  /// @param[in] _step the amount of steps for the Update
  /// @param[in] _proj the type of projection for the camera to use.
  //----------------------------------------------------------------------------------------------------------------------
  PathCamera(  const Vec4 &_up, const std::string &_fName, Real _step ) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~PathCamera() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief update the camera by incrementing the step value and re-calculating the tx matrix
  //----------------------------------------------------------------------------------------------------------------------
  void update() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief update the camera by incrementing the step value and re-calculating the tx matrix
  /// if the camera is at the end of one of the paths it will return the other way
  //----------------------------------------------------------------------------------------------------------------------
  void updateLooped() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a method to draw the camera paths for debugging etc (note uses immediate mode GL)
  //----------------------------------------------------------------------------------------------------------------------
  void drawPaths() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief load a path from a file
  /// @param[in] _fName the name of the file to load
  //----------------------------------------------------------------------------------------------------------------------
  void loadPath( const std::string &_fName) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief create the display lists for the paths so we can see them
  /// @param[in] _lod the level of detail for the paths display list
  //----------------------------------------------------------------------------------------------------------------------
  void createCurvesForDrawing( int _lod ) noexcept;

protected:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  the eye path of the camera's current position value
  //----------------------------------------------------------------------------------------------------------------------
  Real m_eyeCurvePoint;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  the look path of the camera's current position value
  //----------------------------------------------------------------------------------------------------------------------
  Real m_lookCurvePoint;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  BezierCurve for the the eye positions
  //----------------------------------------------------------------------------------------------------------------------
  BezierCurve m_eyePath;
  /// @brief  BezierCurve for the look positions
  //----------------------------------------------------------------------------------------------------------------------
  BezierCurve m_lookPath;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief enumeration for the camera's direction
  //----------------------------------------------------------------------------------------------------------------------
  enum  DIRECTION
      {
      /// @brief camera going forward
      CAMFWD,
      /// @brief camera going backwards
      CAMBWD
      };
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  current direction of the camera
  //----------------------------------------------------------------------------------------------------------------------
  DIRECTION m_dir;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  the step for each update of the camera, the higher the number the smoother the movement
  //----------------------------------------------------------------------------------------------------------------------
  Real m_step;

#ifdef NO_PYTHON_LIB
  public :
      inline PathCamera(){Camera::Camera();}
#endif

};
}
#endif
//----------------------------------------------------------------------------------------------------------------------


