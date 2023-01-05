/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_speed.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlancac </var/spool/mail/mlancac>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:49:15 by mlancac           #+#    #+#             */
/*   Updated: 2023/01/03 15:55:24 by mlancac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* Headers                                                                    */
/* ************************************************************************** */

#include "ft_containers.hpp"

#include <gtest/gtest.h>
#include <iostream>

#define SPEED_FLAG 1000000

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

/* ************************************************************************** */
/* Tests                                                                      */
/* ************************************************************************** */

TEST( test_speed, vector ) {

    ft::vector<int> a;
    for ( int i = 0; i < SPEED_FLAG; i++ ) { a.push_back( i ); }
    for ( auto it = a.begin(); it != a.end(); it++ ) { (void)*it; }
}

TEST( test_speed, stack ) {

    MutantStack<int> a;
    for ( int i = 0; i < SPEED_FLAG; i++ ) { a.push( i ); }
    for ( auto it = a.begin(); it != a.end(); it++ ) { (void)*it; }
}

TEST( test_speed, map ) {

    ft::map<int, int> a;
    for ( int i = 0; i < SPEED_FLAG; i++ ) {
        a.insert( ft::make_pair( i, i * 2 ) );
    }
    for ( auto it = a.begin(); it != a.end(); it++ ) { (void)*it; }
}
