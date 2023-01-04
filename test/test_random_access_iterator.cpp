/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_random_access_iterator.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlancac </var/spool/mail/mlancac>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:11:26 by mlancac           #+#    #+#             */
/*   Updated: 2022/11/11 13:26:34 by mlancac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_containers.hpp"

#include <gtest/gtest.h>
#include <iostream>

template<typename T>
class test_random_access_iterator : public ::testing::Test {

    public:

/* Member Types */
#if LIB == FT
        typedef ft::random_access_iterator<T> iterator;
#elif LIB == STD
        typedef typename std::vector<T>::iterator iterator;
#endif

        void AddValues( int n, int increment = 2 ) {
            this->v.push_back( this->value );
            for ( int i = 0; i < n - 1; i++ ) {
                this->v.push_back( this->v[i] + increment );
            }
        }

        void PrintVector( void ) const {
            std::cout << "vector {";
            for ( auto it = this->v.begin(); it != this->v.end(); it++ )
                std::cout << " " << *it;
            std::cout << " }" << std::endl;
        }

    protected:

        /* Protected Attributes */
        ft::vector<T> v;
};

// TODO: figure a way to add std::string here as well
//		 -> maybe change behaviour of increment
typedef testing::Types< char, int, unsigned int, float, double > VectorTypes;

TYPED_TEST_SUITE( test_random_access_iterator, VectorTypes );

TYPED_TEST( test_random_access_iterator, constructor ) {}
