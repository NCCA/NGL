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
#include "Camera.h"
#include "Util.h"
#include "NGLassert.h"
#include <VertexArrayObject.h>
#include <iostream>
#include <vector>
#include <boost/format.hpp>
//----------------------------------------------------------------------------------------------------------------------
/// @file Camera.cpp
/// @brief implementation files for Camera class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{
// a lot of this stuff is from the HILL book Computer Graphics with OpenGL 2nd Ed Prentice Hall
// a very good book
const static Real CAMERANEARLIMIT=0.00001f;

//----------------------------------------------------------------------------------------------------------------------

Camera::Camera()
{

  m_zNear=0.0001f;
  m_zFar=350.0f;
  m_aspect=720.0f/576.0f;
  m_fov=45.0f;
  m_width=720;
  m_height=576;
  m_eye.set(1,1,1);
}


//----------------------------------------------------------------------------------------------------------------------
void Camera :: setDefaultCamera()
{
  // make default camera
  m_eye=1.0f;
  m_look=0.0f;
  m_up.set(0,1,0);
  m_fov=45.0;
  m_zNear=0.0001f;
  m_zFar=350.0f;
  m_aspect=720.0f/576.0f;
  m_fov=45.0f;

  setShape(m_fov, m_aspect, m_zNear, m_zFar); // good default values here
  set(Vec3(5.0, 5.0, 5.0),Vec3( 0.0, 0.0, 0.0),Vec3(0, 1, 0));
}

//----------------------------------------------------------------------------------------------------------------------
void Camera :: set(const Vec3 &_eye, const Vec3 &_look,  const Vec3 &_up  )
{
	// make U, V, N vectors
	m_eye=_eye;
	m_look=_look;
	m_up=_up;
	m_n=m_eye-m_look;
	m_u=m_up.cross(m_n);
	m_v=m_n.cross(m_u);
	m_u.normalize();
	m_v.normalize();
	m_n.normalize();
	setViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
Camera::Camera(const Vec3 &_eye, const Vec3 &_look, const Vec3 &_up )
{
	setDefaultCamera();
	set(_eye,_look,_up);
}



//----------------------------------------------------------------------------------------------------------------------
void Camera::setViewMatrix()
{
    // grab a pointer to the matrix so we can index is quickly
    Real *M=(Real *)&m_viewMatrix.m_m;
    M[0] =  m_u.m_x;         M[1] =  m_v.m_x;        M[2] =  m_n.m_x;        M[3] = 0.0;
    M[4] =  m_u.m_y;         M[5] =  m_v.m_y;        M[6] =  m_n.m_y;        M[7] = 0.0;
    M[8]  = m_u.m_z;         M[9] =  m_v.m_z;        M[10]=  m_n.m_z;        M[11] =0.0;
    M[12] = -m_eye.dot(m_u); M[13]= -m_eye.dot(m_v); M[14]= -m_eye.dot(m_n); M[15] =1.0;

    calculateFrustum();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::setPerspProjection()
{
  // note 1/tan == cotangent
  Real f= 1.0/tan(radians(m_fov)/2.0);
  m_projectionMatrix.identity();

  m_projectionMatrix.m_m[0][0]=f/m_aspect;
  m_projectionMatrix.m_m[1][1]=f;

  m_projectionMatrix.m_m[2][2]=(m_zFar+m_zNear)/(m_zNear-m_zFar);
  m_projectionMatrix.m_m[3][2]=(2*m_zFar*m_zNear)/(m_zNear-m_zFar);

  m_projectionMatrix.m_m[2][3]=-1;
  m_projectionMatrix.m_m[3][3]=1.0;

}

//----------------------------------------------------------------------------------------------------------------------
void Camera::setProjectionMatrix()
{
	m_projectionMatrix.null();
	setPerspProjection();

}
//----------------------------------------------------------------------------------------------------------------------

void Camera::setShape(Real _viewAngle, Real _aspect, Real _near, Real _far  )

{ // load projection matrix and camera values
	if(_viewAngle >180.0)
	{
		_viewAngle=180.0;
	}
	NGL_ASSERT(_far>_near);
	NGL_ASSERT(_near>CAMERANEARLIMIT);
	if(_near<CAMERANEARLIMIT)
	{
		_near=CAMERANEARLIMIT;
	}
	m_fov = _viewAngle; // viewangle in degrees - must be < 180
	m_aspect = _aspect;
	m_zNear = _near;
	m_zFar = _far;
	setProjectionMatrix();
	//calculateFrustum();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::setAspect( Real _asp  )
{
	m_aspect = _asp;
	setShape(m_fov,m_aspect,m_zNear,m_zFar);
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::setViewAngle( Real _angle	 )
{
	m_fov=_angle;
	setShape(_angle,m_aspect,m_zNear,m_zFar);
}


//----------------------------------------------------------------------------------------------------------------------
void Camera::slide( Real _du,  Real _dv,   Real _dn )
{
	// slide eye by amount du * u + dv * v + dn * n;
	m_eye.m_x += _du * m_u.m_x + _dv * m_v.m_x + _dn * m_n.m_x;
	m_eye.m_y += _du * m_u.m_y + _dv * m_v.m_y + _dn * m_n.m_y;
	m_eye.m_z += _du * m_u.m_z + _dv * m_v.m_z + _dn * m_n.m_z;
	setViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::move( Real _dx, Real _dy,  Real _dz )
{
// simply add the translation to the current eye point
	m_eye.m_x += _dx;
	m_eye.m_y += _dy;
	m_eye.m_z += _dz;
	setViewMatrix();
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::moveBoth( Real _dx, Real _dy, Real _dz )
{
	m_eye.m_x +=_dx;
	m_eye.m_y +=_dy;
	m_eye.m_z +=_dz;
	m_look.m_x+=_dx;
	m_look.m_y+=_dy;
	m_look.m_z+=_dz;
	m_n=m_eye-m_look;
	m_u=m_up.cross(m_n);
	m_v.set(m_n.cross(m_u));
	// normalize vectors
	m_u.normalize();
	m_v.normalize();
	m_n.normalize();
	// pass to OpenGL
	setViewMatrix();
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::rotAxes( Vec4& io_a, Vec4& io_b,  const Real _angle  )
{
// rotate orthogonal vectors a (like x axis) and b(like y axis) through angle degrees
	// convert to radians
	Real ang = radians(_angle);
	// pre-calc cos and sine
	Real c = cos(ang);
	Real s = sin(ang);
	// tmp for io_a vector
	Vec4 t( c * io_a.m_x + s * io_b.m_x,  c * io_a.m_y + s * io_b.m_y,  c * io_a.m_z + s * io_b.m_z);
	// now set to new rot value
	io_b.set(-s * io_a.m_x + c * io_b.m_x, -s * io_a.m_y + c * io_b.m_y, -s * io_a.m_z + c * io_b.m_z);
	// put tmp into _a'
	io_a.set(t.m_x, t.m_y, t.m_z);
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::roll(Real _angle  )
{
  rotAxes(m_u, m_v, -_angle);
  setViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::pitch(Real _angle )
{
  rotAxes(m_n, m_v, _angle);
  setViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::yaw(Real _angle )
{
  rotAxes(m_u, m_n, _angle);
  setViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::moveEye( Real _dx, Real _dy,   Real _dz  )
{
	m_eye.m_x+=_dx;
	m_eye.m_y+=_dy;
	m_eye.m_z+=_dz;
	m_n=m_eye-m_look;
	m_u.set(m_up.cross(m_n));
	m_v.set(m_n.cross(m_u));
	// normalize the vectors
	m_u.normalize();
	m_v.normalize();
	m_n.normalize();
	// pass to OpenGL
	setViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::moveLook(Real _dx,  Real _dy,  Real _dz   )
{
	m_look.m_x+=_dx;
	m_look.m_y+=_dy;
	m_look.m_z+=_dz;
	m_n=m_eye-m_look;
	m_u.set(m_up.cross(m_n));
	m_v.set(m_n.cross(m_u));
	// normalise vectors
	m_u.normalize();
	m_v.normalize();
	m_n.normalize();
	// pass to OpenGL
	setViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::update()
{
	setViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::normalisedYaw( Real _angle )
{
  // build a rotation matrix around the y axis
  Mat4 mat;
  mat.identity();
  mat.rotateY(_angle);
  //multiply all three local coord vectors by the matrix
  m_u = m_u * mat;
  m_v = m_v * mat;
  m_n = m_n * mat;
  // reset the modelview matrix
  setViewMatrix();
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::normalisedRoll(Real _angle  )
{
  // build a rotation matrix around the y axis
  Mat4 mat;
  mat.identity();
  mat.rotateZ(_angle);
  //multiply all three local coord vectors by the matrix
  m_u = m_u * mat;
  m_v = m_v * mat;
  m_n = m_n * mat;
  // reset the modelview matrix
  setViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::normalisedPitch(Real _angle  )
{
  // build a rotation matrix around the y axis
  Mat4 mat;
  mat.identity();
  mat.rotateX(_angle);
  //multiply all three local coord vectors by the matrix
  m_u = m_u * mat;
  m_v = m_v * mat;
  m_n = m_n * mat;
  // reset the modelview matrix
  setViewMatrix();
}



//----------------------------------------------------------------------------------------------------------------------
void Camera::writeRib( RibExport &_rib ) const
{
	if(_rib.isOpen()!=0)
	{
		Real *M=(Real *)&m_viewMatrix.m_m;
		_rib.writeTabs();
		_rib.getStream() <<"# Camera transform from GraphicsLib Camera\n"  ;
		_rib.getStream() <<"# now we need to flip the Z axis\n";
		_rib.getStream() <<"Scale 1 1 -1 \n";

		_rib.getStream() <<"ConcatTransform [ ";
		for (int i=0; i<16; i++)
		{
			_rib.getStream() <<M[i]<<" ";
		}
		_rib.getStream() <<"]\n";
		_rib.getStream() <<"# now we Set the clipping \n";
		_rib.getStream() <<"Clipping "<<m_zNear<<" "<<m_zFar<<"\n";
		_rib.getStream() <<"Projection \"perspective\" \"fov\" ["<<m_fov<<"]\n";
		_rib.getStream() <<"#End of Camera from GraphicsLib\n";
	}
}
//----------------------------------------------------------------------------------------------------------------------
/// Code modified from http://www.lighthouse3d.com/opengl/viewfrustum/index.php?intro
///
void Camera::calculateFrustum()
{

    Real tang = (Real)tan(radians(m_fov) * 0.5) ;
    Real nh = m_zNear * tang;
    Real nw = nh * m_aspect;
    Real fh = m_zFar  * tang;
    Real fw = fh * m_aspect;

    Vec3 nc = (m_eye - m_n * m_zNear).toVec3();
    Vec3 fc = (m_eye - m_n * m_zFar).toVec3();

    m_ntl = nc + m_v.toVec3() * nh - m_u.toVec3() * nw;
    m_ntr = nc + m_v.toVec3() * nh + m_u.toVec3() * nw;
    m_nbl = nc - m_v.toVec3() * nh - m_u.toVec3() * nw;
    m_nbr = nc - m_v.toVec3() * nh + m_u.toVec3() * nw;

    m_ftl = fc + m_v.toVec3() * fh - m_u.toVec3() * fw;
    m_ftr = fc + m_v.toVec3() * fh + m_u.toVec3() * fw;
    m_fbl = fc - m_v.toVec3() * fh - m_u.toVec3() * fw;
    m_fbr = fc - m_v.toVec3() * fh + m_u.toVec3() * fw;
    m_planes[TOP].setPoints(m_ntr,m_ntl,m_ftl);
    m_planes[BOTTOM].setPoints(m_nbl,m_nbr,m_fbr);
    m_planes[LEFT].setPoints(m_ntl,m_nbl,m_fbl);
    m_planes[RIGHT].setPoints(m_nbr,m_ntr,m_fbr);
    m_planes[NEARP].setPoints(m_ntl,m_ntr,m_nbr);
    m_planes[FARP].setPoints(m_ftr,m_ftl,m_fbl);
}

void Camera::drawFrustum()
{
  std::vector<Vec3>points;

  // draw the sides as lines
  points.push_back(m_ntl);
  points.push_back(m_ftl);

  points.push_back(m_ntr);
  points.push_back(m_ftr);

  points.push_back(m_nbl);
  points.push_back(m_fbl);

  points.push_back(m_nbr);
  points.push_back(m_fbr);
  // near plane lines
  points.push_back(m_ntr);
  points.push_back(m_ntl);
  points.push_back(m_nbr);
  points.push_back(m_nbl);
  points.push_back(m_ntr);
  points.push_back(m_nbr);
  points.push_back(m_ntl);
  points.push_back(m_nbl);
  // far plane lines
  points.push_back(m_ftr);
  points.push_back(m_ftl);
  points.push_back(m_fbr);
  points.push_back(m_fbl);
  points.push_back(m_ftr);
  points.push_back(m_fbr);
  points.push_back(m_ftl);
  points.push_back(m_fbl);


  // now we create a VAO to store the data
 VertexArrayObject *vao=VertexArrayObject::createVOA(GL_LINES);
  // bind it so we can set values
  vao->bind();
  // set the vertex data (4 for x,y,z)
  vao->setData(points.size()*sizeof(Vec3),points[0].m_x);
  // now we set the attribute pointer to be 0 (as this matches vertIn in our shader)
  vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Vec3),0);
  // say how many indecis to be rendered
  vao->setNumIndices(points.size());
  vao->draw();
  // now unbind
  vao->unbind();
  vao->removeVOA();

}


CAMERAINTERCEPT Camera::isPointInFrustum( const Vec3 &_p ) const
{
	CAMERAINTERCEPT result = INSIDE;
	for(int i=0; i < 6; ++i)
	{

		if (m_planes[i].distance(_p) < 0)
		{
			return OUTSIDE;
		}
	}

	return result;
}


CAMERAINTERCEPT Camera::isSphereInFrustum(const Vec3 &_p,  Real _radius ) const
{

	CAMERAINTERCEPT result = INSIDE;
	Real distance;

	for(int i=0; i< 6; ++i)
	{
		distance = m_planes[i].distance(_p);
		if (distance < -_radius)
		{
			return OUTSIDE;
		}
		else if (distance < _radius)
		{
			result =  INTERSECT;
		}
	}
	return result;
}

/*
int Camera::boxInFrustum(AABox &b) {

	int result = INSIDE;
	for(int i=0; i < 6; i++) {

		if (pl[i].distance(b.getVertexP(pl[i].normal)) < 0)
			return OUTSIDE;
		else if (pl[i].distance(b.getVertexN(pl[i].normal)) < 0)
			result =  INTERSECT;
	}
	return(result);

 }

*/


/// end citation http://www.lighthouse3d.com/opengl/viewfrustum/index.php?intro


/*
<Camera>
    <fov>45</fov>
    <aspect>0.964198</aspect>
    <near>0.0001</near>
    <far>350</far>
    <eye>0 2 2 1 </eye>
    <look>0 0 0 1 </look>
    <up>0 1 0 1 </up>
</Camera>
*/
void Camera::writeXML(rapidxml::xml_document<> &_doc ,std::string _tag) const
{
//  char *nodeName = _doc.allocate_string(_tag.c_str());        // Allocate string and copy name into it
//  rapidxml::xml_node<>* root = _doc.allocate_node(rapidxml::node_element,nodeName);
//  _doc.append_node(root);
//  char *value = _doc.allocate_string(boost::str( boost::format(" %f") % m_fov).c_str());
//  rapidxml::xml_node<>* child = _doc.allocate_node(rapidxml::node_element, "fov",value);
//  root->append_node(child);

//  value = _doc.allocate_string(boost::str( boost::format(" %f") % m_aspect).c_str());
//  child = _doc.allocate_node(rapidxml::node_element, "aspect",value);
//  root->append_node(child);

//  value = _doc.allocate_string(boost::str( boost::format(" %f") % m_zNear).c_str());
//  child = _doc.allocate_node(rapidxml::node_element, "near",value);
//  root->append_node(child);

//  value = _doc.allocate_string(boost::str( boost::format(" %f") % m_zFar).c_str());
//  child = _doc.allocate_node(rapidxml::node_element, "far",value);
//  root->append_node(child);
//  m_eye.writeXML(_doc,root,"eye");
//  m_look.writeXML(_doc,root,"look");
//  m_up.writeXML(_doc,root,"up");



}


} // end namespace ngl

