cmake_minimum_required(VERSION 3.15...3.30)
project(
	uav_sm
	VERSION 1.0
	LANGUAGES CXX)

# set(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find_package()

#####
# Add library
#####

# Add header only library
# add_library(tinyfsm INTERFACE)
# target_include_directories(tinyfsm INTERFACE
# 	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
# 	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
# )

# add_library(uavsm 
#   src/uav.cpp
# )
# target_include_directories(uavsm PUBLIC
# 	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
# 	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
# )

#####
# Build executables
#####

add_executable(main src/main.cpp src/uav.cpp)
target_include_directories(main PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
# target_link_libraries(main PUBLIC uavsm)