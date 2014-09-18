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
#include "RibExport.h"
#include <boost/format.hpp>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
/// @file RibExport.cpp
/// @brief implementation files for RibExport class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
RibExport::RibExport(const std::string &_fileName)
{
	m_attribCount=0;
	m_transformCount=0;
	m_worldCount=0;
	m_ribFileName=_fileName;
	m_frameNumber=0;
	m_tabs=0;
	m_isOpen=false;
}

//----------------------------------------------------------------------------------------------------------------------
RibExport::~RibExport()
{
	if(m_attribCount !=0)
	{
		std::cerr << "Warning Mismatched AttributeBegin / AttributeEnd block"<<std::endl;
	}
	if(m_transformCount !=0)
	{
		std::cerr << "Warning Mismatched TransformBegin / TransformEnd block"<<std::endl;
	}
	if(m_worldCount !=0)
	{
		std::cerr << "Warning Mismatched WorldBegin / WorldEnd block"<<std::endl;
	}
	if(m_ribFile.is_open())
	{
		m_ribFile.close();
		m_isOpen=false;
	}
}

// Writes the Comment parameters to
// the rib file.
//----------------------------------------------------------------------------------------------------------------------
void RibExport::comment(const std::string &_sText  )
{
	// Append Comment
	m_ribFile << "\n#======================================================\n";
	m_ribFile << "# " << _sText << "\n";
	m_ribFile << "#======================================================\n";
}


//----------------------------------------------------------------------------------------------------------------------
void RibExport::open()
{
	std::string fName;
	fName=(boost::str(boost::format("%s.%03d.rib") % m_ribFileName.c_str() % m_frameNumber));

	m_ribFile.open(fName.c_str(),std::ios::out);
	if (!m_ribFile.is_open())
	{
		std::cerr<<"problems Opening File"<<std::endl;
	}
	m_ribFile<<"# Rib file generated using RibExporter"<<std::endl;
	m_isOpen=true;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::close()
{
	m_ribFile.close();
	++m_frameNumber;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::writeTabs()
{
	for(int i=0; i<m_tabs; ++i)
	{
		m_ribFile <<"\t";
	}
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::AttributeBegin()
{
	writeTabs();
	m_ribFile<<"AttributeBegin "<<std::endl;
	++m_tabs;
	++m_attribCount;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::AttributeEnd()
{
	--m_tabs;
	writeTabs();
	m_ribFile<<"AttributeEnd "<<std::endl;
	m_attribCount--;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::TransformBegin()
{
	writeTabs();
	m_ribFile<<"TransformBegin "<<std::endl;
	++m_tabs;
	++m_transformCount;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::TransformEnd()
{
	--m_tabs;
	writeTabs();
	m_ribFile<<"TransformEnd "<<std::endl;
	--m_transformCount;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::WorldBegin()
{
	writeTabs();
	m_ribFile<<"WorldBegin "<<std::endl;
	++m_tabs;
	++m_worldCount;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::WorldEnd()
{
	--m_tabs;
	writeTabs();
	m_ribFile<<"WorldEnd "<<std::endl;
	--m_worldCount;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::writeToFile( std::string _string   )
{
	writeTabs();
	m_ribFile<<_string<<std::endl;
}



//----------------------------------------------------------------------------------------------------------------------
void RibExport::Translate( const Real _x,   const Real _y,  const Real _z   )
{
	writeTabs();
	m_ribFile<<"Translate "<<_x<<" "<<_y<<" "<<_z<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::Rotate(const Real _angle,const Real _x, const Real _y, const Real _z )
{
	writeTabs();
	m_ribFile<<"Rotate "<<_angle<<" "<<_x<<" "<<_y<<" "<<_z<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::Scale(const Real _x, const Real _y, const Real _z )
{
	writeTabs();
	m_ribFile<<"Scale "<<_x<<" "<<_y<<" "<<_z<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::Sphere(const Real _radius, const Real _zMin,const Real _zMax, const Real _sweep )
{
	writeTabs();
	m_ribFile<<"Sphere "<<_radius<<" "<<_zMin<<" "<<_zMax<<" "<<_sweep<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::Cylinder( const Real _radius, const Real _zMin,  const Real _zMax, const Real _sweep  )
{
	writeTabs();
	m_ribFile<<"Cylinder "<<_radius<<" "<<_zMin<<" "<<_zMax<<" "<<_sweep<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::Cone(const Real _height,  const Real _radius, const Real _sweep    )
{
	writeTabs();
	m_ribFile<<"Cone "<<_height<<" "<<_radius<<" "<<_sweep<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::Paraboloid(const Real _topRad,const Real _zMin, const Real _zMax,  const Real _sweep   )
{
	writeTabs();
	m_ribFile<<"Paraboloid "<<_topRad<<" "<<_zMin<<" "<<_zMax<<" "<<_sweep<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::Hyperboloid( const Real _p1, const Real _p2, const Real _sweep )
{
	writeTabs();
	m_ribFile<<"Hyperboloid "<<_p1<<" "<<_p2<<" "<<_sweep<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::Disk( const Real _height,const Real _radius, const Real _sweep )
{
	writeTabs();
	m_ribFile<<"Disk "<<_height<<" "<<_radius<<" "<<_sweep<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
void RibExport::Torus( const Real _major, const Real _minor, const Real _phiMin,const Real _phiMax, const Real _sweep  )
{
	writeTabs();
	m_ribFile<<"Torus "<<_major<<" "<<_minor<<" "<<_phiMin<<" "<<_phiMax<<" "<<_sweep<<std::endl;
}

} // end ngl namespace

//----------------------------------------------------------------------------------------------------------------------



