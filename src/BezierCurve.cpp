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

/// @file BezierCurve.cpp
/// @brief basic BezierCurve using CoxDeBoor algorithm

#include "BezierCurve.h"
#include <iostream>
namespace ngl
{

void BezierCurve::createKnots() noexcept
{
	m_knots.clear();
	for(unsigned int i=0; i<m_numKnots; ++i)
	{
		m_knots.push_back( (i<(m_numKnots/2))  ? 0.0f : 1.0f);
	}
}


std::vector<Vec3> BezierCurve::getControlPoints() const noexcept
{
	return m_cp;
}
std::vector<Real> BezierCurve::getKnots() const noexcept
{
	return m_knots;
}



BezierCurve::BezierCurve( const std::vector<ngl::Vec3> &_p) noexcept : m_cp{_p}
{
	m_numCP=static_cast<unsigned int>(m_cp.size());
	m_degree=static_cast<unsigned int>(m_cp.size());
	m_order=m_degree+1;
	m_numKnots=m_numCP+m_order;
	createKnots();
}


BezierCurve::BezierCurve(const std::vector<Vec3> &_p, const std::vector<Real> &_k) noexcept : m_cp{_p}, m_knots{_k}
{
	m_numCP=static_cast<unsigned int>(_p.size());
	m_degree=static_cast<unsigned int>(_p.size());
	m_order=m_degree+1;
	m_numKnots=static_cast<unsigned int>(_k.size()); 
}


BezierCurve::~BezierCurve() noexcept
{
	m_cp.clear();
	m_knots.clear();
	if(m_vaoCurve!=nullptr && m_vaoPoints!=nullptr)
	{
		m_vaoCurve->unbind();
    m_vaoCurve->removeVAO();
		m_vaoPoints->unbind();
    m_vaoPoints->removeVAO();
	}
}


Real BezierCurve::coxDeBoor( Real _u,unsigned int _i, unsigned int _k, const std::vector <Real> &_knots ) const noexcept
{
	if(_k==1)
	{
		if( _knots[_i] <= _u && _u <= _knots[_i+1] )
		{
			return 1.0f;
		}
		return 0.0f;
	}
	Real Den1 = _knots[_i+_k-1] - _knots[_i];
	Real Den2 = _knots[_i+_k] - _knots[_i+1];
	Real Eq1=0;
	Real Eq2=0;
	if(Den1>0)
	{
		Eq1 = ((_u-_knots[_i]) / Den1) * coxDeBoor(_u,_i,_k-1,_knots);
	}
	if(Den2>0)
	{
		Eq2 = (_knots[_i+_k]-_u) / Den2 * coxDeBoor(_u,_i+1,_k-1,_knots);
	}
	return Eq1+Eq2;
}



void BezierCurve::drawControlPoints()const noexcept
{

  m_vaoPoints->bind();
  m_vaoPoints->setMode(GL_POINTS);
  m_vaoPoints->draw();
  m_vaoPoints->unbind();

}


void BezierCurve::drawHull()const noexcept
{
  m_vaoPoints->bind();
  m_vaoPoints->setMode(GL_LINE_STRIP);
  m_vaoPoints->draw();
  m_vaoPoints->unbind();
 }


void BezierCurve::draw() const noexcept
{
m_vaoCurve->bind();
m_vaoCurve->draw();
m_vaoCurve->unbind();
}


Vec3 BezierCurve::getPointOnCurve( Real _value  ) const noexcept
{
	Vec3 p;

	// sum the effect of all CV's on the curve at this point to
	// get the evaluated curve point
	//
  for(unsigned int i=0;i!=m_numCP;++i)
	{
		// calculate the effect of this point on the curve
		Real val = coxDeBoor(_value,i,m_degree /*was m_order */,m_knots);

		if(val>0.001f)
		{
			// sum effect of CV on this part of the curve
			p+=val*m_cp[i];
		}
	}

	return p;
}





void BezierCurve::addPoint( const Vec3 &_p    ) noexcept
{
	m_cp.push_back(_p);
	++m_numCP;
	++m_degree;
	m_order=m_degree+1;
	m_numKnots=m_numCP+m_order;
	createKnots();
	#ifdef DEBUG
    std::cout <<"Added "<<m_numCP<<" m_degree "<<m_degree<<" m_numKnots"<<m_numKnots<<" m_order "<<m_order<<'\n';
	#endif
}


void BezierCurve::addPoint( Real _x,  Real _y, Real _z) noexcept
{
	m_cp.push_back(Vec3(_x,_y,_z));
	++m_numCP;
	++m_degree;
	m_order=m_degree+1;
	m_numKnots=m_numCP+m_order;
	createKnots();

	#ifdef DEBUG
    std::cout <<"Added "<<m_numCP<<" m_degree "<<m_degree<<" m_numKnots"<<m_numKnots<<" m_order "<<m_order<<'\n';
	#endif
}

void BezierCurve::addKnot(Real _k) noexcept
{
	m_knots.push_back(_k);
	m_numKnots=m_numCP+m_order;
}

void BezierCurve::createVAO() noexcept
{
  if(m_vaoCurve!=nullptr && m_vaoPoints!=nullptr)
  {
    m_vaoCurve->unbind();
    m_vaoCurve->removeVAO();
    //delete m_vaoCurve;
    m_vaoPoints->unbind();
    m_vaoPoints->removeVAO();
    //delete m_vaoPoints;
  }

  m_vaoPoints=ngl::VAOFactory::createVAO("simpleVAO",GL_POINTS);
  m_vaoPoints->bind();
  size_t size=m_cp.size();
  std::vector <Vec3> points(size);
  for(size_t i=0;i<size;++i)
  {
    points[i].set(m_cp[i]);
  }
  m_vaoPoints->setData(SimpleVAO::VertexData(m_numCP*sizeof(Vec3),points[0].m_x));
  m_vaoPoints->setNumIndices(m_numCP);
  m_vaoPoints->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
  m_vaoPoints->unbind();


  m_vaoCurve=ngl::VAOFactory::createVAO("simpleVAO",GL_LINE_STRIP);
  m_vaoCurve->bind();

  std::vector <Vec3> lines(m_lod);
  for(unsigned int i=0;i!=m_lod;++i)
  {
    Real t  = m_knots[m_numKnots-1] * i / static_cast<Real>(m_lod-1);

    if(i==m_lod-1)
    {
      t-=0.001f;
    }
    lines[i].set(getPointOnCurve(t));
  }
  m_vaoCurve->setData(SimpleVAO::VertexData(m_lod*sizeof(Vec3),lines[0].m_x));
  m_vaoCurve->setNumIndices(m_lod);
  m_vaoCurve->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
  m_vaoCurve->unbind();

}



} // end ngl namespace


