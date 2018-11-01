/**
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
 **/
#ifndef RANDOM_H_
#define RANDOM_H_
//----------------------------------------------------------------------------------------------------------------------
/// @file Random.h
/// @brief an encapsulation of the std::random classes
//----------------------------------------------------------------------------------------------------------------------
// must include types.h first for Real and GLEW if required
#include "Singleton.h"
#include "Vec4.h"

#include <unordered_map>
#include <random>
namespace ngl
{

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief enumerated list of the different distributions we can
  /// add to the generator,
  //----------------------------------------------------------------------------------------------------------------------
  enum  class RANDDIST{ uniform_smallint,uniform_int,uniform_real
                ,bernoulli_distribution,binomial_distribution,cauchy_distribution
                ,gamma_distribution,poisson_distribution,geometric_distribution
                ,triangle_distribution,exponential_distribution,normal_distribution
                ,lognormal_distribution };


//----------------------------------------------------------------------------------------------------------------------
/// @class Random
/// @brief wrapper for std random and distribution functions, it will
/// generate two basic random functions for RandPositiveFloat (0-1) and
/// RandFloat() +/- 1 these are also overloaded to have a param for range
/// added to this are functions for Random Colours and Vectors and Points
/// and also the ability to add other distributions
/// random library.
/// @author Jonathan Macey
/// @version 1.0
/// @date 17/05/10 Initial version

/// @note by default we use the mt19937 mersenne twister but this can
/// be changed in the library by modifying the define ENGINE to any of the following

/// @note as each call to the random generator function accesses the ENGINE m_generator no
/// callable method that invokes any of the generators can be constant as the internal
/// state of m_generator is modified with the call hence the lack of const methods
//----------------------------------------------------------------------------------------------------------------------



class NGL_DLLEXPORT Random : public  Singleton<Random>
{
//----------------------------------------------------------------------------------------------------------------------
/// @brief we are a friend with singelton so we can assess the template methods
//----------------------------------------------------------------------------------------------------------------------
friend class Singleton<Random>;
friend class Colour;
friend class Vec4;

public :

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the seed using std::time(NULL)
  //----------------------------------------------------------------------------------------------------------------------
  void setSeed();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the seed using a param value
  /// @param _value the seed value
  //----------------------------------------------------------------------------------------------------------------------
  void setSeed( unsigned int _value );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief gets a pre-generated Real value for a genetator
  /// @param _name the name of the generator to use for the number
  /// @brief returns a random number created by the generator or 0
  /// if the generator is not found
  //----------------------------------------------------------------------------------------------------------------------
  Real getFloatFromGeneratorName( const std::string &_name);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get a random vector with componets ranged from +/- 1
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 getRandomVec4();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get a random vector with componets ranged from +/- 1 and Normalized
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 getRandomNormalizedVec4();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get a random vector with componets ranged from +/- 1
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 getRandomVec3();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get a random vector with componets ranged from +/- 1 and Normalized
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 getRandomNormalizedVec3();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get a random vector with componets ranged from +/- 1
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 getRandomVec2();

  Vec3 getRandomColour3();
  Vec4 getRandomColour4();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get a random vector with componets ranged from +/- 1 and Normalized
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 getRandomNormalizedVec2();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get a random point in 3D space defaults to +/- 1 else user defined range
  /// @param  _xRange the +/-x range
  /// @param  _yRange the +/-y range
  /// @param  _zRange the +/-z range
  /// @returns a random point
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 getRandomPoint( Real _xRange=1.0, Real _yRange=1.0, Real _zRange=1.0 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a replacement for the old RandomNumber func
  /// this is basically a convinience function
  /// @param _mult an optional multiplyer for the output
  /// @returns (uniform_random(-1-0-+1) * _mult)
  //----------------------------------------------------------------------------------------------------------------------
  Real randomNumber(Real _mult=1);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a replacement for the old ReandomPosNum
  /// this is basically a convinience function
  /// @param _mult an optional multiplyer for the output
  /// @returns (uniform_random(0-1) * _mult)
  //----------------------------------------------------------------------------------------------------------------------
  Real randomPositiveNumber(  Real _mult=1  );

  protected :

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the generator for rng class where all funcs and distribs are added.
  /// all we need to do is replace this one define to use any of the other boost rng
  /// engines.

  std::mt19937 m_generator;
  //----------------------------------------------------------------------------------------------------------------------

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor hidden in protected as we are a singleton class
  //----------------------------------------------------------------------------------------------------------------------
  Random();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief our map to hold the generator data basically we are going to hold
  /// a name / function pair, and this function will be called returning a Real
  /// value
  //----------------------------------------------------------------------------------------------------------------------
  std::unordered_map<std::string, std::uniform_real_distribution<Real> > m_floatGenerators;

};

}// end namespace

#endif
//----------------------------------------------------------------------------------------------------------------------


