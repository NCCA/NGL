/*
  Copyright (C) 2009  Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITH ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Random.h"
#include <cstdlib> // for time
#include <ctime>

//----------------------------------------------------------------------------------------------------------------------
/// @file Random.cpp
/// @brief implementation files for Random class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{
constexpr auto RandomFloat = "RandomFloat";
constexpr auto RandomPositiveFloat = "RandomPositiveFloat";
std::mt19937 Random::m_generator;
// because of C++ 11 we can now use lambda expressions to init static members so we don't need a ctor
std::unordered_map< std::string, std::uniform_real_distribution< Real > > Random::m_floatGenerators = []
{
  std::unordered_map< std::string, std::uniform_real_distribution< Real > > gen;
  // first create a simple uniform real distrib
  std::uniform_real_distribution< Real > MinusPlusOneFloatDistrib(-1.0f, 1.0f);
  gen[RandomFloat] = MinusPlusOneFloatDistrib;
  // same for below but using 0-1 for distrib
  std::uniform_real_distribution< Real > ZeroOneFloatDistrib(0.0f, 1.0f);
  gen[RandomPositiveFloat] = ZeroOneFloatDistrib;
  return gen;
}();

std::unordered_map< std::string, std::uniform_int_distribution< int > > Random::m_intGenerators;

//----------------------------------------------------------------------------------------------------------------------
void Random::setSeed()
{
  m_generator.seed(static_cast< unsigned int >(std::time(nullptr)));
}

//----------------------------------------------------------------------------------------------------------------------
void Random::setSeed(unsigned int _value)
{
  m_generator.seed(_value);
}

//----------------------------------------------------------------------------------------------------------------------
Real Random::getFloatFromGeneratorName(std::string_view _name)
{
  // grab a function pointer based on the _name from the map
  // auto func=m_floatGenerators[_name];
  auto func = m_floatGenerators.find(_name.data());
  // see if we got anything we can use
  if(func != m_floatGenerators.end())
  {
    // if it exists execute the function and return the value
    return func->second(m_generator);
  }
  else
  {
    // otherwise we return the safest possible value 0
    return 0.0f;
  }
}

int Random::getIntFromGeneratorName(std::string_view _name)
{
  // grab a function pointer based on the _name from the map
  // auto func=m_floatGenerators[_name];
  auto func = m_intGenerators.find(_name.data());
  // see if we got anything we can use
  if(func != m_intGenerators.end())
  {
    // if it exists execute the function and return the value
    return func->second(m_generator);
  }
  else
  {
    // otherwise we return the safest possible value 0
    return 0;
  }
}

void Random::addIntGenerator(std::string_view _name, std::uniform_int_distribution< int > &_dist)
{
  m_intGenerators[_name.data()] = _dist;
}

void Random::addFloatGenerator(std::string_view _name, std::uniform_real_distribution< float > &_dist)
{
  m_floatGenerators[_name.data()] = _dist;
}
//----------------------------------------------------------------------------------------------------------------------
Vec4 Random::getRandomVec4()
{
  auto gen = m_floatGenerators[RandomFloat];
  return Vec4(gen(m_generator), gen(m_generator), gen(m_generator), 0.0f);
}

Vec4 Random::getRandomColour4()
{
  auto gen = m_floatGenerators[RandomPositiveFloat];
  return Vec4(gen(m_generator), gen(m_generator), gen(m_generator), 1.0f);
}
Vec3 Random::getRandomColour3()
{
  auto gen = m_floatGenerators[RandomPositiveFloat];
  return Vec3(gen(m_generator), gen(m_generator), gen(m_generator));
}

//----------------------------------------------------------------------------------------------------------------------
Vec4 Random::getRandomNormalizedVec4()
{
  auto gen = m_floatGenerators[RandomFloat];
  Vec4 v(gen(m_generator), gen(m_generator), gen(m_generator), 0.0f);
  v.normalize();
  return v;
}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Random::getRandomVec3()
{
  auto gen = m_floatGenerators[RandomFloat];
  return Vec3(gen(m_generator), gen(m_generator), gen(m_generator));
}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Random::getRandomNormalizedVec3()
{
  auto gen = m_floatGenerators[RandomFloat];
  Vec3 v(gen(m_generator), gen(m_generator), gen(m_generator));
  v.normalize();
  return v;
}

//----------------------------------------------------------------------------------------------------------------------
Vec2 Random::getRandomVec2()
{
  auto gen = m_floatGenerators[RandomFloat];
  return Vec2(gen(m_generator), gen(m_generator));
}

//----------------------------------------------------------------------------------------------------------------------
Vec2 Random::getRandomNormalizedVec2()
{
  auto gen = m_floatGenerators[RandomFloat];
  Vec2 v(gen(m_generator), gen(m_generator));
  v.normalize();
  return v;
}

Vec3 Random::getRandomPoint(Real _xRange, Real _yRange, Real _zRange)
{
  auto gen = m_floatGenerators[RandomFloat];
  return Vec3(gen(m_generator) * _xRange, gen(m_generator) * _yRange, gen(m_generator) * _zRange);
}

//----------------------------------------------------------------------------------------------------------------------
Real Random::randomNumber(Real _mult)
{
  auto gen = m_floatGenerators[RandomFloat];
  return gen(m_generator) * _mult;
}

//----------------------------------------------------------------------------------------------------------------------
Real Random::randomPositiveNumber(Real _mult)
{
  auto gen = m_floatGenerators[RandomPositiveFloat];
  return gen(m_generator) * _mult;
}
} // namespace ngl

//----------------------------------------------------------------------------------------------------------------------
