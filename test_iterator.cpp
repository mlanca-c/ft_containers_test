/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_iterator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlancac </var/spool/mail/mlancac>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:26:32 by mlancac           #+#    #+#             */
/*   Updated: 2022/11/26 15:16:35 by mlancac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_containers.hpp"

#include <gtest/gtest.h>
#include <iostream>

TEST( test_iterator, constructor ) {

    ft::iterator<ft::random_access_iterator_tag, int>   a;
    ft::iterator<ft::random_access_iterator_tag, char>* b;

    b = new ft::iterator<ft::random_access_iterator_tag, char>;
    delete b;
}

TEST( test_iterator, member_types ) {

    typedef ft::iterator<ft::random_access_iterator_tag, int> Iterator;
    Iterator                                                  a;

    ASSERT_EQ( typeid( Iterator::value_type ), typeid( int ) );

    ASSERT_EQ( typeid( Iterator::difference_type ), typeid( ptrdiff_t ) );

    ASSERT_EQ( typeid( Iterator::pointer ), typeid( int* ) );

    ASSERT_EQ( typeid( Iterator::reference ), typeid( int& ) );

    ASSERT_EQ( typeid( Iterator::iterator_category ),
               typeid( ft::random_access_iterator_tag ) );
}
