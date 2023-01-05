/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlancac </var/spool/mail/mlancac>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:29:56 by mlancac           #+#    #+#             */
/*   Updated: 2023/01/03 10:23:40 by mlanca-c         ###   ########.fr       */
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
class test_vector : public ::testing::Test {

    public:

        void SetUp( void ) {}

        void TearDown( void ) {}

        void AddValues( int n, int increment = 2 ) {
            this->v.push_back( this->value );
            size_t s = this->v.size();
            for ( size_t i = s; i < s + n - 1; i++ ) {
                this->v.push_back( this->v[i - 1] + increment );
            }
        }

        void PrintVector( void ) const {
            std::cout << "vector {";
            for ( auto it = this->v.begin(); it != this->v.end(); it++ )
                std::cout << " " << *it;
            std::cout << " }" << std::endl;
        }

        void PrintVector( ft::vector<T>& a ) const {
            std::cout << "vector {";
            for ( auto it = a.begin(); it != a.end(); it++ )
                std::cout << " " << *it;
            std::cout << " }" << std::endl;
        }

    protected:

        ft::vector<T> v;
        T             value;
};

// TODO: figure a way to add std::string here as well
//		-> maybe change behaviour of increment
//  typedef testing::Types< int > VectorTypes;
typedef testing::Types< char, int, unsigned int, float, double > VectorTypes;

TYPED_TEST_SUITE( test_vector, VectorTypes );

/* ************************************************************************** */
/* Tests                                                                      */
/* ************************************************************************** */

TYPED_TEST( test_vector, default_constructor ) {

    ft::vector<TypeParam> a;

    ASSERT_EQ( this->v.size(), 0 );
    ASSERT_EQ( this->v.capacity(), 0 );
    ASSERT_EQ( a.size(), 0 );
    ASSERT_EQ( a.capacity(), 0 );
}

TYPED_TEST( test_vector, fill_constructor ) {

    ft::vector<TypeParam> a( 3 );
    ft::vector<TypeParam> b( 3, this->value );
    // testing size
    ASSERT_EQ( a.size(), 3 );
    ASSERT_EQ( b.size(), 3 );
    // testing capacity
    ASSERT_EQ( a.capacity(), 3 );
    ASSERT_EQ( b.capacity(), 3 );
    // testing vector b's values
    this->v.push_back( this->value );
    this->v.push_back( this->value );
    this->v.push_back( this->value );
    ASSERT_TRUE( b == this->v );
}

TYPED_TEST( test_vector, range_constructor ) {

    ft::vector<TypeParam> a;
    a.push_back( this->value );
    a.push_back( ++this->value );
    a.push_back( ++this->value );
    ft::vector<TypeParam> b( a.begin(), a.end() );
    // testing size
    ASSERT_EQ( a.size(), 3 );
    ASSERT_EQ( b.size(), 3 );
    // testing capacity
    ASSERT_EQ( a.capacity(), 4 );
    ASSERT_EQ( b.capacity(), 3 );
    // testing vector b's values
    ASSERT_TRUE( a == b );
    ASSERT_TRUE( a != this->v );
}

TYPED_TEST( test_vector, copy_constructor ) {

    this->AddValues( 3 );
    ft::vector<TypeParam> a( this->v );
    this->AddValues( 1 );
    ft::vector<TypeParam> b( this->v );
    // testing size
    ASSERT_EQ( a.size(), 3 );
    ASSERT_EQ( b.size(), 4 );
    // testing capacity
    ASSERT_EQ( a.capacity(), 3 );
    ASSERT_EQ( b.capacity(), 4 );
    // testing values
    ASSERT_FALSE( a == b );
    ASSERT_TRUE( b == this->v );
    b.pop_back();
    ASSERT_TRUE( a == b );
}

TYPED_TEST( test_vector, operator_assignment ) {

    ft::vector<TypeParam> a( 3, this->value );
    ft::vector<TypeParam> b( a );
    this->AddValues( 3, 0 );
    // testing size
    ASSERT_EQ( a.size(), 3 );
    ASSERT_EQ( b.size(), 3 );
    // testing capacity
    ASSERT_EQ( a.capacity(), 3 );
    ASSERT_EQ( b.capacity(), 3 );
    // testing values
    ASSERT_TRUE( this->v == a );
    ASSERT_TRUE( a == b );
    a.push_back( ++this->value );
    ASSERT_FALSE( a == b );
    b = a;
    // testing capacity
    ASSERT_EQ( a.capacity(), 6 );
    ASSERT_EQ( b.capacity(), 4 );
    // testing values
    ASSERT_TRUE( a == b );
}

TYPED_TEST( test_vector, destructor ) {

    ft::vector<TypeParam>* a = new ft::vector<TypeParam>;
    ft::vector<TypeParam>* b = new ft::vector<TypeParam>( 3 );
    ft::vector<TypeParam>* c =
        new ft::vector<TypeParam>( a->begin(), a->end() );
    ft::vector<TypeParam>* d = new ft::vector<TypeParam>( *b );
    delete a;
    delete b;
    delete c;
    delete d;
}

/* Testing Iterators */
TYPED_TEST( test_vector, begin ) {

    this->AddValues( 2 );
    ASSERT_EQ( *this->v.begin(), this->value );
    ASSERT_EQ( typeid( this->v.begin() ),
               typeid( typename ft::vector<TypeParam>::iterator ) );
}

TYPED_TEST( test_vector, end ) {

    this->AddValues( 2 );
    ASSERT_EQ( *this->v.end(), *( --this->v.rbegin() ) );
    ASSERT_EQ( typeid( this->v.end() ),
               typeid( typename ft::vector<TypeParam>::iterator ) );
}

TYPED_TEST( test_vector, rbegin ) {

    this->AddValues( 2 );
    ASSERT_EQ( *this->v.rbegin(), *( --this->v.end() ) );
    ASSERT_EQ( typeid( this->v.rbegin() ),
               typeid( typename ft::vector<TypeParam>::reverse_iterator ) );
}

TYPED_TEST( test_vector, rend ) {

    this->AddValues( 2 );
    ASSERT_EQ( *this->v.rend(), *( --this->v.begin() ) );
    ASSERT_EQ( typeid( this->v.rend() ),
               typeid( typename ft::vector<TypeParam>::reverse_iterator ) );
}

/* Testing Capacity */
TYPED_TEST( test_vector, size ) {

    ASSERT_EQ( this->v.size(), 0 );
    // Adding values
    this->AddValues( 1 );
    ASSERT_EQ( this->v.size(), 1 );
    this->AddValues( 12 );
    ASSERT_EQ( this->v.size(), 13 );
    // Removing values
    this->v.pop_back();
    ASSERT_EQ( this->v.size(), 12 );
    // clearing vector
    this->v.clear();
    ASSERT_EQ( this->v.size(), 0 );
}

TYPED_TEST( test_vector, max_size ) {
    ASSERT_EQ( this->v.max_size(), this->v.get_allocator().max_size() );
}

TYPED_TEST( test_vector, resize ) {

    TypeParam             arr[]{ static_cast<TypeParam>( this->value ),
                                 static_cast<TypeParam>( this->value ),
                                 static_cast<TypeParam>( this->value + 1 ),
                                 static_cast<TypeParam>( this->value + 1 ),
                                 static_cast<TypeParam>( this->value + 1 ),
                                 static_cast<TypeParam>( this->value + 1 ) };
    ft::vector<TypeParam> a( arr, arr + 2 );
    ft::vector<TypeParam> b( arr, arr + 6 );
    ft::vector<TypeParam> c;
    // Resizing empty vector
    this->v.resize( 2, this->value++ );
    ASSERT_EQ( this->v.size(), 2 );
    ASSERT_EQ( this->v.capacity(), 2 );
    ASSERT_TRUE( this->v == a );
    // Adding elements
    this->AddValues( 4, 0 );
    ASSERT_EQ( this->v.size(), 6 );
    ASSERT_EQ( this->v.capacity(), 8 );
    ASSERT_TRUE( this->v == b );
    // Resizing back to 2 elements
    this->v.resize( 2 );
    ASSERT_EQ( this->v.size(), 2 );
    ASSERT_EQ( this->v.capacity(), 8 );
    ASSERT_TRUE( this->v == a );
    // Resizing vector to 0
    this->v.resize( 0 );
    ASSERT_EQ( this->v.size(), 0 );
    ASSERT_EQ( this->v.capacity(), 8 );
    ASSERT_TRUE( this->v == c );
    // resizing 9 elements
    c.resize( 9 );
    ASSERT_EQ( c.size(), 9 );
    ASSERT_EQ( c.capacity(), 9 );
}

TYPED_TEST( test_vector, capacity ) {

    // Adding values
    ASSERT_EQ( this->v.capacity(), 0 );
    this->AddValues( 2 );
    ASSERT_EQ( this->v.capacity(), 2 );
    this->AddValues( 2 );
    ASSERT_EQ( this->v.capacity(), 4 );
    this->AddValues( 2 );
    ASSERT_GE( this->v.capacity(), this->v.size() );
    this->AddValues( 2 );
    ASSERT_GE( this->v.capacity(), this->v.size() );
    // Removing Values
    size_t cap = this->v.capacity();
    this->v.pop_back();
    this->v.pop_back();
    ASSERT_EQ( this->v.capacity(), cap );
    // Resizing vector
    this->v.resize( 1 );
    ASSERT_EQ( this->v.capacity(), cap );
    // Clearing vector
    this->v.clear();
    ASSERT_EQ( this->v.capacity(), cap );
}

TYPED_TEST( test_vector, empty ) {

    ASSERT_TRUE( this->v.empty() );
    this->AddValues( 5 );
    ASSERT_FALSE( this->v.empty() );
    this->v.clear();
    ASSERT_TRUE( this->v.empty() );
}

TYPED_TEST( test_vector, reserve ) {

    this->v.reserve( 4 );
    ASSERT_EQ( this->v.capacity(), 4 );
    this->v.reserve( 100 );
    ASSERT_EQ( this->v.capacity(), 100 );
    ASSERT_THROW( this->v.reserve( this->v.max_size() + 1 ),
                  std::length_error );
}

/* Testing Element Access */
TYPED_TEST( test_vector, operator_access ) {

    this->AddValues( 10 );
    for ( int i = 0; i < 10; i++ ) ASSERT_EQ( this->v[i], this->v.at( i ) );
}

TYPED_TEST( test_vector, at ) {

    this->AddValues( 10 );
    for ( int i = 0; i < 10; i++ ) ASSERT_EQ( this->v.at( i ), this->v[i] );
    // testing exception thrown
    ASSERT_THROW( this->v.at( 11 ), std::out_of_range );
}

TYPED_TEST( test_vector, front ) {

    this->AddValues( 10 );
    // Testing with operator[]
    ASSERT_EQ( this->v.front(), this->v[0] );
    // Testing with at method
    ASSERT_EQ( this->v.front(), this->v.at( 0 ) );
    // Testing with iterator
    ASSERT_EQ( this->v.front(), *this->v.begin() );
}

TYPED_TEST( test_vector, back ) {

    this->AddValues( 10 );
    // Testing with operator[]
    ASSERT_EQ( this->v.back(), this->v[9] );
    // Testing with at method
    ASSERT_EQ( this->v.back(), this->v.at( 9 ) );
    // Testing with iterator
    ASSERT_EQ( this->v.back(), *( --this->v.end() ) );
}

TYPED_TEST( test_vector, assign_range ) {

    // assigning 2 values
    this->AddValues( 2, 0 );
    ft::vector<TypeParam> a;
    auto                  it = this->v.begin();
    a.assign( this->v.begin(), this->v.end() );
    ASSERT_EQ( a.size(), 2 );
    // checking values
    TypeParam             arr[] = { this->value, this->value, this->value };
    ft::vector<TypeParam> b( arr, arr + 2 );
    ASSERT_TRUE( a == b );
    // assigning 3 values
    ft::vector<TypeParam> c( arr, arr + 3 );
    a.assign( arr, arr + 3 );
    // checking values
    ASSERT_EQ( a.size(), 3 );
    ASSERT_TRUE( a == c );
}

/* Testing Modifiers */
TYPED_TEST( test_vector, assign_fill ) {

    // assigning 3 elements to vector
    TypeParam             v1[]{ this->value, this->value, this->value };
    ft::vector<TypeParam> a( v1, v1 + 3 );
    this->v.assign( 3, this->value );
    ASSERT_EQ( this->v.size(), 3 );
    ASSERT_EQ( this->v.capacity(), 3 );
    ASSERT_TRUE( this->v == a );
    // assigning 2 elements to vector
    this->v.assign( 2, ++this->value );
    TypeParam             v2[]{ this->value, this->value };
    ft::vector<TypeParam> b( v2, v2 + 2 );
    ASSERT_TRUE( this->v == b );
    ASSERT_EQ( this->v.size(), 2 );
    ASSERT_EQ( this->v.capacity(), 3 );
    // assigning 5 elements to vector
    this->v.assign( 5, ++this->value );
    TypeParam v3[]{ this->value, this->value, this->value, this->value,
                    this->value };
    ft::vector<TypeParam> c( v3, v3 + 5 );
    ASSERT_TRUE( this->v == c );
    ASSERT_EQ( this->v.size(), 5 );
    ASSERT_EQ( this->v.capacity(), 5 );
    // assigning no elements to vector
    ft::vector<TypeParam> d;
    this->v.assign( 0, this->value );
    ASSERT_TRUE( this->v == d );
    ASSERT_EQ( this->v.size(), 0 );
    ASSERT_EQ( this->v.capacity(), 5 );
}

// TODO: check iterators integrity.
TYPED_TEST( test_vector, push_back ) {

    // adding first value
    ASSERT_EQ( this->v.size(), 0 );
    this->v.push_back( this->value );
    ASSERT_EQ( this->v.size(), 1 );
    ASSERT_EQ( this->v.at( 0 ), this->value );
    ASSERT_EQ( this->v[0], this->value );
    // adding another value
    this->value += 2;
    this->v.push_back( this->value );
    ASSERT_EQ( this->v.size(), 2 );
    ASSERT_EQ( this->v.at( 1 ), this->value );
    ASSERT_EQ( this->v[1], this->value );
    // checking values
    TypeParam arr[] = {
        static_cast<TypeParam>( this->value - 2 ),
        this->value,
    };
    ft::vector<TypeParam> a;
    a.insert( a.begin(), arr, arr + 2 );
    ASSERT_TRUE( this->v == a );
    // adding a bunch more values
    // TODO: This goes into stress testing ( testing w/ max_size())
    this->v.clear();
    for ( size_t i = 0; i < 100; i++ ) {
        this->v.push_back( ++this->value );
        ASSERT_EQ( this->v.size(), i + 1 );
        ASSERT_EQ( this->v[i], this->value );
        ASSERT_EQ( this->v.at( i ), this->value );
    }
}

TYPED_TEST( test_vector, pop_back ) {

    this->AddValues( 10, 0 );
    auto it = this->v.end();

    // removing values
    ASSERT_NO_THROW( this->v.pop_back() );
    ASSERT_NE( this->v.end(), it );
    ASSERT_EQ( this->v.size(), 9 );
    ASSERT_EQ( this->v.capacity(), 16 );
    // removing values
    this->v.pop_back();
    ASSERT_EQ( this->v.size(), 8 );
    ASSERT_EQ( this->v.capacity(), 16 );
    // checking values
    ft::vector<TypeParam> a;
    TypeParam arr[10] = { this->value, this->value, this->value, this->value,
                          this->value, this->value, this->value, this->value };
    a.insert( a.begin(), arr, arr + 8 );
    ASSERT_TRUE( this->v == a );
    // removing last value
    this->v.clear();
    this->v.push_back( this->value );
    this->v.pop_back();
    ASSERT_EQ( this->v.size(), 0 );
    ASSERT_EQ( this->v.capacity(), 16 );
}

TYPED_TEST( test_vector, insert_value ) {

    TypeParam arr[] = { static_cast<TypeParam>( this->value + 2 ),
                        static_cast<TypeParam>( this->value ),
                        static_cast<TypeParam>( this->value + 1 ),
                        static_cast<TypeParam>( this->value + 4 ),
                        static_cast<TypeParam>( this->value + 1 ),
                        static_cast<TypeParam>( this->value + 1 ),
                        static_cast<TypeParam>( this->value + 1 ),
                        static_cast<TypeParam>( this->value + 3 ) };
    // inserting this->value in last position
    auto it = this->v.end();
    it = this->v.insert( it, this->value );
    ASSERT_EQ( this->v.begin(), it );
    ASSERT_EQ( this->v.size(), 1 );
    ASSERT_EQ( this->v.capacity(), 1 );
    ASSERT_EQ( this->v.at( 0 ), this->value );
    // Adding 4 more values with push_back
    this->value++;
    this->AddValues( 4, 0 );
    ASSERT_EQ( this->v.size(), 5 );
    ASSERT_EQ( this->v.capacity(), 8 );
    // inserting this->value in first position
    it = this->v.begin();
    it = this->v.insert( it, ++this->value );
    ASSERT_EQ( this->v.begin(), it );
    ASSERT_EQ( this->v.size(), 6 );
    ASSERT_EQ( this->v.capacity(), 8 );
    // inserting this->value in last position
    auto beg = this->v.begin();
    it = this->v.end();
    it = this->v.insert( it, ++this->value );
    ASSERT_NE( this->v.end(), it );
    ASSERT_EQ( this->v.begin(), beg );
    ASSERT_EQ( this->v.at( 6 ), this->value );
    ASSERT_EQ( this->v.size(), 7 );
    ASSERT_EQ( this->v.capacity(), 8 );
    // inserting this->value in third position
    beg = this->v.begin();
    it = this->v.begin() + 3;
    it = this->v.insert( it, ++this->value );
    ASSERT_NE( this->v.end(), it );
    ASSERT_EQ( this->v.begin(), beg );
    ASSERT_EQ( this->v.at( 3 ), this->value );
    ASSERT_EQ( this->v.size(), 8 );
    ASSERT_EQ( this->v.capacity(), 8 );
    // checking values
    ft::vector<TypeParam> a;
    a.insert( a.begin(), arr, arr + 8 );
    ASSERT_TRUE( this->v == a );
}

TYPED_TEST( test_vector, insert_fill ) {

    TypeParam arr[] = { static_cast<TypeParam>( this->value + 2 ),
                        static_cast<TypeParam>( this->value + 2 ),
                        static_cast<TypeParam>( this->value + 2 ),
                        static_cast<TypeParam>( this->value + 2 ),
                        static_cast<TypeParam>( this->value + 3 ),
                        static_cast<TypeParam>( this->value ),
                        static_cast<TypeParam>( this->value ),
                        static_cast<TypeParam>( this->value + 1 ),
                        static_cast<TypeParam>( this->value + 1 ),
                        static_cast<TypeParam>( this->value + 1 ) };
    // inserting 2 this->value in last position
    auto it = this->v.end();
    this->v.insert( it, 2, this->value );
    ASSERT_NE( this->v.begin(), it );
    ASSERT_EQ( this->v.size(), 2 );
    ASSERT_EQ( this->v.capacity(), 2 );
    ASSERT_EQ( this->v.at( 0 ), this->value );
    ASSERT_EQ( this->v.at( 1 ), this->value );
    // inserting 3 this->value in last position
    it = this->v.end();
    this->v.insert( it, 3, ++this->value );
    ASSERT_NE( this->v.begin(), it );
    ASSERT_EQ( this->v.size(), 5 );
    ASSERT_EQ( this->v.capacity(), 5 );
    // inserting this->value in first position
    it = this->v.begin();
    this->v.insert( it, 4, ++this->value );
    ASSERT_NE( this->v.begin(), it );
    ASSERT_EQ( this->v.size(), 9 );
    // inserting this->value in third position
    it = this->v.begin() + 4;
    this->v.insert( it, 1, ++this->value );
    ASSERT_NE( this->v.end(), it );
    ASSERT_EQ( this->v.size(), 10 );
    // checking values
    ft::vector<TypeParam> a;
    a.insert( a.begin(), arr, arr + 10 );
    ASSERT_TRUE( this->v == a );
}

TYPED_TEST( test_vector, insert_range ) {

    TypeParam arr[] = { static_cast<TypeParam>( this->value + 1 ),
                        static_cast<TypeParam>( this->value + 1 ),
                        static_cast<TypeParam>( this->value + 1 ),
                        static_cast<TypeParam>( this->value + 2 ),
                        static_cast<TypeParam>( this->value ),
                        static_cast<TypeParam>( this->value ) };
    // inserting array of 2 in last position
    TypeParam v1[] = { this->value, this->value };
    auto      it = this->v.end();
    ASSERT_NO_THROW( this->v.insert( this->v.end(), v1, v1 + 2 ) );
    ASSERT_NE( this->v.end(), it );
    ASSERT_EQ( this->v.size(), 2 );
    // inserting array of 3 in first position
    TypeParam v2[] = { static_cast<TypeParam>( this->value + 1 ),
                       static_cast<TypeParam>( this->value + 1 ),
                       static_cast<TypeParam>( this->value + 1 ) };
    it = this->v.begin();
    ASSERT_NO_THROW( this->v.insert( this->v.begin(), v2, v2 + 3 ) );
    ASSERT_NE( this->v.begin(), it );
    ASSERT_EQ( this->v.size(), 5 );
    // inserting array of 1 in third position
    TypeParam v3[] = { static_cast<TypeParam>( this->value + 2 ) };
    it = this->v.begin();
    ASSERT_NO_THROW( this->v.insert( this->v.begin() + 3, v3, v3 + 1 ) );
    ASSERT_NE( this->v.begin(), it );
    ASSERT_EQ( this->v.size(), 6 );
    // checking values
    ft::vector<TypeParam> a;
    a.insert( a.begin(), arr, arr + 6 );
    ASSERT_TRUE( this->v == a );
}

TYPED_TEST( test_vector, erase ) {

    TypeParam             arr[]{ static_cast<TypeParam>( this->value + 1 ),
                                 static_cast<TypeParam>( this->value + 2 ),
                                 static_cast<TypeParam>( this->value + 4 ) };
    ft::vector<TypeParam> a( arr, arr + 3 );
    this->AddValues( 6, 1 );
    // erase first value
    ASSERT_EQ( this->v.size(), 6 );
    ASSERT_EQ( this->v.capacity(), 8 );
    auto it = this->v.begin();
    this->v.erase( it );
    ASSERT_EQ( this->v.begin(), it );
    ASSERT_EQ( this->v.size(), 5 );
    ASSERT_EQ( this->v.capacity(), 8 );
    // erase last value
    this->v.erase( this->v.end() - 1 );
    ASSERT_EQ( this->v.size(), 4 );
    ASSERT_EQ( this->v.capacity(), 8 );
    // erase thrid value
    this->v.erase( this->v.begin() + 2 );
    ASSERT_EQ( this->v.size(), 3 );
    ASSERT_EQ( this->v.capacity(), 8 );
    // checking values
    ASSERT_TRUE( this->v == a );
}

TYPED_TEST( test_vector, erase_range ) {

    TypeParam             arr[]{ static_cast<TypeParam>( this->value + 2 ),
                                 static_cast<TypeParam>( this->value + 6 ) };
    ft::vector<TypeParam> a( arr, arr + 2 );
    this->AddValues( 10, 1 );
    // erase first two values
    ASSERT_EQ( this->v.size(), 10 );
    ASSERT_EQ( this->v.capacity(), 16 );
    auto it = this->v.begin();
    this->v.erase( this->v.begin(), this->v.begin() + 2 );
    ASSERT_EQ( this->v.begin(), it );
    ASSERT_EQ( this->v.size(), 8 );
    ASSERT_EQ( this->v.capacity(), 16 );
    // erase last three values
    this->v.erase( this->v.end() - 3, this->v.end() );
    ASSERT_EQ( this->v.size(), 5 );
    ASSERT_EQ( this->v.capacity(), 16 );
    // erase three middle values
    this->v.erase( this->v.begin() + 1, this->v.begin() + 4 );
    ASSERT_EQ( this->v.size(), 2 );
    ASSERT_EQ( this->v.capacity(), 16 );
    // checking values
    ASSERT_TRUE( this->v == a );
    // erasing everything
    this->v.erase( this->v.begin(), this->v.end() );
    ASSERT_FALSE( this->v == a );
    ASSERT_EQ( this->v.size(), 0 );
    ASSERT_EQ( this->v.capacity(), 16 );
    ft::vector<TypeParam> b;
    ASSERT_TRUE( this->v == b );
}

TYPED_TEST( test_vector, swap ) {

    ft::vector<TypeParam> a( 3, this->value );
    ASSERT_EQ( a.size(), 3 );
    ASSERT_EQ( this->v.size(), 0 );
    a.swap( this->v );
    ASSERT_EQ( a.size(), 0 );
    ASSERT_EQ( this->v.size(), 3 );
    ASSERT_EQ( this->v[0], this->value );
    ASSERT_EQ( this->v[1], this->value );
    ASSERT_EQ( this->v[2], this->value );
    this->v.swap( a );
    ASSERT_EQ( a.size(), 3 );
    ASSERT_EQ( this->v.size(), 0 );
    ASSERT_EQ( a[0], this->value );
    ASSERT_EQ( a[1], this->value );
    ASSERT_EQ( a[2], this->value );
}

TYPED_TEST( test_vector, clear ) {

    this->AddValues( 5 );
    ASSERT_EQ( this->v.size(), 5 );
    size_t cap = this->v.capacity();
    this->v.clear();
    ASSERT_EQ( this->v.size(), 0 );
    ASSERT_EQ( this->v.capacity(), cap );
}

/* Testing Allocator */
TYPED_TEST( test_vector, get_allocator ) {

    ASSERT_EQ( this->v.get_allocator(), std::allocator<TypeParam>() );
    ASSERT_EQ( typeid( this->v.get_allocator() ),
               typeid( std::allocator<TypeParam> ) );
}

/* Testing Non-Member Function Overloads */
TYPED_TEST( test_vector, non_member_functions ) {

    ft::vector<TypeParam> a;
    // equals
    ASSERT_TRUE( this->v == this->v );
    this->AddValues( 5 );
    ASSERT_FALSE( this->v == a );
    a = this->v;
    ASSERT_TRUE( a == this->v );
    // not equals
    ASSERT_FALSE( this->v != this->v );
    this->AddValues( 5 );
    ASSERT_TRUE( this->v != a );
    a = this->v;
    ASSERT_FALSE( a != this->v );
    // less and less eq
    ASSERT_FALSE( this->v < a );
    ASSERT_TRUE( this->v <= a );
    this->AddValues( 5 );
    ASSERT_FALSE( this->v < a );
    ASSERT_FALSE( this->v <= a );
    this->v = a;
    ASSERT_FALSE( this->v < a );
    ASSERT_TRUE( this->v <= a );
    // great and great eq
    this->v.clear();
    a.clear();
    ASSERT_FALSE( this->v > a );
    ASSERT_TRUE( this->v >= a );
    this->AddValues( 5 );
    ASSERT_TRUE( this->v > a );
    ASSERT_TRUE( this->v >= a );
    this->v = a;
    ASSERT_FALSE( this->v > a );
    ASSERT_TRUE( this->v >= a );
    // swap
    this->v.clear();
    a.clear();
    this->AddValues( 3 );
    ASSERT_TRUE( this->v > a );
    ASSERT_TRUE( this->v >= a );
    swap( this->v, a );
    ASSERT_FALSE( this->v > a );
    ASSERT_FALSE( this->v >= a );
}
