/*
  Copyright (C) 2016 Jon Macey

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
#ifndef VAOFACTORY_H_
#define VAOFACTORY_H_

#include "AbstractVAO.h"
#include "Types.h"
#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class VAOFactory "include/VAOFactory.h"
/// @brief extensible factory to allow different types of VAO's to be generated for NGL
/// two default ones will be created but allows the user to do more complex stuff if required
/// @author Jonathan Macey
/// @version 1.0
/// @date 6/4/16
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT VAOFactory
{
    public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Add a new vao creator to our factory
  /// @param _type the name of the creator function registered
  /// @param _cb the creator function must pass in a GLenum for the type to create and return an AbstractVAO
  //----------------------------------------------------------------------------------------------------------------------
  static void registerVAOCreator(std::string_view _type, std::function< std::unique_ptr< AbstractVAO >(GLenum _mode) > _cb);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Remove an existing vao creator from the map
  /// @param _type the name of the creator to remove
  //----------------------------------------------------------------------------------------------------------------------
  static void unregisterVAOCreator(std::string_view _type);
  //----------------------------------------------------------------------------------------------------------------------
  /// Create an instance of a named VAO from a creator
  /// @param _type the name of the creator to use from our factory
  /// @param _mode the initial mode to create (i.e. GL_TRIANGLES etc)
  /// @returns AbstractAVO *
  //----------------------------------------------------------------------------------------------------------------------
  static std::unique_ptr< AbstractVAO > createVAO(std::string_view _type, GLenum _mode = GL_TRIANGLES);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief debug function to list all creators
  //----------------------------------------------------------------------------------------------------------------------
  static void listCreators()  noexcept;

  static size_t getNumCreators()  noexcept {return m_vaoCreators.size();}

  private:
  //----------------------------------------------------------------------------------------------------------------------
  //----------------------------------------------------------------------------------------------------------------------
  static std::unordered_map< std::string, std::function< std::unique_ptr< AbstractVAO >(GLenum _mode) > > m_vaoCreators;
};

} // namespace ngl

#endif
