/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlancac </var/spool/mail/mlancac>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:22:54 by mlancac           #+#    #+#             */
/*   Updated: 2022/10/19 16:30:09 by mlancac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_containers.hpp"

#include <gtest/gtest.h>
#include <iostream>

int main( int argc, char* argv[] ) {

    (void)argc;
    (void)argv;

    std::cout << "Using Library: " << ( LIB == FT ? "ft" : "std" ) << std::endl;

    testing::InitGoogleTest( &argc, argv );

    return ( RUN_ALL_TESTS() );
}
