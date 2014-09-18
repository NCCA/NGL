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
#ifndef RANDOM_H__
#define RANDOM_H__
//----------------------------------------------------------------------------------------------------------------------
/// @file Random.h
/// @brief an encapsulation of the boost::random classes
//----------------------------------------------------------------------------------------------------------------------
// must include types.h first for Real and GLEW if required
#include "Colour.h"
#include "Singleton.h"
#include "Vec4.h"

#include <map>
#include <boost/random.hpp>
#include <boost/function.hpp>

namespace ngl
{

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief enumerated list of the different distributions we can
  /// add to the generator,
  //----------------------------------------------------------------------------------------------------------------------
  enum  RANDDIST{ uniform_smallint,uniform_int,uniform_real
                ,bernoulli_distribution,binomial_distribution,cauchy_distribution
                ,gamma_distribution,poisson_distribution,geometric_distribution
                ,triangle_distribution,exponential_distribution,normal_distribution
                ,lognormal_distribution };


//----------------------------------------------------------------------------------------------------------------------
/// @class Random
/// @brief wrapper for boost random and distribution functions, it will
/// generate two basic random functions for RandPositiveFloat (0-1) and
/// RandFloat() +/- 1 these are also overloaded to have a param for range
/// added to this are functions for Random Colours and Vectors and Points
/// and also the ability to add other distributions based on the boost
/// random library.
/// @author Jonathan Macey
/// @version 1.0
/// @date 17/05/10 Initial version

/// @note by default we use the boost::mt19937 mersenne twister but this can
/// be changed in the library by modifying the define ENGINE to any of the following
/// http://www.boost.org/doc/libs/1_43_0/doc/html/boost_random/reference.html#boost_random.reference.generators
/// generators the define for ENGINE is hidden in the protected section where it is first
/// used for the m_generator attribute

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
  void setSeed( int _value );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief gets a pre-generated Real value for a genetator
  /// @param _name the name of the generator to use for the number
  /// @brief returns a random number created by the generator or 0
  /// if the generator is not found
  //----------------------------------------------------------------------------------------------------------------------
  Real getFloatFromGeneratorName( const std::string &_name);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return a random colour with rgb components clamped between 0-1
  //----------------------------------------------------------------------------------------------------------------------
  Colour getRandomColour();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return a random colour with rgba components clamped between 0-1
  //----------------------------------------------------------------------------------------------------------------------
  Colour getRandomColourAndAlpha();
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
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to add a new generator, we must choose which distribution
  /// as well as a range for the distribution (if appropriate)
  /// @param _distribution the distribution function to use
  /// @param _min the min value for the distrbibution note will be cast to (int) if needed
  /// @param _max the max value for distribution note will be cast to (int) if needed
  /// @param _prob, the triangle dist uses this (see http://www.boost.org/doc/libs/1_43_0/doc/html/boost/triangle_distribution.html)
  //----------------------------------------------------------------------------------------------------------------------
  void addGenerator( const std::string &_name, RANDDIST _distribution, Real _min=0.0, Real _max=1.0,Real _prob=0.5);

protected :

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the generator for rng class where all funcs and distribs are added.
  /// all we need to do is replace this one define to use any of the other boost rng
  /// engines.
  #define ENGINE boost::mt19937
  ENGINE m_generator;
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
  std::map<std::string, boost::function <Real (void)> > m_floatGenerators;

};

}// end namespace

#endif
//----------------------------------------------------------------------------------------------------------------------


