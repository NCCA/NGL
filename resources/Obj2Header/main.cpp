#include <iostream>
#include <ngl/Obj.h>

int main(int argc, char **argv)
{
  if(argc <2)
  {
    std::cout<<"no obj file passed\n";

  }
  std::cerr<<"Loading Obj"<<std::endl;
  ngl::Obj *obj = new ngl::Obj();
  obj->load(argv[1],false);
  std::cout <<"num Verts"<<obj->getNumVerts()<<"\n";
  if( obj->isTriangular() != true)
  {
    std::cout<< "need triangular mesh for this sorry \n";
    delete obj;
    exit(EXIT_FAILURE);
  }
  // get the obj data so we can process it locally
  std::vector <ngl::Vec3> verts=obj->getVertexList();
  std::vector <ngl::Face> faces=obj->getFaceList();
  std::vector <ngl::Vec3> tex=obj->getTextureCordList();
  std::vector <ngl::Vec3> normals=obj->getNormalList();

  unsigned int nFaces=faces.size();
  unsigned int nNorm=normals.size();
  unsigned int nTex=tex.size();
    // loop for each of the faces

  struct vertData
  {
    GLfloat u; // tex cords from obj
    GLfloat v; // tex cords
    GLfloat nx; // normal from obj mesh
    GLfloat ny;
    GLfloat nz;
    GLfloat x; // position from obj
    GLfloat y;
    GLfloat z;
  };
  vertData d;
  unsigned long int size=0;
  for(unsigned int i=0;i<nFaces;++i)
  {
      // now for each triangle in the face (remember we ensured tri above)
      for(int j=0;j<3;++j)
      {
        // pack in the vertex data first
        d.x=verts[faces[i].m_vert[j]].m_x;
        d.y=verts[faces[i].m_vert[j]].m_y;
        d.z=verts[faces[i].m_vert[j]].m_z;
        // now if we have norms of tex (possibly could not) pack them as well
        if(nNorm >0 && nTex > 0)
        {
          d.nx=normals[faces[i].m_norm[j]].m_x;
          d.ny=normals[faces[i].m_norm[j]].m_y;
          d.nz=normals[faces[i].m_norm[j]].m_z;

          d.u=tex[faces[i].m_tex[j]].m_x;
          d.v=tex[faces[i].m_tex[j]].m_y;

        }
        // now if neither are present (only verts like Zbrush models)
        else if(nNorm ==0 && nTex==0)
        {
          d.nx=0;
          d.ny=0;
          d.nz=0;
          d.u=0;
          d.v=0;
        }
        // here we've got norms but not tex
        else if(nNorm >0 && nTex==0)
        {
          d.nx=normals[faces[i].m_norm[j]].m_x;
          d.ny=normals[faces[i].m_norm[j]].m_y;
          d.nz=normals[faces[i].m_norm[j]].m_z;
          d.u=0;
          d.v=0;

        }
        // here we've got tex but not norm least common
        else if(nNorm ==0 && nTex>0)
        {
          d.nx=0;
          d.ny=0;
          d.nz=0;
          d.u=tex[faces[i].m_tex[j]].m_x;
          d.v=tex[faces[i].m_tex[j]].m_y;
        }
        std::cout.precision(5);
        std::cout.setf(std::ios::fixed|std::ios::adjustfield);
        std::cout<<d.u<<"f,"<<d.v<<"f,"<<d.nx<<"f,"<<d.ny<<"f,"<<d.nz<<"f,"<<d.x<<"f,"<<d.y<<"f,"<<d.z<<"f,\n";
        size+=8;
    }
   }

  std::cout<<size<<"\n";

}
