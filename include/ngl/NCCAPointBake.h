/*
  Copyright (C) 2010 Jon Macey

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
#ifndef NCCAPOINTBAKE_H__
#define NCCAPOINTBAKE_H__
//----------------------------------------------------------------------------------------------------------------------
/// @file NCCAPointBake.h
/// @brief simple point baked animation data for animation data export
//----------------------------------------------------------------------------------------------------------------------
// must include types.h first for Real and GLEW if required
#include "Obj.h"
#include "Types.h"
#include "Vec4.h"
#include <vector>
#include <string>

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class NCCAPointBake  "include/NCCAPointBake.h"
/// @brief Class to load and manipulate NCCAPointBake data, this will replace the Houdini Clip
/// files as they are now not supported in the educational version of Houdini
/** @verbatim

<?xml version="1.0" encoding="UTF-8" ?>
<NCCAPointBake>
	<MeshName> The name of the mesh exported </MeshName>
	<NumVerts> the number of verts </NumVerts>
	<StartFrame> start frame from export </StartFrame>
	<EndFrame> end frame from export </EndFrame>
	<NumFrames> Total number of frames </NumFrame>
	<TranslateMode> if data for translations are absolute or relative </TranslateMode>
	<Frame number="0">
		<Vertex number="0" attrib="translate"> 2.145875 9.490916 33.391218 </Vertex>
		etc
	</Frame>
</NCCAPointBake>
@endverbatim
 **/
/// @author Jonathan Macey
/// @version 1.0
/// @date Last Revision 2/09/10
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT NCCAPointBake
{
friend class AbstractMesh;
public :
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief ctor for the clip
  //----------------------------------------------------------------------------------------------------------------------
  NCCAPointBake() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief the dtor erases all clip data allocated and also destroys the Obj reference held in the clip
  //----------------------------------------------------------------------------------------------------------------------
  ~NCCAPointBake() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief   ctor using a clip and an obj
  /// @param[in] _fileName the name of the bake file to load
  //----------------------------------------------------------------------------------------------------------------------
  NCCAPointBake( const std::string &_fileName ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  Set the current Frame and map the clip for that frame to the obj
  /// @param[in] frame the frame to set
  //----------------------------------------------------------------------------------------------------------------------
  void setFrame(const unsigned int frame ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  method to load a point baked file
  /// @param[in] _fileName the file to load
  //----------------------------------------------------------------------------------------------------------------------
  bool loadPointBake( const std::string &_fileName) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  method to load a binary point baked file
  /// @param[in] _fileName the file to load
  //----------------------------------------------------------------------------------------------------------------------
  bool loadBinaryPointBake(const std::string &_fileName) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  method to save a binary point baked file basically re-ordered data only
  /// @param[in] _fileName the file to load
  //----------------------------------------------------------------------------------------------------------------------
  bool saveBinaryPointBake( const std::string &_fileName) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  method to attach a mesh to the data
  /// this method will check for basic vetex compatibility and then re-order the data
  /// to match the VBO structure of the mesh
  /// @param[in] _mesh the mesh to attach
  /// @returns true is mesh can be attached else false
  //----------------------------------------------------------------------------------------------------------------------
  bool attachMesh(AbstractMesh *_mesh) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  set the attached mesh to the current frame
  /// @param[in] _frame the frame to set the mesh to
  //----------------------------------------------------------------------------------------------------------------------
  void setMeshToFrame( const unsigned int _frame) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  return the number of Frames loaded from the PointBake file
  /// @returns the number of frames
  //----------------------------------------------------------------------------------------------------------------------
  inline unsigned int getNumFrames() const  noexcept{return m_numFrames-1;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  return the number of verts loaded from the PointBake file
  /// @returns the number of verts
  //----------------------------------------------------------------------------------------------------------------------
  inline unsigned int getNumVerts() const  noexcept{return m_nVerts;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  get a Raw data pointer to the un-sorted PointBake data
  /// @returns a pointer to the data
  //----------------------------------------------------------------------------------------------------------------------
  inline  std::vector < std::vector<Vec3> > & getRawDataPointer()   noexcept{return m_data;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  get a Raw data pointer to the un-sorted PointBake for a particular frame
  /// @param[in] _f the frame to access
  /// @returns a pointer to the data at frame _f
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<Vec3> & getRawDataPointerAtFrame(unsigned int _f) noexcept;


protected :
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief method to create the vertorder container with the correct vertex order in place to match
  /// that of the obj file
  //----------------------------------------------------------------------------------------------------------------------
    void reorderVerts() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the number of frames in the clip file
  //----------------------------------------------------------------------------------------------------------------------
  unsigned int m_numFrames;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Current active frame when animating
  //----------------------------------------------------------------------------------------------------------------------
  unsigned int m_currFrame;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  The actual data of the clip stored per vertex in sequence v0 - vn and then per frame frame
  /// index is always frame 0- endframe despite the start / end values in the clip file
  //----------------------------------------------------------------------------------------------------------------------
  std::vector < std::vector<Vec3> > m_data;
   //----------------------------------------------------------------------------------------------------------------------
  /// @brief  Number of verts in the actual clip
  //----------------------------------------------------------------------------------------------------------------------
  unsigned int m_nVerts;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  the name of the mesh
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_meshName;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the start frame
  //----------------------------------------------------------------------------------------------------------------------
  unsigned int m_startFrame;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the end frame
  //----------------------------------------------------------------------------------------------------------------------
  unsigned int m_endFrame;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief pointer to mesh attatched to data
  //----------------------------------------------------------------------------------------------------------------------
  AbstractMesh *m_mesh;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if we have a binary or xml based file loaded
  //----------------------------------------------------------------------------------------------------------------------
  bool m_binFile;
}; // end class

} // end namespace ngl


#endif // end include guard

//----------------------------------------------------------------------------------------------------------------------

