#include "XMLSerializer.h"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Plane.h"
#include "Transformation.h"
#include "fmt/format.h"
namespace ngl
{


  void XMLSerializer::writeToXML(const std::string &_s, const std::string &_tag)
  {
    char *nodeName = m_doc.allocate_string(_tag.c_str());        // Allocate string and copy name into it

    char *value = m_doc.allocate_string(_s.c_str());
    rapidxml::xml_node<>* root = m_doc.allocate_node(rapidxml::node_element, nodeName,value);
    m_doc.append_node(root);
  }

  void XMLSerializer::writeToXML(const std::string &_s, rapidxml::xml_node<> *_parent,const std::string &_tag)
  {
    char *nodeName = m_doc.allocate_string(_tag.c_str());        // Allocate string and copy name into it
    char *value = m_doc.allocate_string(_s.c_str());
    rapidxml::xml_node<>* root = m_doc.allocate_node(rapidxml::node_element, nodeName,value);
    _parent->append_node(root);
  }

  void XMLSerializer::addNode(const std::string &_tag)
  {
    char *nodeName = m_doc.allocate_string(_tag.c_str());        // Allocate string and copy name into it
    rapidxml::xml_node<>* root = m_doc.allocate_node(rapidxml::node_element,nodeName);
    m_currentNode=root;
    m_doc.append_node(m_currentNode);
  }

  void XMLSerializer::addNode(const std::string &_tag,rapidxml::xml_node<> *_parent)
  {
    char *nodeName = m_doc.allocate_string(_tag.c_str());        // Allocate string and copy name into it
    rapidxml::xml_node<>* root = m_doc.allocate_node(rapidxml::node_element,nodeName);
    m_currentNode=root;
    _parent->append_node(m_currentNode);
  }

  XMLSerializer::XMLSerializer(const std::string &_fname, ACCESSMODE _mode)
  {
    rapidxml::xml_node<>* declatation;

    declatation = m_doc.allocate_node(rapidxml::node_declaration);
    declatation->append_attribute(m_doc.allocate_attribute("version", "1.0"));
    declatation->append_attribute(m_doc.allocate_attribute("encoding", "us-ascii"));
    m_doc.append_node(declatation);
    m_fname=_fname;
    m_mode=_mode;
    m_currentNode=0;
  }

  XMLSerializer::~XMLSerializer()
  {
    if(m_mode ==WRITE)
    {
      std::ofstream file_stored(m_fname.c_str());
      file_stored << m_doc;
      file_stored.close();
      m_doc.clear();
    }
  }

  void XMLSerializer::read(AABB &_s)
  {

  }

  void XMLSerializer::write(const AABB &_s)
  {

  }

  void XMLSerializer::read(BBox &_s)
  {

  }

  void XMLSerializer::write(const BBox &_s)
  {

  }

  void XMLSerializer::read(BezierCurve &_s)
  {

  }

  void XMLSerializer::write(const BezierCurve &_s)
  {

  }

  void XMLSerializer::read(Camera &_s)
  {

  }



  void XMLSerializer::write(const Camera &_s,const std::string &_tag)
  {

    char *nodeName = m_doc.allocate_string(_tag.c_str());        // Allocate string and copy name into it
    rapidxml::xml_node<>* root = m_doc.allocate_node(rapidxml::node_element,nodeName);
    m_doc.append_node(root);
    writeToXML(fmt::format(" {}", _s.getFOV() ),root,"fov");
    writeToXML(fmt::format(" {}" , _s.getAspect() ),root,"aspect");
    writeToXML(fmt::format(" {}", _s.getNear() ),root,"near");
    writeToXML(fmt::format(" {}", _s.getFar() ),root,"far");
    write(_s.getEye(),root,"eye");
    write(_s.getLook(),root,"look");
    write(_s.getUp(),root,"up");

  }

  void XMLSerializer::read(Colour &_s)
  {

  }

  void XMLSerializer::write(const Colour &_s,std::string _tag)
  {
    writeToXML(fmt::format(" {} {} {} {}" , _s.m_r , _s.m_g , _s.m_b , _s.m_a ),_tag);
  }


  void XMLSerializer::write(const Colour &_s,rapidxml::xml_node<> *_parent, std::string _tag)
  {
    writeToXML(fmt::format(" {} {} {} {}" , _s.m_r , _s.m_g , _s.m_b , _s.m_a ),_parent,_tag);
  }

  void XMLSerializer::read(Light &_s)
  {

  }

  void XMLSerializer::write(const Light &_s,const std::string &_tag)
  {
    char *nodeName = m_doc.allocate_string(_tag.c_str());        // Allocate string and copy name into it
    rapidxml::xml_node<>* root = m_doc.allocate_node(rapidxml::node_element,nodeName);
    m_doc.append_node(root);

    write(_s.getPos(),root,"position");
    write(_s.getColour(),root,"colour");
    write(_s.getSpecColour(),root,"specColour");
    //writeToXML(boost::str( boost::format(" {}") % _s.));
    //  m_position.writeXML(_doc,root,"position");
    //  m_diffuse.writeXML(_doc,root,"colour");
    //  m_specular.writeXML(_doc,root,"specColour");
    //  char *value = _doc.allocate_string(boost::str( boost::format(" {}") % m_constantAtten).c_str());
    //  rapidxml::xml_node<>* child = _doc.allocate_node(rapidxml::node_element, "constantAtten",value);
    //  root->append_node(child);

    //  value = _doc.allocate_string(boost::str( boost::format(" {}") % m_linearAtten).c_str());
    //  child = _doc.allocate_node(rapidxml::node_element, "linearAtten",value);
    //  root->append_node(child);

    //  value = _doc.allocate_string(boost::str( boost::format(" {}") % m_quadraticAtten).c_str());
    //  child = _doc.allocate_node(rapidxml::node_element, "quadraticAtten",value);
    //  root->append_node(child);
  }

  void XMLSerializer::read(Mat3 &_s)
  {

  }

  void XMLSerializer::write( Mat3 &_s, std::string _tag)
  {
        writeToXML(fmt::format(" {0} {1} {2} {3} {4} {5} {6} {7} {8}"
                            , _s.m_openGL[0] ,_s.m_openGL[1] , _s.m_openGL[2]
                            , _s.m_openGL[3] , _s.m_openGL[4] , _s.m_openGL[5]
                            , _s.m_openGL[6] , _s.m_openGL[7] , _s.m_openGL[8] ),_tag);

  }

  void XMLSerializer::read(Mat4 &_s)
  {

  }

  void XMLSerializer::write( Mat4 &_s, std::string _tag)
  {
    Real *openGL= _s.openGL();

    writeToXML(fmt::format(" {0} {1} {2} {3} {4} {5} {6} {7} {8} {9} {10} {11} {12} {13} {14} {15}"
                                         , openGL[0] , openGL[1] , openGL[2] , openGL[3]
                                         , openGL[4] , openGL[5] , openGL[6] , openGL[7]
                                         , openGL[8] , openGL[9] , openGL[10] , openGL[11]
                                         , openGL[12] , openGL[13] , openGL[14] , openGL[15]),_tag);

  }

  void XMLSerializer::read(Material &_s)
  {

  }

  void XMLSerializer::write(const Material &_s, const std::string &_tag)
  {
    char *nodeName = m_doc.allocate_string(_tag.c_str());        // Allocate string and copy name into it

    rapidxml::xml_node<>* root = m_doc.allocate_node(rapidxml::node_element,nodeName);
    m_doc.append_node(root);
    write(_s.getDiffuse(),root,"diffuse");
    write(_s.getSpecular(),root,"specular");
    write(_s.getAmbient(),root,"ambient");
    writeToXML(fmt::format(" {0}" , _s.getSpecularExponent()),root,"specularExponent");
    writeToXML(fmt::format(" {0}" , _s.getTransparency()),root,"transparency");
    writeToXML(fmt::format(" {0}" , _s.getRoughness() ),root,"roughness");
  }

  void XMLSerializer::read(PathCamera &_s)
  {

  }

  void XMLSerializer::write(const PathCamera &_s, const std::string &_tag)
  {

  }

  void XMLSerializer::read(Plane &_s)
  {

  }

  void XMLSerializer::write(const Plane &_s,const std::string &_tag)
  {

  }

  void XMLSerializer::read(Quaternion &_s)
  {

  }


  void XMLSerializer::write(const Quaternion &_s, const std::string &_tag)
  {
    writeToXML(fmt::format(" {0} {1} {2} {3}"  , _s.getS() , _s.getX() , _s.getY() , _s.getZ() ),_tag);

  }

  void XMLSerializer::read(SpotLight &_s)
  {

  }

  void XMLSerializer::write(const SpotLight &_s, const std::string &_tag)
  {

  }


  void XMLSerializer::read(Transformation &_s)
  {

  }

  void XMLSerializer::write(const Transformation &_s, const std::string &_tag)
  {



    char *nodeName = m_doc.allocate_string(_tag.c_str());        // Allocate string and copy name into it

    rapidxml::xml_node<>* root = m_doc.allocate_node(rapidxml::node_element,nodeName);
    m_doc.append_node(root);

    write(_s.getPosition(),root,"position");
    write(_s.getRotation(),root,"rotation");
    write(_s.getScale(),root,"scale");

   }

  void XMLSerializer::read(Vec2 &_s)
  {

  }

  void XMLSerializer::write(const Vec2 &_s,std::string _tag)
  {
    writeToXML(fmt::format(" {0} {1} " , _s.m_x , _s.m_y  ),_tag);


  }

  void XMLSerializer::write(const Vec2 &_s,rapidxml::xml_node<> *_parent, std::string _tag)
  {
    writeToXML(fmt::format(" {0} {1}  " , _s.m_x , _s.m_y ),_parent,_tag);
  }



  void XMLSerializer::read(Vec3 &_s)
  {

  }

  void XMLSerializer::write(const Vec3 &_s, std::string _tag)
  {
    writeToXML(fmt::format(" {0} {1} {2} "  , _s.m_x , _s.m_y , _s.m_z ),_tag);
  }
  void XMLSerializer::write(const Vec3 &_s,rapidxml::xml_node<> *_parent, std::string _tag)
  {

    writeToXML(fmt::format(" {0} {1} {2} " , _s.m_x , _s.m_y , _s.m_z  ),_parent,_tag);

  }
  void XMLSerializer::read(Vec4 &_s)
  {
    //  if(_doc->tokenType() != QXmlStreamReader::StartElement &&
    //     _doc->name() == "Vec3")
    //  {
    //    std::cerr<<"error with token type for xml parse\n";
    //  }


  }

  void XMLSerializer::write(const Vec4 &_s, std::string _tag)
  {
    writeToXML(fmt::format(" {0} {1} {2} {3}" , _s.m_x , _s.m_y , _s.m_z , _s.m_w),_tag);
  }


  void XMLSerializer::write(const Vec4 &_s, rapidxml::xml_node<> *_parent, std::string _tag)
  {
   writeToXML(fmt::format(" {0} {1} {2} {3}"  , _s.m_x , _s.m_y , _s.m_z , _s.m_w),_parent,_tag);
  }


}
