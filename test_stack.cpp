/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlancac </var/spool/mail/mlancac>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:46:50 by mlancac           #+#    #+#             */
/*   Updated: 2022/11/26 19:03:51 by mlancac          ###   ########.fr       */
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
class MutantStack : public ft::stack< T, ft::vector<T> > {
    public:

        typedef typename ft::stack<T, ft::vector<T> >::container_type::iterator
            iterator;

        MutantStack( void ) {}

        ~MutantStack( void ) {}

        MutantStack( MutantStack<T> const& src ) { *this = src; }

        MutantStack<T>& operator=( MutantStack<T> const& rhs ) {
            this->c = rhs.c;
            return ( *this );
        }

        iterator begin( void ) { return ( this->c.begin() ); }

        iterator end( void ) { return ( this->c.end() ); }
};

template<typename T>
class test_stack : public ::testing::Test {

    public:

        void SetUp( void ) {}

        void TearDown( void ) {}

        void AddValues( int n, int increment = 2 ) {
            this->s.push( this->value );
            size_t s = this->s.size();
            auto   val = this->value;
            for ( size_t i = s; i < s + n - 1; i++ ) {
                val += increment;
                this->s.push( val );
            }
        }

        void PrintStack( void ) {
            std::cout << "stack {";
            for ( auto it = this->s.begin(); it != this->s.end(); it++ )
                std::cout << " " << *it;
            std::cout << " }" << std::endl;
        }

    protected:

        MutantStack<T> s;
        T              value;
};

// TODO: figure a way to add std::string here as well
//		-> maybe change behaviour of increment
//  typedef testing::Types< int > StackTypes;
typedef testing::Types< char, int, unsigned int, float, double > StackTypes;

TYPED_TEST_SUITE( test_stack, StackTypes );

/* ************************************************************************** */
/* Tests                                                                      */
/* ************************************************************************** */

TYPED_TEST( test_stack, default_constructor ) {

    ft::vector<TypeParam>                        v( 3 );
    ft::stack<TypeParam>                         a;
    ft::stack<TypeParam, ft::vector<TypeParam> > b( v );

    ASSERT_EQ( this->s.size(), 0 );
    ASSERT_EQ( a.size(), 0 );
    ASSERT_EQ( b.size(), 3 );
}

TYPED_TEST( test_stack, destructor ) {

    ft::vector<TypeParam> v( 3 );

    ft::stack<TypeParam, ft::vector<TypeParam> >* a;
    a = new ft::stack<TypeParam, ft::vector<TypeParam> >;
    ft::stack<TypeParam, ft::vector<TypeParam> >* b;
    b = new ft::stack<TypeParam, ft::vector<TypeParam> >( v );

    delete a;
    delete b;
}

TYPED_TEST( test_stack, top ) {

    this->AddValues( 5, 1 );
    ASSERT_EQ( this->s.top(), this->value + 4 );
    this->s.pop();
    ASSERT_EQ( this->s.top(), this->value + 3 );
}

TYPED_TEST( test_stack, empty ) {

    ASSERT_TRUE( this->s.empty() );
    this->s.push( this->value );
    ASSERT_FALSE( this->s.empty() );
}

TYPED_TEST( test_stack, size ) {

    ASSERT_EQ( this->s.size(), 0 );
    this->s.push( this->value );
    ASSERT_EQ( this->s.size(), 1 );
    this->AddValues( 4 );
    ASSERT_EQ( this->s.size(), 5 );
}

TYPED_TEST( test_stack, push ) {

    ASSERT_TRUE( this->s.empty() );
    this->s.push( this->value );
    ASSERT_EQ( this->s.size(), 1 );
    this->s.push( this->value );
    ASSERT_EQ( this->s.size(), 2 );
    this->s.push( this->value );
    ASSERT_EQ( this->s.size(), 3 );
    this->s.push( this->value );
    ASSERT_EQ( this->s.size(), 4 );
    this->s.push( this->value );
    ASSERT_EQ( this->s.size(), 5 );
}

TYPED_TEST( test_stack, pop ) {

    this->AddValues( 4 );
    ASSERT_EQ( this->s.size(), 4 );
    this->s.pop();
    ASSERT_EQ( this->s.size(), 3 );
    this->s.pop();
    ASSERT_EQ( this->s.size(), 2 );
    this->s.pop();
    ASSERT_EQ( this->s.size(), 1 );
    this->s.pop();
    ASSERT_EQ( this->s.size(), 0 );
    ASSERT_TRUE( this->s.empty() );
}

TYPED_TEST( test_stack, non_menber_methods ) {
    // TODO: missing this one
}
