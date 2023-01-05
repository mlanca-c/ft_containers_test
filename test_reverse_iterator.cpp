/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reverse_iterator.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlancac </var/spool/mail/mlancac>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:30:33 by mlancac           #+#    #+#             */
/*   Updated: 2022/11/26 21:16:50 by mlancac          ###   ########.fr       */
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

class test_reverse_iterator : public ::testing::Test {

    public:

        /* Member Types */

        // TODO: change std to ft
        typedef std::vector<int>               Vector;
        typedef typename Vector::iterator      Iterator;
        typedef ft::iterator_traits<Iterator>  Traits;
        typedef ft::reverse_iterator<Iterator> Reverse;

        /* Test Functions */
        void SetUp( void ) {
            this->v = new Vector( 10, 5 );
            this->it = new Iterator( this->v->begin() );
            this->rev = new Reverse( *this->it );
        }

        void TearDown( void ) {
            delete this->v;
            delete this->it;
            delete this->rev;
        }

    protected:

        Vector*   v;
        Iterator* it;
        Reverse*  rev;
};

/* ************************************************************************** */
/* Tests                                                                      */
/* ************************************************************************** */

TEST_F( test_reverse_iterator, Iterator ) {

    typedef ft::iterator< ft::random_access_iterator_tag, int > iterator;
    typedef ft::reverse_iterator< iterator > reverse_iterator;

    EXPECT_EQ( typeid( reverse_iterator::iterator_type ), typeid( iterator ) );

    EXPECT_EQ( typeid( reverse_iterator::iterator_category ),
               typeid( ft::random_access_iterator_tag ) );

    EXPECT_EQ( typeid( reverse_iterator::value_type ),
               typeid( iterator::value_type ) );

    EXPECT_EQ( typeid( reverse_iterator::value_type ), typeid( int ) );

    EXPECT_EQ( typeid( reverse_iterator::difference_type ),
               typeid( iterator::difference_type ) );

    EXPECT_EQ( typeid( reverse_iterator::pointer ),
               typeid( iterator::pointer ) );

    EXPECT_EQ( typeid( reverse_iterator::reference ),
               typeid( iterator::reference ) );
}

TEST_F( test_reverse_iterator, default_constructor ) {
    for ( auto it = this->v->rbegin(); it != this->v->rend(); it++ )
        EXPECT_EQ( *it, 5 );
}

TEST_F( test_reverse_iterator, initialization_constructor ) {}

TEST_F( test_reverse_iterator, copy_constructor ) {}

TEST_F( test_reverse_iterator, dereference_operator ) {}

TEST_F( test_reverse_iterator, adition_operator ) {}

TEST_F( test_reverse_iterator, increment_operator ) {}

TEST_F( test_reverse_iterator, advance_operator ) {}

TEST_F( test_reverse_iterator, subtraction_operator ) {}

TEST_F( test_reverse_iterator, decrease_operator ) {}

TEST_F( test_reverse_iterator, retrocede_operator ) {}

TEST_F( test_reverse_iterator, dereference_iterator_operator ) {}

TEST_F( test_reverse_iterator, dereference_with_offset_operator ) {}

TEST_F( test_reverse_iterator, relational_operators ) {}

TEST_F( test_reverse_iterator, addition_operator ) {}

TEST_F( test_reverse_iterator, subtraction_overload_operator ) {}

TEST_F( test_reverse_iterator, base ) {}
