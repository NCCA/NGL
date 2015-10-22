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
#include "PathCamera.h"
#include "NGLStream.h"
//--------------------------------------------------------------------------------------------------------------------
/// @file PathCamera.cpp
/// @brief implementation files for PathCamera class
//----------------------------------------------------------------------------------------------------------------------


namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
PathCamera::PathCamera( const Vec3 &_up, const BezierCurve &_eyePath,const BezierCurve &_lookPath, Real _step) noexcept
{
	m_dir=CAMFWD;
	m_eyeCurvePoint=0.0;
	m_lookCurvePoint=0.0;
	m_eyePath=_eyePath;
	m_lookPath=_lookPath;
	m_step=_step;
	m_up=_up;
}

//----------------------------------------------------------------------------------------------------------------------
PathCamera::PathCamera(const Vec3 &_up, const Vec3 *_eyePoints,int _nEyePoints, const Vec3 *_lookPoints, int _nLookPoints,Real _step) noexcept
{
	m_dir=CAMFWD;
	m_eyeCurvePoint=0.0;
	m_lookCurvePoint=0.0;
	for(int i=0; i<_nEyePoints; ++i)
	{
		m_eyePath.addPoint(_eyePoints[i]);
	}
	m_eyePath.createKnots();

	for(int i=0; i<_nLookPoints; ++i)
	{
		m_lookPath.addPoint(_lookPoints[i]);
	}
	m_lookPath.createKnots();
	m_step=_step;
	m_up=_up;
}



//----------------------------------------------------------------------------------------------------------------------
PathCamera::PathCamera(const Vec4 &_up, const std::string &_fName, Real _step) noexcept
{
	m_dir=CAMFWD;

	std::ifstream FileIn;
	FileIn.open(_fName.c_str(),std::ios::in);

	if (!FileIn.is_open())
	{
		std::cout <<"File : "<<_fName<<" Not found Exiting "<<std::endl;
		exit(EXIT_FAILURE);
	}
	int nEye,nLook;
	FileIn >> nEye>>nLook;

  Vec4 *eyePoints= new Vec4[nEye];
  Vec4 *lookPoints= new Vec4[nLook];

	for(int i=0; i<nEye; ++i)
	{
		FileIn >> eyePoints[i];
	}
	for(int i=0; i<nLook; ++i)
	{
		FileIn>> lookPoints[i];
	}
	FileIn.close();

	m_eyeCurvePoint=0.0;
	m_lookCurvePoint=0.0;
	for(int i=0; i<nEye; ++i)
	{
		m_eyePath.addPoint(eyePoints[i].toVec3());
	}
	m_eyePath.createKnots();

	for(int i=0; i<nLook; ++i)
	{
		m_lookPath.addPoint(lookPoints[i].toVec3());
	}
	m_lookPath.createKnots();

	m_step=_step;
	m_up=_up;

}

//----------------------------------------------------------------------------------------------------------------------
void PathCamera::loadPath( const std::string &_fName) noexcept
{
	m_dir=CAMFWD;
	m_eyeCurvePoint=0.0;
	m_lookCurvePoint=0.0;

	std::ifstream FileIn;
	FileIn.open(_fName.c_str(),std::ios::in);

	if (!FileIn.is_open())
	{
		std::cout <<"File : "<<_fName<<" Not found Exiting "<<std::endl;
		exit(EXIT_FAILURE);
	}
	/// \todo get this working with loading from a Vector
	/*
	Vector eyePoint;
	Vector lookPoint;

	for(int i=0; i<4; i++)
		{
			FileIn >> eyePoint;
			EyePath->SetCP(i,eyePoint);
			}
	for(int i=0; i<4; i++)
		{
			FileIn>> lookPoint;
			LookPath->SetCP(i,lookPoint);
			}
	*/
	FileIn.close();


}


//----------------------------------------------------------------------------------------------------------------------
PathCamera::~PathCamera() noexcept
{

}

//----------------------------------------------------------------------------------------------------------------------
void PathCamera::update() noexcept
{
  Vec3 ept=m_eyePath.getPointOnCurve(m_eyeCurvePoint);
  Vec3 lpt=m_lookPath.getPointOnCurve(m_lookCurvePoint);
  std::cout <<ept<<lpt<<std::endl;
  m_eye.set(ept);
  m_look.set(lpt);
  m_n=m_eye-m_look;
  m_u.set(m_up.cross(m_n));
  m_v.set(m_n.cross(m_u));
  m_u.normalize(); m_v.normalize(); m_n.normalize();

  setViewMatrix();

	m_eyeCurvePoint+=m_step;
	if(m_eyeCurvePoint>1.0)
	{
		m_eyeCurvePoint=0.0;
	}
	m_lookCurvePoint+=m_step;
	if(m_lookCurvePoint>1.0)
	{
		m_lookCurvePoint=0.0;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void PathCamera::updateLooped() noexcept
{
  Vec3 ept=m_eyePath.getPointOnCurve(m_eyeCurvePoint);
  Vec3 lpt=m_lookPath.getPointOnCurve(m_lookCurvePoint);

  m_eye.set(ept);
  m_look.set(lpt);
  m_n=m_eye-m_look;
  m_u=m_up.cross(m_n);
  m_v=m_n.cross(m_u);
  m_u.normalize(); m_v.normalize(); m_n.normalize();

  setViewMatrix();
  if(m_dir==CAMFWD)
  {
    m_eyeCurvePoint+=m_step;
    if(m_eyeCurvePoint>=1.0)
    {
      m_dir=CAMBWD;
    }

		m_lookCurvePoint+=m_step;
		if(m_lookCurvePoint>=1.0)
		{
			m_dir=CAMBWD;
		}
	} // end if fwd

	else
	{
		m_eyeCurvePoint-=m_step;
		if(m_eyeCurvePoint<=m_step)
		{
			m_dir=CAMFWD;
		}
		m_lookCurvePoint-=m_step;
		if(m_lookCurvePoint<=m_step)
		{
			m_dir=CAMFWD;
		}
	}// end else

}

//----------------------------------------------------------------------------------------------------------------------
void PathCamera::drawPaths()const noexcept
{
/// @todo write code to do the drawing
}

void PathCamera::createCurvesForDrawing(int _lod ) noexcept
{
	// now we set the level of detail for the curve
	m_eyePath.setLOD(_lod);
	m_lookPath.setLOD(_lod);
}



} // end namespace ngll
//----------------------------------------------------------------------------------------------------------------------

