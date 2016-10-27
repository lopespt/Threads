cmake_minimum_required (VERSION 2.8)

# projectname is the same as the main-executable
project(prodconsu)

add_definitions('-g')
add_definitions('-Wall')
add_definitions('-std=c++11')

add_executable(main main.cpp )
target_link_libraries(main pthread)
