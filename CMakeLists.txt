# CMake Version
cmake_minimum_required(VERSION 3.0.2)

# oapi top level CMakeLists
project(Cython)

# Configure the testing
enable_testing()

# To generate the library we need the export macro
add_definitions(-DDLL_BUILD)

# Disable deprecation
add_definitions(-D_CRT_SECURE_NO_WARNINGS)


# Source files for this library
set( Cython_SRCS
	Cython.c
	)
	
# Include header files
set( Cython_HDRS
	Cython.h
	)

# Specified linked library
add_library( Cython STATIC ${Cython_HDRS} ${Cython_SRCS})
