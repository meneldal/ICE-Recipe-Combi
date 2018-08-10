# CMakeList.txt : CMake project for ICE-Recipe-Combi, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source to this project's executable.
add_executable (ICERecipeCombi "ICE-Recipe-Combi.cpp" "ICE-Recipe-Combi.h" "Ingredient.cpp" "Ingredient.h" "Recipe.h")

# TODO: Add tests and install targets if needed.
