cmake_minimum_required(VERSION 3.0)
project(tic-tac-toe LANGUAGES C)

# Find math and pthread library
find_library(MATH m REQUIRED)

# Create HEADER-ONLY library
add_library(HEADER-ONLY INTERFACE)

# Add project library
add_library(PROJECTLIB INTERFACE)
# Add directory "include/" to target library
target_include_directories(HEADER-ONLY INTERFACE ${CMAKE_SOURCE_DIR}/include)
# Add directory "lib/" to target library
target_include_directories(PROJECTLIB INTERFACE ${CMAKE_SOURCE_DIR}/lib)

# Target link math to HEADER-ONLY
target_link_libraries(HEADER-ONLY INTERFACE ${MATH})
target_link_libraries(HEADER-ONLY INTERFACE PROJECTLIB)

add_executable(tic-tac-toe src/main.c)

target_link_libraries(tic-tac-toe PRIVATE HEADER-ONLY)
