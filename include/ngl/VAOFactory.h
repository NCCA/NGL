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

#include "Types.h"
#include "AbstractVAO.h"
#include <unordered_map>
#include <string>
#include <functional>
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
    public :

    private :
    static std::unordered_map<std::string, std::function<AbstractVAO *(GLenum _mode)>> m_renderers;

};


}

#endif
