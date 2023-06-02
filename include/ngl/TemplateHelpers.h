#ifndef TEMPLATEHELPERS_H_
#define TEMPLATEHELPERS_H_
#include <array>
#include <vector>
#include <type_traits>
#include <iostream>
namespace ngl
{


// traits to check for array types
template<typename>
struct is_std_array : std::false_type {};
template<typename T, std::size_t N>
struct is_std_array<std::array<T,N>> : std::true_type {};

// traits for matrix types
// see if forwarding this helps
template<typename T>
struct is_ngl_matrix : std::false_type {};
template<>
struct is_ngl_matrix<ngl::Mat2> : std::true_type {};
template<>
struct is_ngl_matrix<ngl::Mat3> : std::true_type {};
template<>
struct is_ngl_matrix<ngl::Mat4> : std::true_type {};
template<>
struct is_ngl_matrix<ngl::Mat2 &> : std::true_type {};
template<>
struct is_ngl_matrix<ngl::Mat3 &> : std::true_type {};
template<>
struct is_ngl_matrix<ngl::Mat4 &> : std::true_type {};


// vec traits
template<typename T>
struct is_ngl_vec : std::false_type {};
template<>
struct is_ngl_vec<ngl::Vec2> : std::true_type {};
template<>
struct is_ngl_vec<ngl::Vec3> : std::true_type {};
template<>
struct is_ngl_vec<ngl::Vec4> : std::true_type {};
template<>
struct is_ngl_vec<ngl::Vec2 &> : std::true_type {};
template<>
struct is_ngl_vec<ngl::Vec3 &> : std::true_type {};
template<>
struct is_ngl_vec<ngl::Vec4 &> : std::true_type {};

// get the value type of the array
template <typename T>
using array_value_type = std::decay_t<decltype(std::declval<T&>()[0])>;
// trait for vector types
template<class T> struct is_std_vector : public std::false_type {};
template<class T, class Alloc> 
struct is_std_vector<std::vector<T, Alloc>> : public std::true_type {};

template <typename... Ts>
void print_args(Ts&&... args)
{
    ((std::cout <<"args "<< args << " "), ...);
    std::cout << "\n";
}



}

#endif