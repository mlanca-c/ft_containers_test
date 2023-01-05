/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_iterator_traits.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlancac </var/spool/mail/mlancac>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:21:34 by mlancac           #+#    #+#             */
/*   Updated: 2022/11/10 15:24:57 by mlancac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_containers.hpp"

#include <gtest/gtest.h>
#include <iostream>

TEST( test_iterator_traits, iterator ) {

    typedef ft::iterator< ft::random_access_iterator_tag, int > iterator;
    typedef ft::iterator_traits< iterator >                     iterator_traits;

    EXPECT_EQ( typeid( iterator_traits::difference_type ),
               typeid( iterator::difference_type ) );

    EXPECT_EQ( typeid( iterator_traits::value_type ),
               typeid( iterator::value_type ) );

    EXPECT_EQ( typeid( iterator_traits::pointer ),
               typeid( iterator::pointer ) );

    EXPECT_EQ( typeid( iterator_traits::reference ),
               typeid( iterator::reference ) );

    EXPECT_EQ( typeid( ft::random_access_iterator_tag ),
               typeid( iterator::iterator_category ) );

    EXPECT_EQ( typeid( iterator_traits::iterator_category ),
               typeid( iterator::iterator_category ) );
}

TEST( test_iterator_traits, T ) {

    typedef ft::iterator_traits<int*> iterator_traits;

    EXPECT_EQ( typeid( iterator_traits::difference_type ),
               typeid( ptrdiff_t ) );

    EXPECT_EQ( typeid( iterator_traits::value_type ), typeid( int ) );

    EXPECT_EQ( typeid( iterator_traits::pointer ), typeid( int* ) );

    EXPECT_EQ( typeid( iterator_traits::reference ), typeid( int& ) );

    EXPECT_EQ( typeid( iterator_traits::iterator_category ),
               typeid( ft::random_access_iterator_tag ) );
}

TEST( test_iterator_traits, T_const ) {

    typedef ft::iterator_traits<int const*> iterator_traits;

    EXPECT_EQ( typeid( iterator_traits::difference_type ),
               typeid( ptrdiff_t ) );

    EXPECT_EQ( typeid( iterator_traits::value_type ), typeid( int ) );

    EXPECT_EQ( typeid( iterator_traits::pointer ), typeid( int const* ) );

    EXPECT_EQ( typeid( iterator_traits::reference ), typeid( int const& ) );

    EXPECT_EQ( typeid( iterator_traits::iterator_category ),
               typeid( ft::random_access_iterator_tag ) );
}
