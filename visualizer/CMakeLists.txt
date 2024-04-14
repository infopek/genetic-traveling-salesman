cmake_minimum_required(VERSION 3.16..3.24)

project(Visualizer	
    VERSION 1.0.0
    DESCRIPTION "Genetic algorithm visualizer using SFML"
    LANGUAGES CXX)  

add_library(Visualizer
  	src/visualizer/visualizer.cpp)
add_library(Visualizer::Visualizer ALIAS Visualizer)

target_include_directories(
    Visualizer 
		PUBLIC 	
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)

target_link_libraries(
    Visualizer
        PUBLIC
            Core::Core
        PRIVATE
            sfml-system
            sfml-network 
            sfml-graphics 
            sfml-window)
