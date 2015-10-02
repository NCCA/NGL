/*
  Copyright (C) 2015 Jon Macey

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
#ifndef IMAGE_H__
#define IMAGE_H__
/// @file Image.h
/// @brief A generic Image loader / wrapper for different Image libs
/// this allows us to load an image to be used (for example) in the Texture class
/// as there are many different ways to do this this class has compile time options
/// to choose the image loading library to use At present support is going to be
/// QImage (for Qt builds) ImageMagic, OpenImageIO DevIL
/// Image data will be stored in either RGB or RGBA contiguos unsigned char data
#include <string>
#include <boost/scoped_array.hpp>
#include <Types.h>
namespace ngl
{

class Image
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor
  //----------------------------------------------------------------------------------------------------------------------
  Image() ;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor passing in filename
  /// @param _fname the name of the file to load.
  //----------------------------------------------------------------------------------------------------------------------
  Image(const std::string &_fname);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor
  /// @param _i image to copy
  //----------------------------------------------------------------------------------------------------------------------
  Image(const Image &_i);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor as we use a smart pointer the data will release automatically
  //----------------------------------------------------------------------------------------------------------------------
  ~Image(){}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief load the image data, this will clear the previous data and attempt to load the new image data
  /// @param _fname name of the file to load
  /// @returns true is loaded ok, else false
  //----------------------------------------------------------------------------------------------------------------------
  bool load(const std::string &_fname);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief raw access to unsigned char pixel data
  /// @returns a pointer to the first image pixel element.
  //----------------------------------------------------------------------------------------------------------------------
  unsigned char *getPixels() const {return m_data.get();}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Get the width of the texture
  /// @return width of the texture
  //----------------------------------------------------------------------------------------------------------------------
  GLuint getWidth()const {return m_width;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Get the height of the texture
  /// @return height of the texture
  //----------------------------------------------------------------------------------------------------------------------
  GLuint getHeight()const {return m_height;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Get the pixel format
  /// @return pixel format of the texture
  //----------------------------------------------------------------------------------------------------------------------
  GLuint getFormat()const {return m_format;}
private :
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the actual image data loaded packed in r,g,b,(a) format in contiguous memory
	/// stored in a smart_pointer for safety
	//----------------------------------------------------------------------------------------------------------------------
	boost::scoped_array <unsigned char> m_data;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the size of the image in the X direction
	//----------------------------------------------------------------------------------------------------------------------
	GLuint m_width;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the size of the image in the Y direction
	//----------------------------------------------------------------------------------------------------------------------
	GLuint m_height;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief bits per pixel (RGB / RGBA)
	//----------------------------------------------------------------------------------------------------------------------
	GLuint m_bpp;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief image format, use GL types for this as we are going to use this class mainly for OpenGL
	//----------------------------------------------------------------------------------------------------------------------
	GLuint m_format;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief loaded flag
	//----------------------------------------------------------------------------------------------------------------------
	bool m_loaded;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief do we have an alpha channel
	//----------------------------------------------------------------------------------------------------------------------
	bool m_hasAlpha;

};




}

#endif
