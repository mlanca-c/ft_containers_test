cmake_minimum_required(VERSION 2.8)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(PROJECT_NAME ft_containers_test)
project(${PROJECT_NAME})

enable_testing()
find_package(PkgConfig)

include_directories(${CMAKE_SOURCE_DIR}/../inc/)

add_executable(${PROJECT_NAME}
	test.cpp
	test_utils.cpp
	test_vector.cpp
	test_stack.cpp
	test_map.cpp
	test_iterator.cpp
	test_iterator_traits.cpp
	test_reverse_iterator.cpp
	test_random_access_iterator.cpp
	test_Rb_tree.cpp
	test_speed.cpp
)

add_test(ft_containers_gtest ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
	PRIVATE gtest_main
)
