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

#warning This class is marked for deprecation
#ifndef REMOVEDDEPRECATED

#ifndef TRANSFORMSTACK_H__
#define TRANSFORMSTACK_H__
/// @file TransformStack.h
/// @brief a simple transformation stack of transform objects used to mimic GL stack
#include "Transformation.h"
#include "Types.h"
#include <deque>
#include <vector>
#include <cmath>

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
/// @class TransformStack "include/ngl/TransformStack.h"
/// @brief TransformStack Class to replicate basic Affine Transfors ala OpenGL push/pop matrix
/// @authors Jonathan Macey / Vince Bonnet
/// @version 1.0
/// @date 24/03/10 Initial build
//----------------------------------------------------------------------------------------------------------------------


  class NGL_DLLEXPORT TransformStack
  {

  public:
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief ctor will always create an identity matrix as top of stack
      //----------------------------------------------------------------------------------------------------------------------
      TransformStack();
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief copy ctor with reference object
      /// @param[in] _m the stack to copy
      //----------------------------------------------------------------------------------------------------------------------
      TransformStack( const TransformStack& _m  );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief push the current matrix onto the stack
      /// make the new matrix the identity matrix
      //----------------------------------------------------------------------------------------------------------------------
      void pushTransform();
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief push the current matrix onto the stack and place a copy
      /// of the pushed matrix as the current one
      //----------------------------------------------------------------------------------------------------------------------
      void pushTransformAndCopy();
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief pop the previous top of stack
      //----------------------------------------------------------------------------------------------------------------------
      void popTransform();
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief return the current active matrix
      /// @returns the current top of stack
      //----------------------------------------------------------------------------------------------------------------------
      inline Transformation   &getCurrentTransform(){return m_current;}
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief return the global transform
      /// @returns the current top of stack
      //----------------------------------------------------------------------------------------------------------------------
      inline Transformation   &getGlobalTransform(){return m_global;}
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief return the Current and Global matrix multiplied together
      //----------------------------------------------------------------------------------------------------------------------
      Transformation  &getCurrAndGlobal();

      //----------------------------------------------------------------------------------------------------------------------
      /// @brief set the position of the currently active transform (Top of stack) from an Vector
      /// @param _pos the position vector to set
      //----------------------------------------------------------------------------------------------------------------------
      void setPosition(const Vec4 &_pos );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief set the position of the currently active transform (Top of stack) from an Vector
      /// @param _pos the position vector to set
      //----------------------------------------------------------------------------------------------------------------------
      void setPosition(const Vec3 &_pos );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief set the position of the currently active transform (Top of stack) from 3 floats
      /// @param[in] _x the x position
      /// @param[in] _y the y position
      /// @param[in] _z the z position
      //----------------------------------------------------------------------------------------------------------------------
      void setPosition(Real _x,Real _y,  Real _z );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief method add to the existing set the position
      /// @param[in] _position position
      //----------------------------------------------------------------------------------------------------------------------
      void addPosition( const Vec3& _position  );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief method add to the existing set the position
      /// @param[in] _x x position value
      /// @param[in] _y y position value
      /// @param[in] _z z position value
      //----------------------------------------------------------------------------------------------------------------------
      void addPosition( Real _x, Real _y,  Real _z );

      //----------------------------------------------------------------------------------------------------------------------
      /// @brief set the scale of the currently active transform (Top of stack) from an Vector
      /// @param _scale the Scale vector to set
      //----------------------------------------------------------------------------------------------------------------------
      void setScale( const Vec4 &_scale );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief set the scale of the currently active transform (Top of stack) from an Vector
      /// @param _scale the Scale vector to set
      //----------------------------------------------------------------------------------------------------------------------
      void setScale( const Vec3 &_scale  );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief set the scale of the currently active transform (Top of stack) from 3 floats
      /// @param[in] _x the x scale
      /// @param[in] _y the y scale
      /// @param[in] _z the z scale
      //----------------------------------------------------------------------------------------------------------------------
      void setScale( Real _x, Real _y,  Real _z );

      //----------------------------------------------------------------------------------------------------------------------
      /// @brief add the scale of the currently active transform (Top of stack) from an Vector
      /// @param _scale the Scale vector to set
      //----------------------------------------------------------------------------------------------------------------------
      void addScale(const Vec3 &_scale );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief add to the scale of the currently active transform (Top of stack) from 3 floats
      /// @param[in] _x the x scale
      /// @param[in] _y the y scale
      /// @param[in] _z the z scale
      //----------------------------------------------------------------------------------------------------------------------
      void addScale( Real _x,  Real _y,  Real _z  );

      //----------------------------------------------------------------------------------------------------------------------
      /// @brief set the rotation of the currently active transform (Top of stack) from an Vector
      /// @param _rot the rotation vector to set
      //----------------------------------------------------------------------------------------------------------------------
      void setRotation(const Vec4 &_rot );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief set the rotation of the currently active transform (Top of stack) from an Vector
      /// @param _rot the rotation vector to set
      //----------------------------------------------------------------------------------------------------------------------
      void setRotation( const Vec3 &_rot );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief set the rotation of the currently active transform (Top of stack) from 3 floats
      /// @param[in] _x the x rotation
      /// @param[in] _y the y rotation
      /// @param[in] _z the z rotation
      //----------------------------------------------------------------------------------------------------------------------
      void setRotation( Real _x, Real _y,  Real _z );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief set the rotation of the currently active transform (Top of stack) from an Vector
      /// @param _rot the rotation vector to set
      //----------------------------------------------------------------------------------------------------------------------
      void addRotation( const Vec3 &_rot );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief set the rotation of the currently active transform (Top of stack) from 3 floats
      /// @param[in] _x the x rotation
      /// @param[in] _y the y rotation
      /// @param[in] _z the z rotation
      //----------------------------------------------------------------------------------------------------------------------
      void addRotation(Real _x, Real _y,Real _z );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief Set the current top of the stack matrix to _m
      /// @param[in] _m the value to set the current matrix
      //----------------------------------------------------------------------------------------------------------------------
      inline void setCurrent(const Transformation &_m  )
                             {m_current=_m;}
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief Set the current top of the stack matrix to _m
      /// @param[in] _m the value to set the current matrix
      //----------------------------------------------------------------------------------------------------------------------

      inline void setCurrent(const Mat4 &_m )
      {
        m_current.setMatrix(_m);
      }

      //----------------------------------------------------------------------------------------------------------------------
      /// @brief Set the current top of the stack matrix to _m
      /// @param[in] _m the value to set the current matrix
      //----------------------------------------------------------------------------------------------------------------------
      inline void setGlobal(const Transformation &_m )
      {
        m_global=_m;
      }
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief load the current transform matrix to the shader
      /// @param[in] _param the name of the parameter to set (varying mat4)
      /// @param[in] _which which matrix mode to use
      //----------------------------------------------------------------------------------------------------------------------
      void loadMatrixToShader( std::string _param, ACTIVEMATRIX _which=NORMAL  );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief load the current * global transform matrix to the shader
      /// @param[in] _param the name of the parameter to set (varying mat4)
      /// @param[in] _which which matrix mode to use
      //----------------------------------------------------------------------------------------------------------------------
      void loadGlobalAndCurrentMatrixToShader( std::string _param, ACTIVEMATRIX _which=NORMAL );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief load the current * global transform matrix to the shader
      /// @param[in] _param the name of the parameter to set (varying mat4)
      /// @param[in] _which which matrix mode to use
      //----------------------------------------------------------------------------------------------------------------------
      void loadGlobalMatrixToShader( std::string _param, ACTIVEMATRIX _which=NORMAL );
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief load the current * global transform matrix to the shader
      /// @return the global matrix
      //----------------------------------------------------------------------------------------------------------------------
      inline Mat4  getGlobalMatrix()
      {
        return m_globalMatrix;
      }
   protected :
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief the current active transfom
      //----------------------------------------------------------------------------------------------------------------------
      Transformation m_current;
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief a global transformation useful for adding global TRS to
      /// all transforms, to use this use the GloabAndCurrent methods
      //----------------------------------------------------------------------------------------------------------------------
      Transformation m_global;
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief a current and global transformation useful for adding global TRS to
      /// all transforms, to use this use the GlobalAndCurrent methods
      //----------------------------------------------------------------------------------------------------------------------
      Transformation m_currentAndGlobal;
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief this matrix is the right Multiplied accumulation of all transforms
      /// it contains the current overall transform in a similar way to OpenGL Push/Pop
      /// matrix operations do
      //----------------------------------------------------------------------------------------------------------------------
      Mat4 m_globalMatrix;
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief the stack containing the other Transforms
      //----------------------------------------------------------------------------------------------------------------------
      std::vector<Transformation> m_stack;
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief the max stack size this just put this in
      /// to be in line with OpenGL but could overiddedn
      //----------------------------------------------------------------------------------------------------------------------
      const static int MAXNGLTRANSFORMSTACKSIZE=40;
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief current index into the stack
      //----------------------------------------------------------------------------------------------------------------------
      unsigned int m_index;


      #ifdef NO_PYTHON_LIB
        public :
          std::string pyPrint();
      #endif
};
}

#endif
#endif // REMOVEDDEPRECATED
//----------------------------------------------------------------------------------------------------------------------
