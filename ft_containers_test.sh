#!/bin/bash


SED="sed -i.tmp --expression"
LIB=$1
if [[ "$LIB" == "std" ]]; then
	echo "std"
	$SED '20s/.*/# define LIB STD/' ../inc/ft_containers.hpp
elif [[ "$LIB" == "ft" ]]; then
	echo "ft"
	$SED '20s/.*/# define LIB FT/' ../inc/ft_containers.hpp
fi

# checking if build/ already exists
if [ -d "build/" ]; then
	cd build;
else
	mkdir build;
	cd build;
	cmake .. -Wno-dev
fi

# compling tests
make && ./ft_containers_test --gtest_color=yes
cd ../;

$SED '20s/.*/# define LIB FT/' ../inc/ft_containers.hpp
