#ifndef NGLHASH_H_
#define NGLHASH_H_

#include <ngl/Vec2.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Mat2.h>
#include <ngl/Mat3.h>
#include <ngl/Mat4.h>
#include <ngl/Quaternion.h>
#include <algorithm>


// Modified from GLM hash routines
void hashCombine(size_t &seed, size_t hash)
{
	hash += 0x9e3779b9 + (seed << 6) + (seed >> 2);
	seed ^= hash;
}

template <> 
struct std::hash<ngl::Vec2 >
{
  std::size_t operator()(const ngl::Vec2 &v) const noexcept
  {
		size_t seed = 0;
		hash<float> hasher;
		hashCombine(seed, hasher(v.m_x));
		hashCombine(seed, hasher(v.m_y));
		return seed;
	}
};

template <> 
struct std::hash<ngl::Vec3 >
{
  std::size_t operator()(const ngl::Vec3 &v) const noexcept
  {
		size_t seed = 0;
		hash<float> hasher;
		hashCombine(seed, hasher(v.m_x));
		hashCombine(seed, hasher(v.m_y));
		hashCombine(seed, hasher(v.m_z));
		return seed;
	}
};

template <> 
struct std::hash<ngl::Vec4 >
{
  std::size_t operator()(const ngl::Vec4 &v) const noexcept
  {
		size_t seed = 0;
		hash<float> hasher;
		hashCombine(seed, hasher(v.m_x));
		hashCombine(seed, hasher(v.m_y));
		hashCombine(seed, hasher(v.m_z));
		hashCombine(seed, hasher(v.m_w));
		return seed;
	}
};

template <> 
struct std::hash<ngl::Quaternion >
{
  std::size_t operator()(const ngl::Quaternion &v) const noexcept
  {
		size_t seed = 0;
		hash<float> hasher;
		hashCombine(seed, hasher(v.m_s));
		hashCombine(seed, hasher(v.m_x));
		hashCombine(seed, hasher(v.m_y));
		hashCombine(seed, hasher(v.m_z));
		return seed;
	}
};

template <> 
struct std::hash<ngl::Mat2>
{
  std::size_t operator()(const ngl::Mat2 &v) const noexcept
  {
		size_t seed = 0;
		hash<float> hasher;
    for(auto i : v.m_openGL)
		{
  		hashCombine(seed, hasher(i));
		}
		return seed;
	}
};

template <> 
struct std::hash<ngl::Mat3>
{
  std::size_t operator()(const ngl::Mat3 &v) const noexcept
  {
		size_t seed = 0;
		hash<float> hasher;
    for(auto i : v.m_openGL)
  	{
			hashCombine(seed, hasher(i));
		}
		return seed;
	}
};

template <> 
struct std::hash<ngl::Mat4>
{
  std::size_t operator()(const ngl::Mat4 &v) const noexcept
  {
		size_t seed = 0;
		hash<float> hasher;
    for(auto i : v.m_openGL)
  	{
			hashCombine(seed, hasher(i));
		}
		return seed;
	}
};
#endif