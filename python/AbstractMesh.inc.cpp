namespace ngl
{

boost::python::list AbstractMesh::getVertexListPY()
{
	unsigned int size=m_verts.size();
	boost::python::list verts;
	for(unsigned int i=0; i<size; ++i)
	{
			verts.append(m_verts[i].m_x);
			verts.append(m_verts[i].m_y);
			verts.append(m_verts[i].m_z);
	}
    return verts;
}


boost::python::list AbstractMesh::getNormalListPY()
{
	unsigned int size=m_norm.size();
	boost::python::list verts;
	for(unsigned int i=0; i<size; ++i)
	{
			verts.append(m_norm[i].m_x);
			verts.append(m_norm[i].m_y);
			verts.append(m_norm[i].m_z);
	}
    return verts;
}


boost::python::list AbstractMesh::getTextureCordListPY()
{
	unsigned int size=m_tex.size();
	boost::python::list verts;
	for(unsigned int i=0; i<size; ++i)
	{
			verts.append(m_tex[i].m_x);
			verts.append(m_tex[i].m_y);
			verts.append(m_tex[i].m_z);
	}
    return verts;
}


}
