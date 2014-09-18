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
#ifndef NGLASSERT_H__
#define NGLASSERT_H__

//----------------------------------------------------------------------------------------------------------------------
/// @file NGLassert.h
/// @brief re impliment asserts so we don't exit on failure
//----------------------------------------------------------------------------------------------------------------------
/// @brief re-define the standard assert to work for ngl
/// first check to see if assert is defined and undef it
/// this file is to replace the std C++ Assert functions
/// These are turned on and off by specifying the _DEBUG flag
/// in the make file (-DNGL_DEBUG in the FLAGS line.
/// These are simmilar to the normal assert macros but don't exit
/// the program as our asserts are not usually fatal. Also can use the
/// assert in the TODO list to flag methods which have not yet been
/// implimented.
//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
// now if we are in debug mode use these macros
#if defined(NGL_DEBUG)

	#include <iostream>
	#define NGL_ASSERT(X) \
		 if(!(X)) \
		 { \
			 std::cerr << "Assertion failed :"<< #X \
			 << "\nFailure occured on line " \
			 << __LINE__ << " of source file :" \
			 << "\n \""<<__FILE__<<"\"" << std::endl; \
		 }


//----------------------------------------------------------------------------------------------------------------------


#endif // #if defined(NGL_DEBUG)

#endif // __NGLASSERT_H__









