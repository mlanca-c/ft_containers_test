/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlancac </var/spool/mail/mlancac>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:38:45 by mlancac           #+#    #+#             */
/*   Updated: 2023/01/04 15:48:57 by mlancac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* Headers                                                                    */
/* ************************************************************************** */

#include "ft_containers.hpp"

#include <gtest/gtest.h>
#include <iostream>

/* ************************************************************************** */
/* Class                                                                      */
/* ************************************************************************** */

template<typename T>
class test_map : public ::testing::Test {

    public:

        /* Member Types */
        typedef typename T::first_type           first_type;
        typedef typename T::second_type          second_type;
        typedef ft::map<first_type, second_type> Map;

        void SetUp( void ) {}

        void TearDown( void ) {}

        void AddValues( int n, float increment = 1 ) {

            first_type val = ( this->m.empty() ? 0 : this->m.end()->first );
            auto       s = this->m.size();
            while ( this->m.size() != s + n ) {
                val += increment;
                this->m[val] = static_cast<second_type>( val * 2 );
            }
        }

        void Print( Map& a ) const {

            std::cout << "map {" << std::endl;
            for ( auto it = a.begin(); it != a.end(); it++ )
                std::cout << " " << it->first << ": " << it->second
                          << std::endl;
            std::cout << "}" << std::endl;
        }

    protected:

        Map         m;
        first_type  key = 0;
        second_type value = 0;
};

// TODO: figure a way to add std::string here as well
//		-> maybe change behaviour of increment
// typedef testing::Types< ft::pair<int, int> > MapTypes;
typedef testing::Types<
    ft::pair<int, int>, ft::pair<int, char>, ft::pair<int, unsigned int>,
    ft::pair<int, float>, ft::pair<int, double>, ft::pair<char, char>,
    ft::pair<char, int>, ft::pair<char, unsigned int>, ft::pair<char, float>,
    ft::pair<char, double>, ft::pair<unsigned int, unsigned int>,
    ft::pair<unsigned int, int>, ft::pair<unsigned int, char>,
    ft::pair<unsigned int, float>, ft::pair<unsigned int, double>,
    ft::pair<float, int>, ft::pair<float, char>, ft::pair<float, unsigned int>,
    ft::pair<float, float>, ft::pair<float, double>, ft::pair<double, int>,
    ft::pair<double, char>, ft::pair<double, unsigned int>,
    ft::pair<double, float>, ft::pair<double, double> >
    MapTypes;

TYPED_TEST_SUITE( test_map, MapTypes );

/* ************************************************************************** */
/* Tests                                                                      */
/* ************************************************************************** */

TYPED_TEST( test_map, default_constructor ) {

    typename test_map<TypeParam>::Map a;

    ASSERT_EQ( this->m.size(), 0 );
    ASSERT_EQ( a.size(), 0 );
}

TYPED_TEST( test_map, range_constructor ) {

    this->AddValues( 5 );
    typename test_map<TypeParam>::Map a( this->m.begin(), this->m.end() );
    typename test_map<TypeParam>::Map b( ++this->m.begin(), this->m.end() );
    ASSERT_EQ( a.size(), 5 );
    ASSERT_EQ( b.size(), 4 );
    ASSERT_EQ( a, this->m );
    ASSERT_NE( a, b );
}

TYPED_TEST( test_map, copy_constructor ) {

    this->AddValues( 5 );
    typename test_map<TypeParam>::Map a( this->m );
    ASSERT_EQ( a.size(), 5 );
    ASSERT_EQ( a, this->m );
}

TYPED_TEST( test_map, operator_assignment ) {

    this->AddValues( 5 );
    typename test_map<TypeParam>::Map a;
    ASSERT_NE( a, this->m );
    a = this->m;
    ASSERT_EQ( a, this->m );
}

TYPED_TEST( test_map, destructor ) {

    this->AddValues( 3 );
    typename test_map<TypeParam>::Map* a =
        new typename test_map<TypeParam>::Map;
    typename test_map<TypeParam>::Map* b =
        new typename test_map<TypeParam>::Map( this->m );
    typename test_map<TypeParam>::Map* c =
        new typename test_map<TypeParam>::Map( b->begin(), b->end() );

    delete a;
    delete b;
    delete c;
}

TYPED_TEST( test_map, begin ) {

    this->AddValues( 2 );
    ASSERT_EQ( *this->m.begin(), *this->m.rend() );
    ASSERT_EQ( typeid( this->m.begin() ),
               typeid( typename test_map<TypeParam>::Map::iterator ) );
}

TYPED_TEST( test_map, end ) {

    this->AddValues( 2 );
    ASSERT_EQ( *( --this->m.end() ), *this->m.rbegin() );
    ASSERT_EQ( typeid( this->m.end() ),
               typeid( typename test_map<TypeParam>::Map::iterator ) );
}

TYPED_TEST( test_map, rbegin ) {

    this->AddValues( 2 );
    ASSERT_EQ( *this->m.rbegin(), *( --this->m.end() ) );
    ASSERT_EQ( typeid( this->m.rbegin() ),
               typeid( typename test_map<TypeParam>::Map::reverse_iterator ) );
}

TYPED_TEST( test_map, rend ) {

    this->AddValues( 2 );
    ASSERT_EQ( *this->m.rend(), *this->m.begin() );
    ASSERT_EQ( typeid( this->m.rbegin() ),
               typeid( typename test_map<TypeParam>::Map::reverse_iterator ) );
}

TYPED_TEST( test_map, empty ) {

    ASSERT_TRUE( this->m.empty() );
    this->AddValues( 2 );
    ASSERT_FALSE( this->m.empty() );
    this->m.clear();
    ASSERT_TRUE( this->m.empty() );
}

TYPED_TEST( test_map, size ) {

    ASSERT_EQ( this->m.size(), 0 );
    // Adding values
    this->AddValues( 1 );
    ASSERT_EQ( this->m.size(), 1 );
    this->AddValues( 12 );
    ASSERT_EQ( this->m.size(), 13 );
    // Removing values
    this->m.erase( ++this->m.begin() );
    ASSERT_EQ( this->m.size(), 12 );
    // clearing vector
    this->m.clear();
    ASSERT_EQ( this->m.size(), 0 );
}

TYPED_TEST( test_map, max_size ) {

    typedef ft::pair<typename test_map<TypeParam>::first_type const,
                     typename test_map<TypeParam>::second_type >
        map_pair;
    ASSERT_LT( this->m.max_size(), std::allocator<map_pair>().max_size() );
}

TYPED_TEST( test_map, access_operator ) {

    this->m[this->key] = this->value;
    ASSERT_EQ( this->m[this->key], this->value );
}

TYPED_TEST( test_map, at ) {

    this->AddValues( 4 );
    for ( auto it = this->m.begin(); it != this->m.end(); it++ )
        ASSERT_EQ( this->m.at( it->first ), it->second );
    ASSERT_THROW( this->m.at( 0 ), std::out_of_range );
}

TYPED_TEST( test_map, insert ) {

    ft::map<int, int> a;

    auto beg = ( a.insert( ft::make_pair( 1, 2 ) ) ).first;
    auto end = ( a.insert( ft::make_pair( 4, 8 ) ) ).first;
    ASSERT_TRUE( a.insert( ft::make_pair( 2, 4 ) ).second );
    ASSERT_TRUE( a.insert( ft::make_pair( 3, 6 ) ).second );

    ASSERT_EQ( a.size(), 4 );
    ASSERT_EQ( a.begin(), beg );
    ASSERT_EQ( --a.end(), end );

    ASSERT_FALSE( a.insert( ft::make_pair( 3, 6 ) ).second );
    ASSERT_EQ( a.size(), 4 );

    ASSERT_TRUE( a.insert( ft::make_pair( 5, 10 ) ).second );
    ASSERT_NE( --a.end(), end );

    ASSERT_TRUE(
        this->m.insert( ft::make_pair( this->key, this->value ) ).second );
    ASSERT_TRUE(
        this->m.insert( ft::make_pair( ++this->key, ++this->value ) ).second );
    ASSERT_TRUE(
        this->m.insert( ft::make_pair( ++this->key, ++this->value ) ).second );
    ASSERT_FALSE(
        this->m.insert( ft::make_pair( this->key, this->value ) ).second );
    ASSERT_EQ( this->m.size(), 3 );
}

TYPED_TEST( test_map, erase ) {

    ft::map<int, int> a;
    a.insert( ft::make_pair( 1, 2 ) );
    a.insert( ft::make_pair( 4, 8 ) );
    // adding values to b
    ft::map<int, int> b;
    b.insert( ft::make_pair( 1, 2 ) );
    b.insert( ft::make_pair( 2, 4 ) );
    b.insert( ft::make_pair( 3, 6 ) );
    b.insert( ft::make_pair( 4, 8 ) );
    b.insert( ft::make_pair( 5, 10 ) );
    b.insert( ft::make_pair( 6, 12 ) );

    // erase first value
    ASSERT_EQ( b.size(), 6 );
    b.erase( ++b.begin() );
    ASSERT_EQ( b.size(), 5 );
    ASSERT_EQ( b.find( 2 ), b.end() );
    // erase last 2 values
    auto it = --b.end();
    b.erase( --it, b.end() );
    ASSERT_EQ( b.find( 5 ), b.end() );
    ASSERT_EQ( b.find( 6 ), b.end() );
    ASSERT_EQ( b.size(), 3 );
    // erase value from key
    ASSERT_NE( b.find( 3 ), b.end() );
    b.erase( 3 );
    ASSERT_EQ( b.find( 3 ), b.end() );
    ASSERT_EQ( b.size(), 2 );
    // checking values
    ASSERT_EQ( b, a );
    // erasing everything
    b.erase( b.begin(), b.end() );
    ASSERT_TRUE( b.empty() );

    this->AddValues( 10 );
    this->m.erase( ++this->m.begin(), --this->m.end() );
    ASSERT_EQ( this->m.size(), 2 );
    this->m.erase( this->m.begin() );
    ASSERT_EQ( this->m.size(), 1 );
    this->m.erase( this->m.begin()->first );
    ASSERT_EQ( this->m.size(), 0 );
}

TYPED_TEST( test_map, clear ) {

    this->AddValues( 5 );
    ASSERT_EQ( this->m.size(), 5 );
    this->m.clear();
    ASSERT_TRUE( this->m.empty() );
}

TYPED_TEST( test_map, key_comp ) {
    ASSERT_EQ( typeid( this->m.key_comp() ),
               typeid( std::less<typename test_map<TypeParam>::first_type> ) );
}

TYPED_TEST( test_map, value_comp ) {
    typedef typename test_map<TypeParam>::Map::value_compare value_compare;
    ASSERT_EQ( typeid( this->m.value_comp() ), typeid( value_compare ) );
}

TYPED_TEST( test_map, find ) {

    ft::map<int, int> a;
    a.insert( ft::make_pair( 1, 2 ) );
    a.insert( ft::make_pair( 2, 4 ) );
    a.insert( ft::make_pair( 3, 6 ) );
    ASSERT_EQ( a.find( 0 ), a.end() );
    ASSERT_EQ( a.find( 1 )->first, 1 );
    ASSERT_EQ( a.find( 1 )->second, 2 );
    ASSERT_EQ( a.find( 2 )->first, 2 );
    ASSERT_EQ( a.find( 2 )->second, 4 );
    ASSERT_EQ( a.find( 3 )->first, 3 );
    ASSERT_EQ( a.find( 3 )->second, 6 );
    ASSERT_EQ( a.find( 4 ), a.end() );
}

TYPED_TEST( test_map, count ) {

    this->AddValues( 4 );
    for ( auto it = this->m.begin(); it != this->m.end(); it++ )
        ASSERT_EQ( this->m.count( it->first ), 1 );
    ASSERT_EQ( this->m.count( 0 ), 0 );
}

TYPED_TEST( test_map, lower_bound ) {

    this->AddValues( 2, 1 );
    auto val = this->m.begin()->first;

    ASSERT_EQ( this->m.lower_bound( val - 1 ), this->m.begin() );
    ASSERT_EQ( this->m.lower_bound( val ), this->m.begin() );
    ASSERT_EQ( this->m.lower_bound( ++val ), ++this->m.begin() );
    ASSERT_EQ( this->m.lower_bound( ++val ), this->m.end() );
}

TYPED_TEST( test_map, upper_bound ) {

    this->AddValues( 2, 1 );
    auto val = this->m.begin()->first;

    ASSERT_EQ( this->m.upper_bound( val - 1 ), this->m.begin() );
    ASSERT_EQ( this->m.upper_bound( val ), ++this->m.begin() );
    ASSERT_EQ( this->m.upper_bound( ++val ), this->m.end() );
    ASSERT_EQ( this->m.upper_bound( ++val ), this->m.end() );
}

TYPED_TEST( test_map, equal_range ) {

    this->AddValues( 3, 1 );
    auto val = this->m.begin()->first;

    auto it = this->m.equal_range( val );
    ASSERT_EQ( it.second, this->m.find( val + 1 ) );

    it = this->m.equal_range( val - 1 );
    ASSERT_EQ( it.first, this->m.begin() );
    ASSERT_EQ( it.second, this->m.begin() );

    it = this->m.equal_range( val + 15 );
    ASSERT_EQ( it.first, this->m.end() );
    ASSERT_EQ( it.second, this->m.end() );
}

TYPED_TEST( test_map, get_allocator ) {

    typedef ft::pair<typename test_map<TypeParam>::first_type const,
                     typename test_map<TypeParam>::second_type >
        map_pair;
    ASSERT_EQ( typeid( this->m.get_allocator() ),
               typeid( std::allocator<map_pair> ) );
}

TYPED_TEST( test_map, non_member_functions ) {

    typename test_map<TypeParam>::Map a;
    // equals
    ASSERT_TRUE( this->m == this->m );
    this->AddValues( 5 );
    ASSERT_FALSE( this->m == a );
    a = this->m;
    ASSERT_TRUE( this->m == a );
    // not equals
    ASSERT_FALSE( this->m != this->m );
    this->AddValues( 5 );
    ASSERT_TRUE( this->m != a );
    a = this->m;
    ASSERT_FALSE( this->m != a );
    // less and less eq
    ASSERT_FALSE( this->m < a );
    ASSERT_TRUE( this->m <= a );
    this->AddValues( 5 );
    ASSERT_FALSE( this->m < a );
    ASSERT_FALSE( this->m <= a );
    this->m = a;
    ASSERT_FALSE( this->m < a );
    ASSERT_TRUE( this->m <= a );
    // great and great eq
    this->m.clear();
    a.clear();
    ASSERT_FALSE( this->m > a );
    ASSERT_TRUE( this->m >= a );
    this->AddValues( 5 );
    ASSERT_TRUE( this->m > a );
    ASSERT_TRUE( this->m >= a );
    this->m = a;
    ASSERT_FALSE( this->m > a );
    ASSERT_TRUE( this->m >= a );
    // swap
    this->m.clear();
    a.clear();
    this->AddValues( 3 );
    ASSERT_TRUE( this->m > a );
    ASSERT_TRUE( this->m >= a );
    swap( this->m, a );
    ASSERT_FALSE( this->m > a );
    ASSERT_FALSE( this->m >= a );
}
