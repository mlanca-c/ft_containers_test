/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlancac </var/spool/mail/mlancac>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:18:24 by mlancac           #+#    #+#             */
/*   Updated: 2022/11/30 18:24:41 by mlancac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* Headers                                                                    */
/* ************************************************************************** */

#include "ft_containers.hpp"

#include <gtest/gtest.h>
#include <iostream>
#include <string>

#if LIB == FT
# define nullptr_t ft::s_nullptr
#else
# define nullptr_t std::nullptr_t
#endif /* LIB */

/* ************************************************************************** */
/* Testing ft::equal                                                          */
/* ************************************************************************** */

TEST( test_equal, equal_equality ) {

    int             arr[] = { 1, 2, 3, 4, 5 };
    ft::vector<int> vec( arr, arr + 5 );
    ASSERT_TRUE( ft::equal( vec.begin(), vec.end(), arr ) );
    arr[0] = 0;
    ASSERT_FALSE( ft::equal( vec.begin(), vec.end(), arr ) );
}

bool pred1( int i, int j ) { return ( i == j ); }

bool pred2( int i, int j ) { return ( i >= j ); }

TEST( test_equal, equal_predicate ) {

    int             arr[] = { 1, 2, 3, 4, 5 };
    ft::vector<int> vec( arr, arr + 5 );
    ASSERT_TRUE( ft::equal( vec.begin(), vec.end(), arr, pred1 ) );
    arr[0] = 0;
    ASSERT_FALSE( ft::equal( vec.begin(), vec.end(), arr, pred1 ) );
    ASSERT_TRUE( ft::equal( vec.begin(), vec.end(), arr, pred2 ) );
}

/* ************************************************************************** */
/* Testing ft::lexicographical_compare                                        */
/* ************************************************************************** */

TEST( test_lexicographical_compare, default_lexicographical_compare ) {

    char foo[] = "Apple";
    char bar[] = "apartment";
    ASSERT_TRUE( ft::lexicographical_compare( foo, foo + 5, bar, bar + 9 ) );
    ASSERT_FALSE( ft::lexicographical_compare( bar, bar + 9, foo, foo + 5 ) );
}

bool pred3( char c1, char c2 ) {
    return ( std::tolower( c1 ) < std::tolower( c2 ) );
}

TEST( test_lexicographical_compare, custom_lexicographical_compare ) {

    char foo[] = "Apple";
    char bar[] = "apartment";
    ASSERT_FALSE(
        ft::lexicographical_compare( foo, foo + 5, bar, bar + 9, pred3 ) );
    ASSERT_TRUE(
        ft::lexicographical_compare( bar, bar + 9, foo, foo + 5, pred3 ) );
}

/* ************************************************************************** */
/* Testing ft::enable_if                                                      */
/* ************************************************************************** */

template<class T>
bool foo( T t, typename ft::enable_if<ft::is_integral<T>::value >::type* = 0 ) {
    return ( true );
}

template<class T>
bool foo( T t,
          typename ft::enable_if<!ft::is_integral<T>::value >::type* = 0 ) {
    return ( false );
}

TEST( test_enable_if, enable_if ) {
    ASSERT_TRUE( foo( 7 ) );
    ASSERT_FALSE( foo( "hello" ) );
}

/* ************************************************************************** */
/* Testing ft::is_integral                                                    */
/* ************************************************************************** */

class class_t {};

struct struct_t {};

enum enum_t {};

TEST( test_is_integral, is_integral ) {

    // testing integral types
    ASSERT_TRUE( ft::is_integral<bool>::value == true );
    ASSERT_TRUE( ft::is_integral<char>::value == true );
    ASSERT_TRUE( ft::is_integral<wchar_t>::value == true );
    ASSERT_TRUE( ft::is_integral<signed char>::value == true );
    ASSERT_TRUE( ft::is_integral<short int>::value == true );
    ASSERT_TRUE( ft::is_integral<int>::value == true );
    ASSERT_TRUE( ft::is_integral<long int>::value == true );
    ASSERT_TRUE( ft::is_integral<long long int>::value == true );
    ASSERT_TRUE( ft::is_integral<unsigned char>::value == true );
    ASSERT_TRUE( ft::is_integral<unsigned short int>::value == true );
    ASSERT_TRUE( ft::is_integral<unsigned int>::value == true );
    ASSERT_TRUE( ft::is_integral<unsigned long int>::value == true );
    ASSERT_TRUE( ft::is_integral<unsigned long long int>::value == true );
    // testing floating point types
    ASSERT_FALSE( ft::is_integral<float>::value == true );
    ASSERT_FALSE( ft::is_integral<double>::value == true );
    ASSERT_FALSE( ft::is_integral<long double>::value == true );
    // testing void type
    ASSERT_FALSE( ft::is_integral<void>::value == true );
    // testing null pointer type
    ASSERT_FALSE( ft::is_integral<nullptr_t>::value == true );
    // testing custom / standard types
    ASSERT_FALSE( ft::is_integral<class_t>::value == true );
    ASSERT_FALSE( ft::is_integral<struct_t>::value == true );
    ASSERT_FALSE( ft::is_integral<enum_t>::value == true );
    ASSERT_FALSE( ft::is_integral<std::string>::value == true );
}

/* ************************************************************************** */
/* Testing ft::pair                                                           */
/* ************************************************************************** */

TEST( test_pair, default_constructor ) {

    ft::pair<int, int> a;
    ASSERT_EQ( a.first, 0 );
    ASSERT_EQ( a.second, 0 );
}

TEST( test_pair, copy_constructor ) {

    ft::pair<int, int>  a( 1, 2 );
    ft::pair<char, int> b( a );
    ASSERT_EQ( a.first, 1 );
    ASSERT_EQ( a.second, 2 );
    ASSERT_EQ( b.first, 1 );
    ASSERT_EQ( b.second, 2 );
}

TEST( test_pair, initialization_constructor ) {

    ft::pair<int, std::string> a( 1, "second" );
    ASSERT_EQ( a.first, 1 );
    ASSERT_EQ( a.second, "second" );
}

TEST( test_pair, destructor ) {

    ft::pair<int, std::string>* a =
        new ft::pair<int, std::string>( 1, "second" );
    delete a;
}

TEST( test_pair, operator_assignemnt ) {

    ft::pair<int, int>  a( 1, 2 );
    ft::pair<char, int> b;
    b = a;
    ASSERT_EQ( a.first, 1 );
    ASSERT_EQ( a.second, 2 );
    ASSERT_EQ( b.first, 1 );
    ASSERT_EQ( b.second, 2 );
}

TEST( test_pair, non_member_functions ) {
    ft::pair<int, int> a( 0, 0 );
    ft::pair<int, int> b( 0, 0 );
    // equals
    ASSERT_TRUE( a == a );
    ASSERT_TRUE( b == b );
    ASSERT_TRUE( a == b );
    a.first = 1;
    ASSERT_FALSE( a == b );
    b = a;
    ASSERT_TRUE( a == b );
    // not equals
    ASSERT_FALSE( a != a );
    ASSERT_FALSE( b != b );
    ASSERT_FALSE( a != b );
    a.first = 0;
    ASSERT_TRUE( a != b );
    b = a;
    ASSERT_FALSE( a != b );
    // less and less eq
    ASSERT_FALSE( a < b );
    ASSERT_TRUE( a <= b );
    a.first = 1;
    ASSERT_FALSE( a < b );
    ASSERT_FALSE( a <= b );
    b.second = 1;
    ASSERT_FALSE( a < b );
    ASSERT_FALSE( a <= b );
    b.first = 1;
    ASSERT_TRUE( a < b );
    ASSERT_TRUE( a <= b );
    // great and great eq
    ASSERT_FALSE( a > b );
    ASSERT_FALSE( a >= b );
}

TEST( test_pair, make_pair ) {
    int                arr[5] = { 1, 2, 3, 4, 5 };
    ft::pair<int, int> a = ft::make_pair( 1, arr[1] );
    ASSERT_EQ( a.first, 1 );
    ASSERT_EQ( a.second, 2 );
}
