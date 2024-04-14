cmake_minimum_required(VERSION 3.16..3.24)

project(Core	
    VERSION 1.0.0
    DESCRIPTION "Genetic algorithm implementation"
    LANGUAGES CXX
    )  

add_library(Core 
    src/genetic-algorithm/genetic_algorithm.cpp
    src/genetic-algorithm/traveling_salesman.cpp
  	)
add_library(Core::Core ALIAS Core)

target_include_directories(
    Core 
		PUBLIC 	
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
	)
